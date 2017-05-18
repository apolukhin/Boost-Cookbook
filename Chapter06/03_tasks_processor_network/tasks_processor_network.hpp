#ifndef BOOK_CHAPTER6_TASK_PROCESSOR_NETWORK_HPP
#define BOOK_CHAPTER6_TASK_PROCESSOR_NETWORK_HPP

#include "../02_tasks_processor_timers/tasks_processor_timers.hpp"

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/read.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <boost/lexical_cast.hpp>

struct connection_with_data {
    boost::asio::ip::tcp::socket socket_;
    std::string data_;

    explicit connection_with_data(boost::asio::io_service& ios)
        : socket_(ios) 
    {}

    void connect(const boost::asio::ip::tcp::endpoint& endpoint) {
        socket_.connect(endpoint);
    }

    void shutdown() {
        socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
        socket_.close();
    }
};

using connection_ptr = std::unique_ptr<connection_with_data>;


template <class T>
struct task_wrapped_with_connection {
private:
    connection_ptr c_;
    T task_unwrapped_;

public:
    explicit task_wrapped_with_connection(connection_ptr&& c, const T& f)
        : c_(std::move(c))
        , task_unwrapped_(f)
    {}

    task_wrapped_with_connection(task_wrapped_with_connection&&) = default;
    task_wrapped_with_connection& operator=(task_wrapped_with_connection&&) = default;

    task_wrapped_with_connection(const task_wrapped_with_connection&);
    task_wrapped_with_connection& operator=(const task_wrapped_with_connection&);

    template <class... Args>
    void operator()(Args&&... args) {
        // resetting interruption
        try {
            boost::this_thread::interruption_point();
        } catch(const boost::thread_interrupted&){}

        try {
            // Executing task
            task_unwrapped_(std::move(c_), std::forward<Args>(args)...);
        } catch (const std::exception& e) {
            std::cerr<< "Exception: " << e.what() << '\n';
        } catch (const boost::thread_interrupted&) {
            std::cerr<< "Thread interrupted\n";
        } catch (...) {
            std::cerr<< "Unknown exception\n";
        }
    }
};

template <class Functor>
void async_write_data(connection_ptr&& c, const Functor& f) {
    boost::asio::ip::tcp::socket& s = c->socket_;
    std::string& d = c->data_;

    boost::asio::async_write(
        s,
        boost::asio::buffer(d),
        task_wrapped_with_connection<Functor>(std::move(c), f)
    );
}

template <class Functor>
void async_read_data(connection_ptr&& c, const Functor& f, std::size_t at_least_bytes) {
    c->data_.resize(at_least_bytes);

    boost::asio::ip::tcp::socket& s = c->socket_;
    std::string& d = c->data_;
    char* p = (d.empty() ? 0 : &d[0]);

    boost::asio::async_read(
        s,
        boost::asio::mutable_buffers_1(p, d.size()),
        task_wrapped_with_connection<Functor>(std::move(c), f)
    );
}


template <class Functor>
void async_read_data_at_least(connection_ptr&& c, const Functor& f, std::size_t at_least_bytes, std::size_t at_most = 4095) {
    c->data_.resize(at_most);

    boost::asio::ip::tcp::socket& s = c->socket_;
    std::string& d = c->data_;
    char* p = (d.empty() ? 0 : &d[0]);

    boost::asio::async_read(
        s,
        boost::asio::mutable_buffers_1(p, d.size()),
        boost::asio::transfer_at_least(at_least_bytes),
        task_wrapped_with_connection<Functor>(std::move(c), f)
    );
}
namespace detail {
    class tcp_listener: public boost::enable_shared_from_this<tcp_listener> {
        typedef boost::asio::ip::tcp::acceptor acceptor_t;
        acceptor_t acceptor_;
        connection_ptr new_c_;
        boost::function<void(connection_ptr)> func_;
    public:
        template <class Functor>
        tcp_listener(
                boost::asio::io_service& io_service,
                unsigned short port,
                const Functor& task_unwrapped)
            : acceptor_(io_service,boost::asio::ip::tcp::endpoint(
                boost::asio::ip::tcp::v4(), port
            ))
            , func_(task_unwrapped)
        {}

        void stop() {
            acceptor_.close();
        }
        
        void push_task() {
            if (!acceptor_.is_open()) {
                return;
            }

            new_c_.reset(
                new connection_with_data(acceptor_.get_io_service())
            );

            boost::asio::ip::tcp::socket& s = new_c_->socket_;
            acceptor_.async_accept(s, boost::bind(
                &tcp_listener::handle_accept,
                this->shared_from_this(),
                boost::asio::placeholders::error
            ));
        }

    private:
        void handle_accept(const boost::system::error_code& error) {
            if (!error) {
                task_wrapped_with_connection< boost::function<void(connection_ptr)> >(
                    std::move(new_c_),
                    func_
                )(); // Running the task
            } else {
                std::cerr << error << '\n';
            }
            push_task();
        }
    }; // class tcp_listener
} // namespace detail

namespace tp_network {

class tasks_processor: public tp_timers::tasks_processor {
    typedef std::map<
        unsigned short,
        boost::shared_ptr<detail::tcp_listener>
    > listeners_map_t;

    static listeners_map_t& listeners() {
        static listeners_map_t l;
        return l;
    }

public:
    template <class Functor>
    static void add_listener(unsigned short port_num, const Functor& f) {
        listeners_map_t::const_iterator it = listeners().find(port_num);
        if (it != listeners().end()) {
            throw std::logic_error(
                "Such listener for port '" 
                + boost::lexical_cast<std::string>(port_num) 
                + "' already created"
            );
        }

        listeners()[port_num] = boost::make_shared<detail::tcp_listener>(boost::ref(get()), port_num, f);
        listeners()[port_num]->push_task(); // Start accepting
    }

    static void remove_listener(unsigned short port_num) {
        listeners_map_t::iterator it = listeners().find(port_num);
        if (it == listeners().end()) {
            throw std::logic_error(
                "No listener for port '" 
                + boost::lexical_cast<std::string>(port_num) 
                + "' created"
            );
        }

        (*it).second->stop();
        listeners().erase(it);
    }

    static connection_ptr create_connection(const char* addr, unsigned short port_num) {
        connection_ptr c( new connection_with_data(get()) );
        c->connect(boost::asio::ip::tcp::endpoint(
            boost::asio::ip::address_v4::from_string(addr),
            port_num
        ));

        return c;
    }
};

} // namespace tp_network

#endif // BOOK_CHAPTER6_TASK_PROCESSOR_NETWORK_HPP

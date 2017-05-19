#ifndef BOOK_CHAPTER6_TASK_PROCESSOR_NETWORK_HPP
#define BOOK_CHAPTER6_TASK_PROCESSOR_NETWORK_HPP

#include "../02_tasks_processor_timers/tasks_processor_timers.hpp"

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/read.hpp>
#include <boost/function.hpp>

#include <memory> // std::unique_ptr

struct connection_with_data {
    boost::asio::ip::tcp::socket socket;
    std::string data;

    explicit connection_with_data(boost::asio::io_service& ios)
        : socket(ios) 
    {}

    void shutdown() {
        if (!socket.is_open()) {
            return;
        }

        boost::system::error_code ignore;
        socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignore);
        socket.close(ignore);
    }

    ~connection_with_data() {
        shutdown();
    }
};

typedef std::unique_ptr<connection_with_data> connection_ptr;


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

    void operator()(const boost::system::error_code& error, std::size_t bytes_count) {
        const auto task = detail::make_task_wrapped([this, &error, bytes_count]() {
            this->c_->data.resize(bytes_count);
            this->task_unwrapped_(std::move(this->c_), error);
        });

        task();
    }
};

template <class Functor>
void async_write_data(connection_ptr&& c, const Functor& f) {
    boost::asio::ip::tcp::socket& s = c->socket;
    std::string& d = c->data;

    boost::asio::async_write(
        s,
        boost::asio::buffer(d),
        task_wrapped_with_connection<Functor>(std::move(c), f)
    );
}

template <class Functor>
void async_read_data(connection_ptr&& c, const Functor& f, std::size_t at_least_bytes) {
    c->data.resize(at_least_bytes);

    boost::asio::ip::tcp::socket& s = c->socket;
    std::string& d = c->data;
    char* p = (d.empty() ? 0 : &d[0]);

    boost::asio::async_read(
        s,
        boost::asio::mutable_buffers_1(p, d.size()),
        task_wrapped_with_connection<Functor>(std::move(c), f)
    );
}


template <class Functor>
void async_read_dataat_least(connection_ptr&& c, const Functor& f, std::size_t at_least_bytes, std::size_t at_most = 4095) {
    std::string& d = c->data;
    d.resize(at_most);
    char* p = (at_most == 0 ? 0 : &d[0]);

    boost::asio::ip::tcp::socket& s = c->socket;

    boost::asio::async_read(
        s,
        boost::asio::mutable_buffers_1(p, at_most),
        boost::asio::transfer_at_least(at_least_bytes),
        task_wrapped_with_connection<Functor>(std::move(c), f)
    );
}

namespace tp_network {

class tasks_processor: public tp_timers::tasks_processor {
    typedef boost::asio::ip::tcp::acceptor acceptor_t;
    typedef boost::function<void(connection_ptr, const boost::system::error_code&)> on_accpet_func_t;

    struct tcp_listener {
        acceptor_t              acceptor_;
        const on_accpet_func_t  func_;
        connection_ptr          new_c_;

        template <class Functor>
        tcp_listener(
                boost::asio::io_service& io_service,
                unsigned short port,
                const Functor& task_unwrapped)
            : acceptor_(io_service, boost::asio::ip::tcp::endpoint(
                boost::asio::ip::tcp::v4(), port
            ))
            , func_(task_unwrapped)
        {}
    };
    typedef std::unique_ptr<tcp_listener> listener_ptr;

    struct handle_accept {
        listener_ptr listener;

        explicit handle_accept(listener_ptr&& l)
            : listener(std::move(l))
        {}

        void operator()(const boost::system::error_code& error) {
            task_wrapped_with_connection<on_accpet_func_t> task(std::move(listener->new_c_), listener->func_);
            if (error) {
                std::cerr << error << '\n';
            }

            start_accepting_connection(std::move(listener));
            task(error, 0);
        }
    };

   static void start_accepting_connection(listener_ptr&& listener) {
        if (!listener->acceptor_.is_open()) {
            return;
        }

        listener->new_c_.reset(
            new connection_with_data(listener->acceptor_.get_io_service())
        );

        boost::asio::ip::tcp::socket& s = listener->new_c_->socket;
        acceptor_t& a = listener->acceptor_;
        a.async_accept(
            s,
            tasks_processor::handle_accept(std::move(listener))
        );
    }

public:
    template <class Functor>
    static void add_listener(unsigned short port_num, const Functor& f) {
        std::unique_ptr<tcp_listener> listener(
            new tcp_listener(get_ios(), port_num, f)
        );

        start_accepting_connection(std::move(listener));
    }

    static connection_ptr create_connection(const char* addr, unsigned short port_num) {
        connection_ptr c( new connection_with_data(get_ios()) );
        c->socket.connect(boost::asio::ip::tcp::endpoint(
            boost::asio::ip::address_v4::from_string(addr),
            port_num
        ));

        return c;
    }
};

} // namespace tp_network

#endif // BOOK_CHAPTER6_TASK_PROCESSOR_NETWORK_HPP

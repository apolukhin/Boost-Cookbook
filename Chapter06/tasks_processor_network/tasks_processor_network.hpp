#ifndef BOOK_CHAPTER6_TASK_PROCESSOR_NETWORK_HPP
#define BOOK_CHAPTER6_TASK_PROCESSOR_NETWORK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "../tasks_processor_timers/tasks_processor_timers.hpp"

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/read.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <boost/lexical_cast.hpp>

class tcp_connection_ptr {
    boost::shared_ptr<boost::asio::ip::tcp::socket> socket_;
public:
    explicit tcp_connection_ptr(
            boost::shared_ptr<boost::asio::ip::tcp::socket> socket)
        : socket_(socket) 
    {}

    explicit tcp_connection_ptr(
            boost::asio::io_service& ios,
            const boost::asio::ip::tcp::endpoint& endpoint)
        : socket_(boost::make_shared<boost::asio::ip::tcp::socket>(
             boost::ref(ios)
        ))
    {
        socket_->connect(endpoint);
    }
    
    template <class Functor>
    void async_write(
        const boost::asio::const_buffers_1& buf, const Functor& f) const
    {
        boost::asio::async_write(*socket_, buf, f);
    }

    template <class Functor>
    void async_write(
        const boost::asio::mutable_buffers_1& buf, const Functor& f) const
    {
        boost::asio::async_write(*socket_, buf, f);
    }

    template <class Functor>
    void async_read(
        const boost::asio::mutable_buffers_1& buf,
        const Functor& f,
        std::size_t at_least_bytes) const
    {
        boost::asio::async_read(
            *socket_, buf, boost::asio::transfer_at_least(at_least_bytes), f
        );
    }

    void shutdown() const {
        socket_->shutdown(boost::asio::ip::tcp::socket::shutdown_both);
        socket_->close();
    }
};

namespace detail {
    class tcp_listener: public boost::enable_shared_from_this<tcp_listener> {
        typedef boost::asio::ip::tcp::acceptor acceptor_t;
        acceptor_t acceptor_;
        boost::function<void(tcp_connection_ptr)> func_;
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

            typedef boost::asio::ip::tcp::socket socket_t;
            boost::shared_ptr<socket_t> socket = boost::make_shared<socket_t>(
                boost::ref(acceptor_.get_io_service())
            );
            
            acceptor_.async_accept(*socket, boost::bind(
                &tcp_listener::handle_accept,
                this->shared_from_this(),
                tcp_connection_ptr(socket),
                boost::asio::placeholders::error
            ));
        }

    private:
        void handle_accept(
                const tcp_connection_ptr& new_connection,
                const boost::system::error_code& error)
        {
            push_task();
            if (!error) {
                make_task_wrapped(boost::bind(func_, new_connection))
                    (); // Running the task
            } else {
                std::cerr << error << '\n';
            }
        }
    }; // class tcp_listener
} // namespace detail

namespace tp_network {

class tasks_processor: public tp_timers::tasks_processor {
    typedef std::map<
        unsigned short,
        boost::shared_ptr<detail::tcp_listener>
    > listeners_map_t;
    listeners_map_t listeners_;

public:
    static tasks_processor& get();

    template <class Functor>
    void add_listener(unsigned short port_num, const Functor& f) {
        listeners_map_t::const_iterator it = listeners_.find(port_num);
        if (it != listeners_.end()) {
            throw std::logic_error(
                "Such listener for port '" 
                + boost::lexical_cast<std::string>(port_num) 
                + "' already created"
            );
        }

        listeners_[port_num] = boost::make_shared<detail::tcp_listener>(boost::ref(ios_), port_num, f);
        listeners_[port_num]->push_task(); // Start accepting
    }

    void remove_listener(unsigned short port_num) {
        listeners_map_t::iterator it = listeners_.find(port_num);
        if (it == listeners_.end()) {
            throw std::logic_error(
                "No listener for port '" 
                + boost::lexical_cast<std::string>(port_num) 
                + "' created"
            );
        }

        (*it).second->stop();
        listeners_.erase(it);
    }

    tcp_connection_ptr create_connection(const char* addr, unsigned short port_num) {
        return tcp_connection_ptr(ios_, boost::asio::ip::tcp::endpoint(
                boost::asio::ip::address_v4::from_string(addr) , port_num
        ));
    }
};

} // namespace tp_network

#endif // BOOK_CHAPTER6_TASK_PROCESSOR_NETWORK_HPP

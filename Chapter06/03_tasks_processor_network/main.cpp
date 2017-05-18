
// Big part of code for this recipe
// in in this header:
#include "tasks_processor_network.hpp"
using namespace tp_network;

#include <boost/asio/read.hpp>
#include <boost/asio/write.hpp>

class authorizer {
public:
    static void on_connection_accpet(connection_ptr&& connection) {
        async_read_data_at_least(std::move(connection), &authorizer::on_data_recieve, 1);
    }

    static void on_data_recieve(connection_ptr&& connection, const boost::system::error_code& error, std::size_t bytes_recieved) {
        if (error) {
            std::cerr << "authorizer.on_data_recieve: error during recieving response: " << error << '\n';
            assert(false);
        }

        if (bytes_recieved == 0) {
            std::cerr << "authorizer.on_data_recieve: zero bytes recieved\n";
            assert(false);
        }

        // We have data in `message_` and now we can 
        // do some authorization...
        // ...
        connection->data_ = "OK";
        // ...

        // Now we have response in `message_` and it's time to send it
        async_write_data(std::move(connection), &authorizer::on_data_send);
    }

    static void on_data_send(connection_ptr&& connection, const boost::system::error_code& error, std::size_t bytes_send) {
        if (error) {
            std::cerr << "authorizer.on_data_send: error during sending response: " << error << '\n';
            assert(false);
        }

        connection->shutdown();
    }
};

bool g_authed = false;

void finsh_socket_auth_task(
        connection_ptr&& soc,
        const boost::system::error_code& err,
        std::size_t bytes_transfered)
{
    if (err && err != boost::asio::error::eof) {
        std::cerr << "finsh_socket_auth_task: Client error on recieve: " << err.message() << '\n';
        assert(false);
    }

    if (bytes_transfered != 2) {
        std::cerr << "finsh_socket_auth_task: wrong bytes count\n";
        assert(false);
    }

    if (soc->data_ != "OK") {
        std::cerr << "finsh_socket_auth_task: wrong response: " << soc->data_ << '\n';
        assert(false);
    }

    g_authed = true;
    soc->shutdown();
    tasks_processor::stop();
}

void recieve_auth_task(connection_ptr&& soc, const boost::system::error_code& err, std::size_t bytes_recieved) {
    if (err) {
        std::cerr << "recieve_auth_task: Client error on recieve: " << err.message() << '\n';
        assert(false);
    }

    async_read_data(
        std::move(soc),
        &finsh_socket_auth_task,
        2
    );
}

const unsigned short g_port_num = 65001;

void send_auth_task() {
    connection_ptr soc = tasks_processor::create_connection("127.0.0.1", g_port_num);
    soc->data_ = "auth_name";

    async_write_data(
        std::move(soc),
        &recieve_auth_task
    );
}

int main() {
    tasks_processor::run_delayed(boost::posix_time::seconds(1), &send_auth_task);
    tasks_processor::add_listener(g_port_num, &authorizer::on_connection_accpet);
    assert(!g_authed);

    tasks_processor::start();
    assert(g_authed);
}

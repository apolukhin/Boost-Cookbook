// Big part of code for this recipe
// in in this header:
#include "tasks_processor_network.hpp"
using namespace tp_network;

class authorizer {
public:
    static void on_connection_accpet(connection_ptr&& connection, const boost::system::error_code& error) {
        assert(!error);
        async_read_dataat_least(std::move(connection), &authorizer::on_datarecieve, 1);
    }

    static void on_datarecieve(connection_ptr&& connection, const boost::system::error_code& error) {
        if (error) {
            std::cerr << "authorizer.on_datarecieve: error during recieving response: " << error << '\n';
            assert(false);
        }

        if (connection->data.size() == 0) {
            std::cerr << "authorizer.on_datarecieve: zero bytes recieved\n";
            assert(false);
        }

        assert(connection->data == "auth_name");

        // We have data and now we can 
        // do some authorization.
        // ...
        connection->data = "OK";
        // ...

        // Now we have response in `connection->data` and it's time to send it.
        async_write_data(std::move(connection), &authorizer::on_datasend);
    }

    static void on_datasend(connection_ptr&& connection, const boost::system::error_code& error) {
        if (error) {
            std::cerr << "authorizer.on_datasend: error during sending response: " << error << '\n';
            assert(false);
        }

        connection->shutdown();
    }
};

bool g_authed = false;

void finsh_socket_auth_task(
        connection_ptr&& soc,
        const boost::system::error_code& err)
{
    if (err && err != boost::asio::error::eof) {
        std::cerr << "finsh_socket_auth_task: Client error on recieve: " << err.message() << '\n';
        assert(false);
    }

    if (soc->data.size() != 2) {
        std::cerr << "finsh_socket_auth_task: wrong bytes count\n";
        assert(false);
    }

    if (soc->data != "OK") {
        std::cerr << "finsh_socket_auth_task: wrong response: " << soc->data << '\n';
        assert(false);
    }

    g_authed = true;
    soc->shutdown();
    tasks_processor::stop();
}

void recieve_auth_task(connection_ptr&& soc, const boost::system::error_code& err) {
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
    soc->data = "auth_name";

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

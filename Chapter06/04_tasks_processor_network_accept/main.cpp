// Big part of code for this recipe
// in in this header:
#include "tasks_processor_network_accept.hpp"
#include "../03_tasks_processor_network_client/client.hpp"
using namespace tp_network;

class authorizer {
public:
    static void on_connection_accpet(
        connection_ptr&& connection,
        const boost::system::error_code& error)
    {
        if (error) return;
        async_read_data_at_least(std::move(connection), &authorizer::on_datarecieve, 1, 1024);
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


int main() {
    tasks_processor::run_delayed(boost::posix_time::seconds(1), &send_auth);
    tasks_processor::add_listener(g_port_num, &authorizer::on_connection_accpet);
    assert(!g_authed);

    tasks_processor::start();
    assert(g_authed);
}

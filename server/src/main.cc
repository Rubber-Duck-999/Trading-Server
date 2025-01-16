#include "Server.h"

int main() {
    BOOST_LOG_TRIVIAL(info) << "Start TCP Trading Server";
    // Setup TCP server
    Server server = Server();

    OrderBook orderBook = OrderBook("ABC ");

    // Setup clients
    if (!server.SetupConnections()) {
        BOOST_LOG_TRIVIAL(error) << "Exiting app";
        return 1;
    }

    // Run AcceptConnections in a separate thread
    boost::thread accept_thread([&server, &orderBook]() {
        server.AcceptConnections(orderBook);
    });

    // Main thread remains free
    BOOST_LOG_TRIVIAL(info) << "Main application thread";

    accept_thread.join();

    return 0;
}
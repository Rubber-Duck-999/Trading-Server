#include "Server.h"

int main() {
    // Create an order book for the asset "ABC"
    OrderBook orderBook = OrderBook("ABC ");

    // Setup TCP server
    Server server = Server();

    // Setup clients
    if (!server.SetupConnections()) {
        BOOST_LOG_TRIVIAL(error) << "Exiting app";
        return 1;
    }

    // Acept TCP client connections and publish order book
    if(!server.AcceptConnections(orderBook)) {
        BOOST_LOG_TRIVIAL(error) << "Exiting app";
        return 1;
    }
    return 0;
}
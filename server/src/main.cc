#include "Server.h"

int main() {
    // Setup TCP server
    Server server = Server();

    OrderBook orderBook = OrderBook("ABC ");

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
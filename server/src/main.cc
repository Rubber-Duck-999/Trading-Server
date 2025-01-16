#include "server.h"

int main() {
    Server server = Server();
    // Setup clients
    if (!server.SetupConnections()) {
        BOOST_LOG_TRIVIAL(error) << "Exiting app";
        return 1;
    }
    if(!server.AcceptConnections()) {
        BOOST_LOG_TRIVIAL(error) << "Exiting app";
        return 1;
    }
    return 0;
}
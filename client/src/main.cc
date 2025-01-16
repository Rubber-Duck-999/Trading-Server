#include "Client.h"

int main() {
    BOOST_LOG_TRIVIAL(info) << "Start TCP Trading Client";
    Client client = Client();
    // Setup clients
    if (!client.SetupConnections()) {
        BOOST_LOG_TRIVIAL(error) << "Exiting app";
        return 1;
    }

    if(!client.CreateConnections()) {
        BOOST_LOG_TRIVIAL(error) << "Exiting app";
        return 1;
    }
    return 0;
}
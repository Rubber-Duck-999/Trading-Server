#include "Client.h"
#include <iostream>
#include <stdexcept>

int main(int argc, char* argv[]) {
    BOOST_LOG_TRIVIAL(info) << "Start TCP Trading Client";

    if (argc != 3) {
        BOOST_LOG_TRIVIAL(error) << "Usage: " << argv[0] << " <cumulative_quantity> <number_of_ticks>";
        return 1;
    }

    int cumulative_quantity, number_of_ticks;
    try {
        // Catt the input strings to ints
        cumulative_quantity = std::stoi(argv[1]);
        number_of_ticks = std::stoi(argv[2]);
    } catch (const std::invalid_argument& e) {
        BOOST_LOG_TRIVIAL(error) << "Invalid arguments provided. Both inputs must be integers.";
        return 1;
    } catch (const std::out_of_range& e) {
        BOOST_LOG_TRIVIAL(error) << "Input integers are out of range.";
        return 1;
    }

    BOOST_LOG_TRIVIAL(info) << "Q: " << cumulative_quantity << " and N: " << number_of_ticks;

    Client client = Client();
    // Setup clients
    if (!client.SetupConnections()) {
        BOOST_LOG_TRIVIAL(error) << "Exiting app";
        return 1;
    }

    if (!client.CreateConnections(cumulative_quantity, number_of_ticks)) {
        BOOST_LOG_TRIVIAL(error) << "Exiting app";
        return 1;
    }

    return 0;
}

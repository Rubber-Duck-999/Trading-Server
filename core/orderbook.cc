#include "OrderBook.h"

OrderBook::OrderBook(const std::string& ticker) {
    ticker_ = ticker;
    order_book_data_ = ";";
    bid_prices_ = { "     ", "     ", "     ", "     ", "     " };
    ask_prices_ = { "     ", "     ", "     ", "     ", "     " };
    bid_quantities_ = { "    ", "    ", "    ", "    ", "    " };
    ask_quantities_ = { "    ", "    ", "    ", "    ", "    " };
    InitializeValues();
}

std::string OrderBook::GeneratePrice(int max, int min) {
    int price = rand() % (max - min + 1) + min;
    return std::to_string(price);
}

// Generate random quantity for order book
std::string OrderBook::GenerateQuantity(int max, int min) {
    int quantity = rand() % (max - min + 1) + min;
    return std::to_string(quantity);
}

void OrderBook::InitializeValues() {
    for (int i = 0; i < 5; ++i) {
        bid_prices_[i] = GeneratePrice(150, 200);
        ask_prices_[i] = GeneratePrice(200, 150);
        bid_quantities_[i] = GenerateQuantity(20, 1);
        ask_quantities_[i] = GenerateQuantity(20, 1);
    }
}

std::string OrderBook::GetOrderBookData() {
    // Convert to string for publishing
    std::ostringstream orderBookStream;

    orderBookStream << "Ticker: " << ticker_ << "\n";

    orderBookStream << "Bid Prices: ";
    for (const auto& price : bid_prices_) {
        orderBookStream << price << " ";
    }
    orderBookStream << "\n";

    orderBookStream << "Ask Prices: ";
    for (const auto& price : ask_prices_) {
        orderBookStream << price << " ";
    }
    orderBookStream << "\n";

    orderBookStream << "Bid Quantities: ";
    for (const auto& qty : bid_quantities_) {
        orderBookStream << qty << " ";
    }
    orderBookStream << "\n";

    orderBookStream << "Ask Quantities: ";
    for (const auto& qty : ask_quantities_) {
        orderBookStream << qty << " ";
    }
    orderBookStream << "\n";

    order_book_data_ =  orderBookStream.str();
    BOOST_LOG_TRIVIAL(debug) << "Publish order book: " << order_book_data_;
    return order_book_data_;
}

template <size_t N>
std::array<std::string, N> ParseArray(const std::string& values) {
    std::array<std::string, N> result;
    std::istringstream valueStream(values);
    for (size_t i = 0; i < N; ++i) {
        if (!(valueStream >> result[i])) {
            result[i] = "";
        }
    }
    return result;
}

void OrderBook::ParseOrderBookData(const std::string& orderBookString) {
    std::istringstream stream(orderBookString);
    std::string line;
    try {
        while (std::getline(stream, line)) {
            std::istringstream lineStream(line);
            std::string key;

            // Extract the key (e.g., "Ticker", "Bid Prices")
            if (std::getline(lineStream, key, ':')) {
                std::string values;
                std::getline(lineStream, values);
                values = values.substr(1);

                if (key == "Ticker") {
                    ticker_ = values;
                } else if (key == "Bid Prices") {
                    bid_prices_ = ParseArray<5>(values);
                } else if (key == "Ask Prices") {
                    ask_prices_ = ParseArray<5>(values);
                } else if (key == "Bid Quantities") {
                    bid_quantities_ = ParseArray<5>(values);
                } else if (key == "Ask Quantities") {
                    ask_quantities_ = ParseArray<5>(values);
                }
            }
        }
    } catch (const std::exception& e) {
        BOOST_LOG_TRIVIAL(error) << "Error parsing order book data: " << e.what();
    }
}
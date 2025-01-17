#include "OrderBook.h"

OrderBook::OrderBook(const std::string& ticker) {
    ticker_ = ticker;
    order_book_data_ = "";
    bid_prices_ = { "     ", "     ", "     ", "     ", "     " };
    ask_prices_ = { "     ", "     ", "     ", "     ", "     " };
    bid_quantities_ = { "    ", "    ", "    ", "    ", "    " };
    ask_quantities_ = { "    ", "    ", "    ", "    ", "    " };
    InitializeValues();
}

void OrderBook::InitializeValues() {
    for (int i = 0; i < 5; ++i) {
        bid_prices_[i] = GeneratePrice(150, 100);
        ask_prices_[i] = GeneratePrice(200, 150);
        bid_quantities_[i] = GenerateQuantity(20, 1);
        ask_quantities_[i] = GenerateQuantity(20, 1);
    }
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

std::string OrderBook::GetOrderBookData() {
    // Convert to string for publishing
    std::ostringstream orderBookStream;

    orderBookStream << "Ticker: " << ticker_ << "\n";

    orderBookStream << "Bid Prices: ";
    for (const auto& price : bid_prices_) {
        orderBookStream << std::setw(5) << price << " ";
    }
    orderBookStream << "\n";

    orderBookStream << "Ask Prices: ";
    for (const auto& price : ask_prices_) {
        orderBookStream << std::setw(5) << price << " ";
    }
    orderBookStream << "\n";

    orderBookStream << "Bid Quantities: ";
    for (const auto& qty : bid_quantities_) {
        orderBookStream << std::setw(4) << qty << " ";
    }
    orderBookStream << "\n";

    orderBookStream << "Ask Quantities: ";
    for (const auto& qty : ask_quantities_) {
        orderBookStream << std::setw(4) << qty << " ";
    }
    orderBookStream << "\n";

    order_book_data_ =  orderBookStream.str();
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
}

void OrderBook::DetermineBidOrder() {
    bid_sum_ = 0;
    best_bid_ = 0;
    // Logic is if you have { 3, 3, 2 } for bid quantities
    // at prices { 100, 90, 50 }
    // and a q of 4 your best bid is 90
    for (size_t i = 0; i < bid_prices_.size(); ++i) {
        bid_sum_ += std::stoi(bid_quantities_[i]);
        if (bid_sum_ >= cumulative_quantity_) {
            best_bid_ = std::stoi(bid_prices_[i]);
            bid_sum_ = cumulative_quantity_;
            break;
        }
    }
    best_bid_ = best_bid_ - number_of_ticks_;
    BOOST_LOG_TRIVIAL(info) << "Placing bid order at: " << best_bid_;
}

void OrderBook::DetermineAskOrder() {
    ask_sum_ = 0;
    best_ask_ = 0;
    for (size_t i = 0; i < ask_prices_.size(); ++i) {
        ask_sum_ += std::stoi(ask_quantities_[i]);
        if (ask_sum_ >= cumulative_quantity_) {
            best_ask_ = std::stoi(ask_prices_[i]);
            ask_sum_ = cumulative_quantity_;
            break;
        }
    }
    best_ask_ = best_ask_ - number_of_ticks_;
    BOOST_LOG_TRIVIAL(info) << "Placing ask order at: " << best_ask_;
}
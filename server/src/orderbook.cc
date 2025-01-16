#include "OrderBook.h"

OrderBook::OrderBook(const std::string& ticker) {
    ticker_ = ticker;
    order_book_data_ = ";";
    bid_prices_ = { "     ", "     ", "     ", "     ", "     " };
    ask_prices_ = { "     ", "     ", "     ", "     ", "     " };
    bid_quantities_ = { "    ", "    ", "    ", "    ", "    " };
    ask_quantities_ = { "    ", "    ", "    ", "    ", "    " };
}

std::string OrderBook::GeneratePrice(int min, int max) {
    int price = rand() % (max - min + 1) + min;
    return std::to_string(price);
}

// Generate random quantity for order book
std::string OrderBook::GenerateQuantity(int min, int max) {
    int quantity = rand() % (max - min + 1) + min;
    return std::to_string(quantity);
}

std::string OrderBook::GetOrderBookData() {
    // Temp for now
    for (int i = 0; i < 5; ++i) {
        bid_prices_[i] = GeneratePrice(100, 150);
        ask_prices_[i] = GeneratePrice(150, 200);
        bid_quantities_[i] = GenerateQuantity(1, 20);
        ask_quantities_[i] = GenerateQuantity(1, 20);
    }
    
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
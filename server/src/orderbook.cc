#include "OrderBook.h"

OrderBook::OrderBook(const std::string& ticker) {
    ticker_ = ticker;
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

void OrderBook::GenerateRandomData() {
    for (int i = 0; i < 5; ++i) {
        bid_prices_[i] = GeneratePrice(100, 150);
        ask_prices_[i] = GeneratePrice(150, 200);
        bid_quantities_[i] = GenerateQuantity(1, 20);
        ask_quantities_[i] = GenerateQuantity(1, 20);
    }
}
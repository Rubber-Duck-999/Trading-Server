#ifndef ORDERBOOK_h
#define ORDERBOOK_h

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include "constants.h"
#include <arpa/inet.h>
#include "boost/log/trivial.hpp"
#include "boost/log/utility/setup.hpp"
#include <boost/log/utility/setup/common_attributes.hpp>
#include <iomanip>

class OrderBook {
private:
    std::string ticker_;
    std::array<std::string, 5> bid_prices_;
    std::array<std::string, 5> ask_prices_;
    std::array<std::string, 5> bid_quantities_;
    std::array<std::string, 5> ask_quantities_;
    std::string order_book_data_;
    // Client points
    int cumulative_quantity_;
    int number_of_ticks_;
    std::string best_bid_;
    std::string best_ask_;
    // Generate random prices and quantities
    std::string GeneratePrice(int min, int max);
    std::string GenerateQuantity(int min, int max);
    // Random initializer
    void InitializeValues();
    void DetermineBestBid();
public:
    OrderBook(const std::string& ticker);
    // GettTers
    std::string GetTicker() const {
        return ticker_;
    };
    std::array<std::string, 5> GetBidPrices() const {
        return bid_prices_;
    };
    std::array<std::string, 5> GetAskPrices() const {
        return ask_prices_;
    };
    std::array<std::string, 5> GetBidQuantities() const {
        return bid_quantities_;
    };
    std::array<std::string, 5> GetAskQuantities() const {
        return ask_quantities_;
    };
    std::string GetBestBid() const {
        return best_bid_;
    }
    std::string GetBestAsk() const {
        return best_ask_;
    };
    // Setters
    void SetBidPrices(const std::array<std::string, 5>& bidPrices) {
        bid_prices_ = bidPrices;
    };
    void SetAskPrices(const std::array<std::string, 5>& askPrices) {
        ask_prices_ = askPrices;
    };
    void SetBidQuantities(const std::array<std::string, 5>& bidQuantities) {
        bid_quantities_ = bidQuantities;
    };
    void SetAskQuantities(const std::array<std::string, 5>& askQuantities) {
        ask_quantities_ = askQuantities;
    };
    std::string GetOrderBookData();
    void ParseOrderBookData(const std::string& orderBookString);
    void DetermineOrder();
};

#endif 	/* ORDERBOOK_H */
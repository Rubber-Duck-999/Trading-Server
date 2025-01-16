#ifndef ORDERBOOK_h
#define ORDERBOOK_h

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include "logging.h"
#include "constants.h"
#include <arpa/inet.h>


class OrderBook {
private:
    std::string ticker_;
    std::array<std::string, 5> bid_prices_;
    std::array<std::string, 5> ask_prices_;
    std::array<std::string, 5> bid_quantities_;
    std::array<std::string, 5> ask_quantities_;
    // Generate random prices and quantities
    std::string GeneratePrice(int min, int max);
    std::string GenerateQuantity(int min, int max);
public:
    OrderBook(const std::string& ticker);

    // GettTers
    std::string GetTicker() const;
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

    // Method to generate random data for the order book
    void GenerateRandomData();
};

#endif 	/* ORDERBOOK_H */
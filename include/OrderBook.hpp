#pragma once
#include "Types.hpp"
#include <map>
#include <vector>
#include <functional>

namespace quant {
    class IOrderBook {
        public:
            virtual ~IOrderBook() = default;
            virtual void update(Side side, double price, int quantity) = 0;
            virtual std::vector<OrderBookLevel> getTopLevels(Side side, int depth) const = 0;
    };

    class OrderBook : public IOrderBook {
        private:
            // std::map is sorted by key.
            // For Asks: Default (ascending) is perfect (cheapest first).
            std::map<double, int> asks;
            // For Bids: We need descending (highest first).
            // We use std::greater<double> as a template argument.
            std::map<double, int, std::greater<double>> bids;

        public:
            void update(Side side, double price, int quantity) override;
            std::vector<OrderBookLevel> getTopLevels(Side side, int depth) const override;
    };
}
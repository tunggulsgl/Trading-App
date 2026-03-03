#pragma once
#include "OrderBook.hpp"
#include "Strategy.hpp"
#include <RiskManager.hpp>
#include <vector>

namespace quant {
    class MarketSimulator {
        private:
            IOrderBook &orderBook;
            IStrategy &strategy;
            RiskManager &risk;

        public:
            MarketSimulator(IOrderBook &o, IStrategy &s, RiskManager &r)
                : orderBook(o), strategy(s), risk(r) {}

            // Simulates the market by processing a list of ticks
            void run(const std::vector<Tick> &ticks);
    };
}
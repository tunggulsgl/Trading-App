#pragma once
#include <Strategy.hpp>

namespace quant {
    class SpreadStrategy : public IStrategy {
        private:
            double threshold;

        public:
            explicit SpreadStrategy(double threshold) : threshold(threshold) {}

            std::optional<Order> onMarketUpdate(const std::string &ticker, const IOrderBook &book) override;
    };

}
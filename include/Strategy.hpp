#pragma once
#include "Types.hpp"
#include "OrderBook.hpp"
#include <optional>

namespace quant {
    class IStrategy {
        public:
        virtual ~IStrategy() = default;
        // The "Decision" method
        virtual std::optional<Order> onMarketUpdate(const std::string &ticker, const IOrderBook &book) = 0;
    };
}
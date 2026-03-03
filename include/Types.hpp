#pragma once
#include <string>
#include <chrono>

namespace quant {
    using Timestamp = std::chrono::time_point<std::chrono::high_resolution_clock>;

    enum class Side {BUY, SELL};

    enum class RiskResult {APPROVED, REJECTED_POSITION_LIMIT, REJECTED_PRICE_OUT_OF_RANGE};

    struct Tick {
        std::string ticker;
        double price;
        int quantity;
        Timestamp timestamp;
    };

    struct OrderBookLevel {
        double price;
        int quantity;
    };

    struct Order {
        std::string ticker;
        Side side;
        double price;
        int quantity;
    };
}
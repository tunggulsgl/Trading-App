#pragma once
#include <string>
#include <chrono>

namespace quant {
    using Timestamp = std::chrono::time_point<std::chrono::high_resolution_clock>;

    enum class Side {BUY, SELL};

    enum class RiskResult {APPROVED, REJECTED_POSITION_LIMIT, REJECTED_PRICE_OUT_OF_RANGE};

    struct Tick {
        std::string ticker;
        Side side;
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

    // This "teaches" C++ how to print the Side enum
    inline std::ostream& operator<<(std::ostream& os, const Side& side) {
        switch (side) {
            case Side::BUY:  return os << "BUY";
            case Side::SELL: return os << "SELL";
            default:         return os << "UNKNOWN";
        }
    }
}
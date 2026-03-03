#pragma once
#include "Types.hpp"
#include <atomic>

namespace quant {
    class RiskManager {
        private:
            int maxPosition;
            std::atomic<int> currentPosition {0};

        public:
            explicit RiskManager(int maxPosition) : maxPosition(maxPosition) {}

            // Check if an order is safe to send
            RiskResult validateOrder(const Order &order);

            // Update position after a successful trade
            void updatePosition(int quantity);

            int getCurrentPosition() const {
                return currentPosition.load();
            }
    };
}
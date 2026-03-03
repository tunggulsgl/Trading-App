#include "RiskManager.hpp"

namespace quant {

    RiskResult RiskManager::validateOrder(const Order &order) {
        // If it's a buy, check if we will exceed the limit
        if (order.side == Side::BUY) {
            if (currentPosition.load() + order.quantity > maxPosition) {
                return RiskResult::REJECTED_POSITION_LIMIT;
            }
        }

        // We could also check for "Fat Finger" errors (prices too far from the market)
        if (order.price <= 0) return RiskResult::REJECTED_PRICE_OUT_OF_RANGE;

        return RiskResult::APPROVED;
    }

    void RiskManager::updatePosition(int quantity) {
        // Atomic addition (no mutex needed)
        currentPosition.fetch_add(quantity);
    }
}

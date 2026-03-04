#include "OrderBook.hpp"
#include <algorithm>
#include <iostream>

namespace quant {
    void OrderBook::update(Side side, double price, int quantity) {
        // std::cout << side << " " << price << " " << quantity << std::endl;
        if (side == Side::BUY) {
            if (quantity == 0) {
                bids.erase(price);
            } else {
                bids[price] = quantity;
            }
        } else {
            if (quantity == 0) {
                asks.erase(price);
            } else {
                asks[price] = quantity;
            }
        }
    }

    std::vector<OrderBookLevel> OrderBook::getTopLevels(Side side, int depth) const {
        int count = 0;
        std::vector<OrderBookLevel> levels;

        if (side == Side::BUY) {
            for (const auto& [price, quantity] : bids) {
                if (count >= depth) break;

                levels.push_back({price, quantity});
                count++;
            }
        } else {
            for (const auto& [price, quantity] : asks) {
                if (count >= depth) break;

                levels.push_back({price, quantity});
                count++;
            }
        }

        return levels;
    }
}

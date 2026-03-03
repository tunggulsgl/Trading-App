#include "MarketSimulator.hpp"
#include <iostream>

namespace quant {
    void MarketSimulator::run(const std::vector<Tick> &ticks) {
        std::cout << "[SIMULATOR] Starting Playback of " << ticks.size() << " ticks..." << std::endl;

        for (const Tick &tick : ticks) {
            // 1. Update the Book
            // Note: For simplicity, we assume the CSV 'side' is the side of the order
            // In a real system, we'd need to know if the tick is a Buy or Sell order.
            // Let's assume price > 0 for this demo.

            Side side = (tick.quantity % 2 == 0) ? Side::SELL : Side::BUY;
            orderBook.update(side, tick.price, tick.quantity);

            // 2. Check strategy
            auto order = strategy.onMarketUpdate(tick.ticker, orderBook);

            if (order) {
                std::cout << "[STRATEGY] Alert on " << tick.ticker << " @ " << tick.price << std::endl;

                // 3. Risk check
                if (risk.validateOrder(*order) == RiskResult::APPROVED) {
                    std::cout << ">>> EXECUTION: " << (order->side == Side::BUY ? "BUY " : "SELL ")
                              << order->quantity << " shares." << std::endl;
                    risk.updatePosition(order->quantity);
                }
            }
        }

        std::cout << "[SIMULATOR] Playback Complete." << std::endl;
    }
}
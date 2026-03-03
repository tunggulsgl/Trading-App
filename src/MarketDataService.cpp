#include "MarketDataService.hpp"

namespace quant {
    void MarketDataService::addTick(const std::string &ticker) {
        // This is safe to do at startup (Cold Path)
        if (priceCache.find(ticker) == priceCache.end()) {
            priceCache[ticker] = std::make_unique<std::atomic<double>>(0.0);
        }
    }

    void MarketDataService::onTick(const Tick &tick) {
        // We assume the ticker was added during Cold Path.
        // No map insertion here = No reallocations = High Speed.
        auto it = priceCache.find(tick.ticker);
        if (it != priceCache.end()) {
            it -> second -> store(tick.price, std::memory_order_relaxed);
        }
    }

    std::optional<double> MarketDataService::getLastPrice(const std::string &ticker) const {
        auto it = priceCache.find(ticker);
        if (it != priceCache.end()) {
            return it -> second -> load(std::memory_order_relaxed);
        }
        return std::nullopt;
    }
}

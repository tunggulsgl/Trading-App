#pragma once
#include "Types.hpp"
#include <unordered_map>
#include <memory>
#include <atomic>
#include <optional>

namespace quant {
    class IMarketDataService {
    public:
        virtual ~IMarketDataService() = default;
        virtual void onTick(const Tick &tick) = 0;
        virtual std::optional<double> getLastPrice(const std::string &ticker) const = 0;
    };

    class MarketDataService : public IMarketDataService {
    private:
        // We pre-allocate atomics to avoid Mutexes during the "Hot Path"
        // Key: Ticker Symbol, Value: Atomic price
        std::unordered_map<std::string, std::unique_ptr<std::atomic<double>>> priceCache;

    public:
        // COLD PATH: Used at startup to "warm up" the memory
        void addTick(const std::string &ticker);
        // HOT PATH: Called millions of times. Must be lock-free.
        void onTick(const Tick &tick) override;
        // Thread-safe read
        std::optional<double> getLastPrice(const std::string &ticker) const override;
    };
}
#include "OrderBook.hpp"
#include "SpreadStrategy.hpp"
#include "RiskManager.hpp"
#include "CSVReader.hpp"
#include "ThreadSafeQueue.hpp"
#include <iostream>
#include <thread>

using namespace quant;

int main() {
    OrderBook appleBook;
    SpreadStrategy strategy(0.05);
    RiskManager risk(1000);
    ThreadSafeQueue<Tick> tickQueue;

    // Load data
    auto ticks = CSVReader::loadTicks("market_data.csv");

    // --- THREAD 1: THE CONSUMER (The "Brain") ---
    // This thread waits for ticks and processes them.
    std::jthread consumerThread([&]() {
        Tick t;
        while (tickQueue.pop(t)) {
            //Side side = (t.quantity % 2 == 0) ? Side::SELL : Side::BUY;
            //appleBook.update(side, t.price, t.quantity);
            appleBook.update(t.side, t.price, t.quantity);

            auto order = strategy.onMarketUpdate(t.ticker, appleBook);

            if (order && risk.validateOrder(*order) == RiskResult::APPROVED) {
                std::cout << "[EXECUTION] Thread ID: " << std::this_thread::get_id()
                          << " | BUY " << order->ticker << " @ " << order->price << std::endl;
                risk.updatePosition(order->quantity);
            }
        }
    });

    // --- THREAD 2: THE PRODUCER (The "Market Feed") ---
    std::cout << "[FEED] Starting data stream from Thread: " << std::this_thread::get_id() << std::endl;
    for (const auto& tick : ticks) {
        tickQueue.push(tick);
        // Simulate real-world delay between market events
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    tickQueue.setFinished(); // Tell the consumer we are done

    return 0; // jthread automatically joins here
}
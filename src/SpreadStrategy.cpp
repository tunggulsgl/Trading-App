#include <SpreadStrategy.hpp>

namespace quant {
    std::optional<Order> SpreadStrategy::onMarketUpdate(const std::string &ticker, const IOrderBook &book) {
        // Get the best bid and ask
        auto topBids = book.getTopLevels(Side::BUY, 1);
        auto topAsks = book.getTopLevels(Side::SELL, 1);

        // We need both side to calculate spread
        if (topBids.empty() || topAsks.empty()) return std::nullopt;

        double bestBid = topBids[0].price;
        double bestAsk = topAsks[0].price;
        double currentSpread = bestAsk - bestBid;

        // If spread is tight, place an orders
        if (currentSpread < threshold) {
            return Order({ticker, Side::BUY, bestBid, 100});
        }

        return std::nullopt;
    }
}

#include <gtest/gtest.h>
#include "OrderBook.hpp"

using namespace quant;

class OrderBookTest : public ::testing::Test {
protected:
    OrderBook book;
};

// Test 1: Ensure Bids are sorted Highest to Lowest
TEST_F(OrderBookTest, BidsAreSortedByPriceTimePriority) {
    book.update(Side::BUY, 100.0, 10);
    book.update(Side::BUY, 105.0, 10); // Higher price
    book.update(Side::BUY, 102.0, 10);

    auto topBids = book.getTopLevels(Side::BUY, 3);

    ASSERT_EQ(topBids.size(), 3);
    EXPECT_DOUBLE_EQ(topBids[0].price, 105.0); // Highest first
    EXPECT_DOUBLE_EQ(topBids[1].price, 102.0);
    EXPECT_DOUBLE_EQ(topBids[2].price, 100.0);
}

// Test 2: Ensure quantity of 0 removes a price level
TEST_F(OrderBookTest, QuantityZeroRemovesLevel) {
    book.update(Side::SELL, 200.0, 50);
    book.update(Side::SELL, 200.0, 0); // Remove it

    auto topAsks = book.getTopLevels(Side::SELL, 1);
    EXPECT_TRUE(topAsks.empty());
}
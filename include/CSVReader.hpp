#pragma once
#include "Types.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

namespace quant {
    class CSVReader {
        public:
            // Read the CSV and return the vector of Tick
            static std::vector<Tick> loadTicks(const std::string &fileName) {
                std::vector<Tick> ticks;
                std::ifstream file(fileName);
                std::string line;

                // Skip the header row
                if (!std::getline(file, line)) return ticks;

                while (std::getline(file, line)) {
                    std::stringstream ss(line);
                    std::string ticker, sideStr, priceStr, qtyStr;

                    // Parse csv columns
                    std::getline(ss, ticker, ',');
                    std::getline(ss, sideStr, ',');
                    std::getline(ss, priceStr, ',');
                    std::getline(ss, qtyStr, ',');

                    Tick tick;
                    tick.ticker = ticker;
                    tick.price = std::stod(priceStr);
                    tick.quantity = std::stoi(qtyStr);
                    tick.timestamp = std::chrono::high_resolution_clock::now();

                    // REAL PARSING LOGIC:
                    if (sideStr == "BUY") {
                        tick.side = Side::BUY;
                    } else {
                        tick.side = Side::SELL;
                    }

                    ticks.push_back(tick);
                }

                return ticks;
            }
    };
}
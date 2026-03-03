# QuantEngine: High-Frequency Trading Framework

A high-performance, multithreaded trading engine framework developed in **C++20**. This project demonstrates the core components of a quantitative trading system, focusing on low-latency data structures, thread-safe message passing, and decoupled service architecture.



## 1. Architecture Overview
The system follows a **Producer-Consumer** pattern to decouple market data ingestion from strategy execution.

- **Market Data Service:** A lock-free price cache using `std::atomic` to ensure high-speed updates without mutex contention.
- **Order Book:** Implements Price-Time Priority using sorted maps (`std::map` with custom comparators) to maintain Bid/Ask depth with $O(\log N)$ complexity.
- **Strategy Engine:** A modular interface for "Alpha" generation. Includes a sample `SpreadStrategy` that triggers orders based on bid-ask spread compression.
- **Risk Manager:** An independent safety gatekeeper utilizing atomic position tracking to enforce exposure limits.
- **Market Simulator:** A backtesting utility that streams historical "Tape" data from CSV files into the live engine.

## 2. Key Engineering Features
- **Low Latency:** Separation of "Hot Path" (Execution) and "Cold Path" (Initialization) to minimize runtime overhead.
- **Thread Safety:** Custom `ThreadSafeQueue` utilizing `std::condition_variable` and `std::mutex` for efficient inter-thread communication.
- **Memory Management:** Zero-copy principles using `std::move` semantics and RAII through `std::unique_ptr`.
- **Modern C++20:** Leverages `std::jthread` for safe thread lifecycle management and `std::optional` for deterministic error handling.

## 3. Project Structure
```text
TradingApp/
├── include/           # Header-only interfaces and contracts
├── src/               # Implementation of core trading logic
├── apps/              # Main entry point for the multithreaded engine
├── market_data.csv    # Sample historical market data
└── CMakeLists.txt     # Cross-platform build configuration

cmake_minimum_required(VERSION 3.20)
project(TradingApp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. CORE CONFIGURATION
include_directories(include)

# 2. THE PRODUCTION LIBRARY (Logic only, NO test files here!)
add_library(QuantLib
        src/MarketDataService.cpp
        src/OrderBook.cpp
        src/SpreadStrategy.cpp
        src/RiskManager.cpp
        src/MarketSimulator.cpp
)

# 3. THE MAIN TRADING APP
add_executable(TradingApp apps/main.cpp)
target_link_libraries(TradingApp QuantLib)

# Copy CSV to build directory for the app to find it
configure_file(
        ${CMAKE_SOURCE_DIR}/market_data.csv
        ${CMAKE_CURRENT_BINARY_DIR}/market_data.csv
        COPYONLY
)

# 4. UNIT TESTING SECTION (GTest)
if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# 5. THE TEST EXECUTABLE
# We define it HERE, so we can configure it below.
add_executable(QuantTests
        tests/test_main.cpp
        tests/OrderBookTests.cpp
)

# 6. TEST CONFIGURATION (Include paths and Linking)
target_include_directories(QuantTests PRIVATE
        include
        ${googletest_SOURCE_DIR}/googletest/include
)

target_link_libraries(QuantTests
        QuantLib
        gtest_main
)

# 7. ENABLE CLION TEST EXPLORER
include(GoogleTest)
gtest_discover_tests(QuantTests)
cmake_minimum_required(VERSION 3.10)
project(BowlingGame)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify the include directories
include_directories(${CMAKE_SOURCE_DIR}/inc)

# Define the source files for the main program
set(SOURCES
    src/bowling_game.cpp
    driver/main.cpp
)

# Create the main executable
add_executable(BowlingGame ${SOURCES})

# Find Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Define the source files for the test program
set(TEST_SOURCES
    src/bowling_game.cpp
    tests/bowling_game_test.cpp
)

# Create the test executable
add_executable(BowlingGameTests ${TEST_SOURCES})

# Link Google Test libraries to the test executable
target_link_libraries(BowlingGameTests ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)

# Enable testing
enable_testing()
add_test(NAME BowlingGameTests COMMAND BowlingGameTests)
#include <gtest/gtest.h>
#include "bowling_game.h"

TEST(BowlingGameTest, GameWithSpare) {
    std::vector<int> rolls = {5, 5, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    EXPECT_EQ(BowlingGame::calculateScore(rolls), 16);
}

TEST(BowlingGameTest, GameWithStrike) {
    std::vector<int> rolls = {10, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    EXPECT_EQ(BowlingGame::calculateScore(rolls), 24);
}

TEST(BowlingGameTest, PerfectGame) {
    std::vector<int> rolls = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
    EXPECT_EQ(BowlingGame::calculateScore(rolls), 300);
}

TEST(BowlingGameTest, TenthFrameSpare) {
    std::vector<int> rolls = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 3};
    EXPECT_EQ(BowlingGame::calculateScore(rolls), 13);
}

TEST(BowlingGameTest, TenthFrameStrike) {
    std::vector<int> rolls = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 5, 3};
    EXPECT_EQ(BowlingGame::calculateScore(rolls), 18);
}

TEST(BowlingGameTest, AllOpenFrames) {
    std::vector<int> rolls = {1, 2, 3, 4, 2, 3, 4, 5, 1, 1, 2, 2, 3, 3, 4, 4, 2, 2, 1, 1};
    EXPECT_EQ(BowlingGame::calculateScore(rolls), 50);
}

TEST(BowlingGameTest, GameUTFromImage) {
    std::vector<int> rolls = {1, 4, 5, 5, 6, 4, 9, 0, 6, 1, 7, 3, 9, 1, 7, 1, 2, 8, 3, 6};
    EXPECT_EQ(BowlingGame::calculateScore(rolls), 122);
}

TEST(BowlingGameTest, InvalidRoll) {
    std::vector<int> rolls = {1, 11};
    EXPECT_THROW(BowlingGame::calculateScore(rolls), InvalidRollException);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

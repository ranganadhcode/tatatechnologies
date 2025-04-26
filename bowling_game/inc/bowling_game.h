#ifndef BOWLING_GAME_H
#define BOWLING_GAME_H

#include <vector>
#include <stdexcept>

class Frame {
public:
    Frame() : roll1(0), roll2(0), bonusRoll1(0), bonusRoll2(0) {}
    Frame(int roll1, int roll2 = 0, int bonusRoll1 = 0, int bonusRoll2 = 0);
    int calculateScore() const;
    bool isStrike() const { return roll1 == 10; }
    bool isSpare() const { return !isStrike() && roll1 + roll2 == 10; }
    bool isTenthFrame() const { return bonusRoll1 != 0 || bonusRoll2 != 0; }
    int getRoll1() const { return roll1; }
    int getRoll2() const { return roll2; }
    int getBonusRoll1() const { return bonusRoll1; }
    int getBonusRoll2() const { return bonusRoll2; }

private:
    int roll1, roll2; // First and second rolls in the frame
    int bonusRoll1, bonusRoll2; // Bonus rolls for 10th frame (Strike or Spare)
    friend class Player; // Allow Player to access private members
};

class Player {
public:
    Player();
    void addRoll(int pins);
    int getTotalScore() const;

private:
    std::vector<Frame> frames;
    int frameIndex;
    int rollIndex;
};

class BowlingGame {
public:
    static int calculateScore(const std::vector<int>& rolls);
};

class InvalidRollException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid roll! Pins must be between 0 and 10.";
    }
};

#endif
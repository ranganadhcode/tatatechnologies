#include "bowling_game.h"

Frame::Frame(int roll1, int roll2, int bonusRoll1, int bonusRoll2) {
    if (roll1 < 0 || roll1 > 10 || roll2 < 0 || roll2 > 10 ||
        bonusRoll1 < 0 || bonusRoll1 > 10 || bonusRoll2 < 0 || bonusRoll2 > 10) {
        throw InvalidRollException();
    }
    this->roll1 = roll1;
    this->roll2 = roll2;
    this->bonusRoll1 = bonusRoll1;
    this->bonusRoll2 = bonusRoll2;
}

int Frame::calculateScore() const {
    int score = roll1 + roll2;
    if (isStrike() && !isTenthFrame()) {
        score += bonusRoll1 + bonusRoll2; // Bonus from next two rolls
    } else if (isSpare() && !isTenthFrame()) {
        score += bonusRoll1; // Bonus from next roll
    } else if (isTenthFrame()) {
        score += bonusRoll1 + bonusRoll2; // Include bonus rolls for 10th frame
    }
    return score;
}

Player::Player() : frameIndex(0), rollIndex(0) {
    frames.resize(10);
}

void Player::addRoll(int pins) {
    if (pins < 0 || pins > 10) {
        throw InvalidRollException();
    }

    if (frameIndex < 9) { // Normal frames (1-9)
        if (rollIndex == 0) {
            // Apply bonuses to previous frames
            if (frameIndex > 0 && frames[frameIndex - 1].isSpare()) {
                frames[frameIndex - 1] = Frame(frames[frameIndex - 1].getRoll1(), frames[frameIndex - 1].getRoll2(), pins, 0);
            }
            if (frameIndex > 0 && frames[frameIndex - 1].isStrike()) {
                if (frames[frameIndex - 1].getBonusRoll1() == 0) {
                    frames[frameIndex - 1] = Frame(frames[frameIndex - 1].getRoll1(), 0, pins, 0);
                }
            }
            if (frameIndex > 1 && frames[frameIndex - 2].isStrike() && frames[frameIndex - 2].getBonusRoll2() == 0) {
                frames[frameIndex - 2] = Frame(frames[frameIndex - 2].getRoll1(), 0, frames[frameIndex - 2].getBonusRoll1(), pins);
            }
            frames[frameIndex] = Frame(pins, 0, 0, 0); // First roll
            if (pins == 10) { // Strike
                frameIndex++;
                rollIndex = 0;
            } else {
                rollIndex = 1;
            }
        } else { // Second roll
            // Apply bonus to previous strike if second roll is available
            if (frameIndex > 0 && frames[frameIndex - 1].isStrike() && frames[frameIndex - 1].getBonusRoll2() == 0) {
                frames[frameIndex - 1] = Frame(frames[frameIndex - 1].getRoll1(), 0, frames[frameIndex - 1].getBonusRoll1(), pins);
            }
            frames[frameIndex] = Frame(frames[frameIndex].getRoll1(), pins, 0, 0);
            frameIndex++;
            rollIndex = 0;
        }
    } else if (frameIndex == 9) { // 10th frame
        if (rollIndex == 0) {
            // Apply bonus to Frame 9 if it was a spare or strike
            if (frameIndex > 0 && frames[frameIndex - 1].isSpare()) {
                frames[frameIndex - 1] = Frame(frames[frameIndex - 1].getRoll1(), frames[frameIndex - 1].getRoll2(), pins, 0);
            }
            if (frameIndex > 0 && frames[frameIndex - 1].isStrike()) {
                if (frames[frameIndex - 1].getBonusRoll1() == 0) {
                    frames[frameIndex - 1] = Frame(frames[frameIndex - 1].getRoll1(), 0, pins, 0);
                } else if (frames[frameIndex - 1].getBonusRoll2() == 0) {
                    frames[frameIndex - 1] = Frame(frames[frameIndex - 1].getRoll1(), 0, frames[frameIndex - 1].getBonusRoll1(), pins);
                }
            }
            if (frameIndex > 1 && frames[frameIndex - 2].isStrike() && frames[frameIndex - 2].getBonusRoll2() == 0) {
                frames[frameIndex - 2] = Frame(frames[frameIndex - 2].getRoll1(), 0, frames[frameIndex - 2].getBonusRoll1(), pins);
            }
            frames[frameIndex] = Frame(pins, 0, 0, 0);
            rollIndex = 1;
        } else if (rollIndex == 1) {
            if (frameIndex > 0 && frames[frameIndex - 1].isStrike() && frames[frameIndex - 1].getBonusRoll2() == 0) {
                frames[frameIndex - 1] = Frame(frames[frameIndex - 1].getRoll1(), 0, frames[frameIndex - 1].getBonusRoll1(), pins);
            }
            if (frames[frameIndex].isStrike()) {
                frames[frameIndex] = Frame(frames[frameIndex].getRoll1(), 0, pins, 0);
            } else {
                frames[frameIndex] = Frame(frames[frameIndex].getRoll1(), pins, 0, 0);
            }
            if (frames[frameIndex].isStrike() || frames[frameIndex].isSpare()) {
                rollIndex = 2;
            } else {
                frameIndex++; // End game
            }
        } else if (rollIndex == 2) {
            if (frames[frameIndex].isStrike()) {
                frames[frameIndex] = Frame(frames[frameIndex].getRoll1(), frames[frameIndex].getRoll2(), frames[frameIndex].getBonusRoll1(), pins);
            } else {
                frames[frameIndex] = Frame(frames[frameIndex].getRoll1(), frames[frameIndex].getRoll2(), pins, 0);
            }
            if (frames[frameIndex].isStrike() && frames[frameIndex].getRoll2() == 10) {
                rollIndex = 3;
            } else {
                frameIndex++; // End game
            }
        } else if (rollIndex == 3) {
            frames[frameIndex] = Frame(frames[frameIndex].getRoll1(), frames[frameIndex].getRoll2(), frames[frameIndex].getBonusRoll1(), pins);
            frameIndex++; // End game
        }
    }
}

int Player::getTotalScore() const {
    int total = 0;
    for (int i = 0; i < 10; i++) { // Sum all 10 frames
        total += frames[i].calculateScore();
    }
    return total;
}

int BowlingGame::calculateScore(const std::vector<int>& rolls) {
    Player player;
    for (int pins : rolls) {
        player.addRoll(pins);
    }
    return player.getTotalScore();
}
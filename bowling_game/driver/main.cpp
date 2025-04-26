#include <iostream>
#include <vector>
#include "bowling_game.h"
using namespace std;

int main() {
    vector<int> rolls;
    int rollValue;

    cout << "Enter the number of pins knocked down in each roll (enter -1 to finish):\n";
    while (true) {
        cin >> rollValue;
        if (rollValue == -1) break;
        try {
            rolls.push_back(rollValue);
        } catch (const InvalidRollException& e) {
            cout << e.what() << endl;
            return 1;
        }
    }

    try {
        int totalScore = BowlingGame::calculateScore(rolls);
        cout << "Total score: " << totalScore << endl;
    } catch (const InvalidRollException& e) {
        cout << e.what() << endl;
        return 1;
    }

    return 0;
}
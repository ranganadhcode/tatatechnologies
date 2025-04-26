Google Test Set Up:
- On Ubuntu/Linux:
    sudo apt-get install libgtest-dev
    sudo apt-get install cmake
    cd /usr/src/gtest
    sudo cmake CMakeLists.txt
    sudo make
    sudo cp lib/*.a /usr/lib

Compilation Steps: Run below steps from the project home
    mkdir build
    cd build
    cmake ..
    make
    ./BowlingGameTests      // To run Unit Test
    ./BowlingGame           // To run the Project alone

Unit Test Case Explanations
    - GameWithSpare: Tests a spare with a bonus roll.
    - GameWithStrike: Tests a strike with bonus rolls.
    - PerfectGame: Tests a perfect game (all strikes).
    - TenthFrameSpare: Tests a spare in the 10th frame with a bonus roll.
    - TenthFrameStrike: Tests a strike in the 10th frame with two bonus rolls.
    - AllOpenFrames: Tests a game with no spares or strikes.
    - ExampleGameFromImage: Tests the example from the image.
    - InvalidRoll: Tests exception handling for invalid input.
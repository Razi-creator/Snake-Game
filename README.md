# Console-Based Snake Game (C++)

## Description
A classic, terminal-based Snake game written in C++. This project features a multi-round system where players can set the number of rounds and a time limit for each. As the rounds progress, the game dynamically generates more obstacles, increasing the difficulty. At the end of the gameplay, match statistics (Round, Time Spent, and Score) are automatically logged into a text file.

## Features
* **Classic Gameplay:** Navigate the snake to eat food (`*`), grow in length, and accumulate points.
* **Progressive Difficulty:** Random obstacles (`X`) are generated on the board. The number of obstacles increases based on the current round number.
* **Timed Rounds:** Each round operates on a strict timer. The round ends if the snake collides with a wall/obstacle, or if the time runs out.
* **Real-time HUD:** A flickering-free display that shows the current score, active round, and a live countdown timer.
* **Persistent Score Tracking:** Automatically generates and appends match results to a `results.txt` file in a neatly formatted table.

## Prerequisites
* **OS:** Windows (This game utilizes `<windows.h>` and `<conio.h>` for console manipulation and asynchronous keyboard input).
* **Compiler:** Any standard C++ compiler (e.g., GCC/MinGW, MSVC).

## Controls
Use the **Arrow Keys** to navigate the snake:
* `Up Arrow` - Move Up
* `Down Arrow` - Move Down
* `Left Arrow` - Move Left
* `Right Arrow` - Move Right

## How to Run
1. Clone the repository and compile the `main.cpp` (or whatever you named your file) using your C++ compiler.
   ```bash
   g++ main.cpp -o snakegame
## Run the executable:

**Bash**
./snakegame

Enter the total number of rounds you wish to play.

Enter the time limit (in seconds) for each round.

Play the game! Once all rounds are finished, check the results.txt file in the same directory to view your performance history.

## Code Structure:

**class SG**: The core game engine encapsulating the board state, snake logic, and UI rendering.

**game_board()**: Initializes the play area, boundaries (#), and random obstacles (X).

**movement_func()**: Handles the core logic for moving the snake array, detecting collisions, and eating food.

**recordStats()**: Handles file I/O operations to log the player's score and time data safely.

# Console Ping Pong Game in C++

This is a simple console-based ping pong (Pong) game written in C++ using the Windows console API. The game features a persistent high score saved to a text file and allows two players to control left and right paddles using keyboard controls.

## Features

- Play classic Pong in the console window
- Control left paddle with **W** (up) and **S** (down)
- Control right paddle with **Up Arrow** and **Down Arrow**
- The ball bounces between the paddles and walls
- Persistent high score is saved to a `highscore.txt` file
- Reset high score through the main menu
- Shows a congratulatory message if you beat the previous high score
- Smooth paddle movement when holding down control keys
- Clean border-drawn console graphics

## Controls

- **W**: Move left paddle up
- **S**: Move left paddle down
- **Up Arrow**: Move right paddle up
- **Down Arrow**: Move right paddle down
- **Esc**: Quit gameplay and return to the menu
- **R**: Reset high score (from menu)

## How to Build

> **Note**: This game uses `<conio.h>` and `<windows.h>`, so it will only compile on **Windows**.

1. Install a C++ compiler supporting Windows console API, e.g. MinGW or Visual Studio.
2. Save the source code (e.g., `pong.cpp`).
3. Compile:

```bash
g++ pong.cpp -o pong
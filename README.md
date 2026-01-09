# Tic-Tac-Toe Reborn

A simple, modern C++ implementation of the classic Tic-Tac-Toe game using SDL3.

## Features

- **Local Multiplayer:** Play against a friend on the same machine.
- **Graphical Interface:** Clean UI powered by SDL3.
- **Game States:** Menu, Gameplay, and Win/Draw detection.

## Prerequisites

Before building the project, ensure you have the following installed:

- **C++ Compiler:** Compatible with C++23 (e.g., GCC 11+, Clang 14+, MSVC).
- **CMake:** Version 3.10 or later.
- **SDL3 Libraries:**
  - `SDL3`
  - `SDL3_image`
  - `SDL3_ttf`

## Build Instructions

1.  **Clone the repository** (if applicable) or navigate to the project directory.

2.  **Create a build directory:**
    ```bash
    mkdir build
    cd build
    ```

3.  **Configure the project with CMake:**
    ```bash
    cmake ..
    ```

4.  **Compile the source code:**
    ```bash
    make
    ```

## Running the Game

The game relies on loading assets (images and fonts) from the `assets/` directory. For the game to find these files, run the executable from the project root directory:

```bash
./build/tictactoe
```

## Controls

- **Mouse:** Left-click to select options in the menu and place your symbol (X or O) on the grid.

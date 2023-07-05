# Snake Game
This is a console-based Snake Game built in C language. The game allows the player to control a snake on a board and eat food to grow longer. The goal is to achieve the highest score possible without colliding with the borders of the board or the snake's own body.

# Project Structure
The project consists of the following files:

main.c: This file contains the main function and serves as the entry point of the program. It handles user input, initializes the game board, and controls the game flow.

functions.c: This file contains various functions used in the game, including board creation, board printing, board updating, snake movement, and food placement.

functions.h: This header file defines the function prototypes used in the project. It provides a way to declare the functions and share them across different files.

# How to Play
Compile the project using a C compiler (e.g., gcc).
Run the compiled executable to start the game.
Enter the desired board size when prompted.
Control the snake's movement by entering the corresponding keys:
  UP: 8
  DOWN: 2
  LEFT: 4
  RIGHT: 6
The snake will move according to the input, and the board will be updated.
Collect food (@) to increase the snake's size and score.
The game ends if the snake hits the borders of the board or its own body.
After the game ends, the final score will be displayed.
# Dependencies
The project relies on the following standard C libraries:

stdbool.h
stdio.h
stdlib.h

# Dual N-Back Game

A C++ implementation of the Dual N-Back memory-training game for the ACE6193 Object-Oriented Programming assignment.

## Overview

Dual N-Back challenges the player to remember information from several rounds earlier. During each round, the player compares the current position and/or symbol with the ones shown **N rounds before**.

This project demonstrates object-oriented programming concepts in C++, including program structure, game logic, user interaction, and memory-based comparisons.

## Files

- `assignment_last.cpp` — main Dual N-Back game implementation
- `assignment.cpp` — earlier assignment source file

## Requirements

- A C++ compiler supporting C++11 or later, such as `g++`

## Build and run

```bash
g++ assignment_last.cpp -o dual_n_back
./dual_n_back

On Windows:
g++ assignment_last.cpp -o dual_n_back.exe
.\dual_n_back.exe

### How to play
1. Start the program.
2. Follow the prompts displayed in the terminal.
3. Remember the visual and/or audio information from previous rounds.
4. Indicate a match when the current item is the same as the item from N rounds earlier.
5. Continue until the game ends and review your score.

Course: ACE6193 — Object-Oriented Programming with C++

Author: Mohammed Waleed Khan

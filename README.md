# Dual N-Back Game

A C++ implementation of a Dual N-Back memory-training game for the **ACE6193 Object-Oriented Programming** assignment.

## Overview

Dual N-Back challenges the player to remember information from several rounds earlier. In each round, compare the current position and/or symbol with the one shown **N rounds before**.

This project demonstrates object-oriented programming concepts in C++, including game logic, user interaction, and memory-based comparisons.

## Files

- `assignment_last.cpp` — Main Dual N-Back game implementation
- `assignment.cpp` — Earlier assignment source file

## Requirements

- A C++ compiler supporting C++11 or later, such as `g++`

## Build and Run

```bash
g++ assignment_last.cpp -o dual_n_back
./dual_n_back
```

### Windows

```powershell
g++ assignment_last.cpp -o dual_n_back.exe
.\dual_n_back.exe
```

## How to Play

1. Start the program.
2. Follow the prompts in the terminal.
3. Remember the visual or audio information from earlier rounds.
4. Indicate a match if the current item is the same as the one from **N rounds earlier**.
5. Continue until the game ends and review your score.

## Course

ACE6193 — Object-Oriented Programming with C++

## Author

Mohammed Waleed Khan

# Terminal Wordle
**University of Tennessee – Knoxville**  
**CS202 Spring 2024 Final Project**

## Overview
**Terminal Wordle** is a command-line version of the popular game **Wordle**, developed for the CS202 final project. Players guess five-letter words and receive feedback via color-coded hints.

## How to Run
To start the game, run the following command in your terminal:
```bash
./main input/valid-wordle-words.txt input/shuffled_real_wordles.txt
```

## How to Play
After each guess, you'll receive a hint using the following format:

- `g` = **green**: correct letter, correct position  
- `y` = **yellow**: correct letter, wrong position  
- `w` = **white**: letter not in the word  

**Example:**
```
Guess:  c l e a r  
Hint:   w w g w y  
Answer: t r e n d
```

This means:
- `e` is in the correct position (green),
- `r` is in the word but in the wrong position (yellow),
- The rest are not in the word (white).

## Commands
- Type `new` to start a new game  
- Type `help` to view the full list of instructions

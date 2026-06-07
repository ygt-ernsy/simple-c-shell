# Custom UNIX Shell

This is a custom UNIX shell created for study purposes.

## Initial Goals

My initial goals for this project are:
- To be able to continuously parse the arguments given.
- To be able to distinguish between different symbols.

Although these goals are small for a project as big as a custom UNIX shell, I want to maintain this document to keep track of my progress and update my objectives. As I go through building this project, my goals will naturally expand. 

Therefore, an ongoing goal is:
- To update this document each time I complete my current goals.

## Initial Planning

The shell will be a program that repeatedly reads from the terminal, waiting for the user to input a line and press `Enter`. The shell will then parse the input and act accordingly.

For this first phase, I will be writing a parser that can:
- Read a line from `stdin`.
- Parse the given line.

### Initial Pipeline

User input -> parser -> execute -> output

### Parser

Insied parser.c there will be a parser function which will:
- Iterate a given line
- Put the words which are seperated with a ' ' inside a give n char* array

## Files to Create Now
- `src/parser.c`
- `include/paser.h`

## Things That I learned in this phase:
- You need this command if you want to compile a .c file that doesn't have main: gcc -c
- You need this command if you want to compile a .c file that includes a header from another directory: gcc -I./dir-to-include

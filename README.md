# Compiler-Theory-Semantic
This repo contains code from a school project that asked us to modify a skeleton file of a semantic analyzer using flex, bison, C++, and make as part of a study in compiler theory.

## Requirements
- Your favorite Linux distribution (I recommend Ubuntu for this project)
- Use `apt` or `yum` to get the packages for Flex, Bison, Make, and G++ (Use `sudo` to avoid permission issues)
- Create your desired directory for the files using `mkdir`
- Move source files to your chosen directory using `mv` or your personally prefered method
- Navigate to the directory with the source files and use `make` to compile the project
- Utilize the following syntax to run the program `./compile < test1.txt`

## Features Added
- Added recognition for ERROR: Type Mismatch on Variable Initialization
- Added recognition for ERROR: When statement Types Mismatch
- Added recognition for ERROR: Switch Expression Not Integer
- Added recognition for ERROR: Case Types Mismatch
- Added recognition for ERROR: Arithmetic Operator Requires Numeric Types
- Added recognition for ERROR: Undeclared Scalar
- Added recognition for ERROR: Undeclared List
- Added recognition for ERROR: List Element Types Do Not Match
- Added recognition for ERROR: List Type Does Not Match Element Types
- Added recognition for ERROR: List Subscript Must Be Integer
- Added recognition for ERROR: Character Literals Cannot be Compared to Numeric Expressions
- Added recognition for ERROR: Remainder Operator Requires Integer Operands
- Added recognition for ERROR: If-Elsif-Else Type Mismatch
- Added recognition for ERROR: Fold Requires A Numeric List

### Special Notes
- If you are modifying any of the files, you must run `make` to compile your new changes
- If you are modifying any `.cc` files, be sure to modify the corresponding `.h` files.
- You can initiate a coding environment using VS Code using the `code .` command.
- You can utilize the test files from the related repositories for this project
   

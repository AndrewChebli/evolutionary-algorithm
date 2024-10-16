
# Puzzle Solver using Evolutionary Algorithm

This project implements an evolutionary algorithm to solve an 8x8 square puzzle consisting of 64 square pieces. Each piece (tile) has 4 edges with motifs (patterns or colors), and the goal is to arrange the tiles such that adjacent edges have matching motifs.

## Table of Contents
- [Description](#description)
- [Files](#files)
  - [main.cpp](#maincpp)
  - [evol-puzzle.h](#evol-puzzleh)
  - [evol-puzzle.cpp](#evol-puzzlecpp)
- [How to Compile](#how-to-compile-and-run)
- [How to Run](#how-to-run)
- [Input File](#input-file)
- [Command-Line Arguments](#command-line-arguments)
- [Output](#output)
- [Dependencies](#dependencies)
- [License](#license)

## Description
The puzzle consists of arranging 64 square tiles in an 8x8 grid. Each tile has four edges, each marked with a motif represented by a digit from 0 to 6 (total of 7 motifs). The objective is to place and orient the tiles so that adjacent edges have matching motifs.

This program uses an evolutionary algorithm (genetic algorithm) to find a solution:
- **Initialization**: Generate an initial population of candidate solutions.
- **Evaluation**: Assess the fitness of each candidate by counting the number of mismatched edges.
- **Selection**: Select the fittest candidates to be parents for the next generation.
- **Crossover**: Create offspring by combining parts of parent solutions.
- **Mutation**: Introduce random changes to offspring to maintain genetic diversity.
- **Iteration**: Repeat the evaluation, selection, crossover, and mutation steps over multiple generations.

The program continues evolving the population for a specified number of generations or until an optimal solution (zero mismatches) is found.

## Files

### main.cpp
Purpose: Contains the main function, which is the entry point of the application. It initializes the puzzle solver, reads input, generates the initial population, and evolves the population over a specified number of generations.

Key Functions and Operations:
- Parses command-line arguments to enable verbose output (-v flag).
- Prompts the user to input:
  - Population size (number of candidate solutions in each generation).
  - Number of generations to evolve.
- Measures the execution time of the evolutionary process.
- Reads the initial puzzle pieces from `Ass1Input.txt`.
- Builds necessary data structures:
  - Map of tiles and their rotations.
  - Duplicate tiles tracking.
- Calls functions to generate the initial population and evolve it.
- Outputs the time taken for the evolution process.
- Cleans up dynamically allocated memory before exiting.

### evol-puzzle.h
Purpose: Declares constants, function prototypes, and includes necessary headers for the puzzle solver. It serves as the interface for the functions implemented in `evol-puzzle.cpp`.

Key Components:
- **Constants**:
  - `TILE_SIZE`: Size of each tile (number of edges, which is 4).
  - `TILES_IN_PUZZLE_COUNT`: Total number of tiles in the puzzle (64).
- **Function Prototypes**:
  - Random number generator setup (`getRandomGen`).
  - Tile manipulation functions (rotation, conversion between arrays and strings).
  - Puzzle input/output functions (`readInput`, `printPuzzle`, `savePuzzle`).
  - Memory allocation and deallocation functions for puzzles and populations.
  - Evolutionary algorithm functions (`generatePopulation`, `evolve`, `mutate`, `crossover`, `evaluateFitness`, etc.).
  - Utility functions for genetic operations (crossover, mutation, selection).
- **Libraries Included**: 
  - Standard libraries for input/output, file handling, random number generation, data structures, time measurement, etc.

### evol-puzzle.cpp
Purpose: Implements the functions declared in `evol-puzzle.h`. Contains the core logic for the evolutionary algorithm and puzzle manipulation.

Key Functions Implemented:
- **Random Number Generation**:
  - `getRandomGen()`: Initializes the random number generator and distribution.
- **Tile Manipulation**:
  - `rotateToLeftByOneIndex()`: Rotates a tile's edges to the left.
  - `convertTileToVector()`, `convertTileToString()`: Converts tile representations between arrays, vectors, and strings.
- **Puzzle Handling**:
  - `readInput()`: Reads the initial puzzle pieces from a file.
  - `allocatePuzzle()`, `freePuzzle()`: Handles memory allocation and deallocation for a puzzle.
  - `printPuzzle()`, `savePuzzle()`: Outputs the puzzle to the console or saves it to a file.
- **Population Management**:
  - `allocatePopulation()`, `freePopulation()`: Manages memory for the population of candidate solutions.
  - `generatePopulation()`: Creates the initial population with variations in tile positions and orientations.
- **Evolutionary Algorithm Functions**:
  - `evolve()`: Controls the evolution process over generations.
  - `evaluateFitness()`: Calculates the fitness of each candidate by counting edge mismatches.
  - `selectParentsAndWorst()`: Selects the best candidates as parents and identifies the worst candidates for replacement.
  - `crossover()`: Performs crossover operations to generate offspring from parent candidates.
  - `mutate()`: Applies random mutations to offspring to introduce variability.
  - `selectSurvivorsAndReplace()`: Replaces the worst candidates with new offspring.
- **Utility Functions**:
  - `countEdgeMismatch()`: Counts the number of mismatches in a puzzle.
  - `swapTile()`, `copyPuzzle()`, `copyTile()`: Manipulates tiles and puzzles during genetic operations.
  - `recordDuplicateTiles()`, `buildMapOfTiles()`: Manages tile uniqueness and rotations.

## How to Compile and Run
Ensure you have a C++ compiler that supports C++11 or higher (e.g., GCC, Clang, or MSVC).

Using the terminal, navigate to the directory containing the source files and run:

compile and run main:
```
Linux/MacOS

g++ -std=c++11 -o puzzle_solver main.cpp evol-puzzle.cpp -O3 && ./puzzle_solver

Windows

g++ -std=c++11 -o puzzle_solver main.cpp evol-puzzle.cpp -O3; ./puzzle_solver
```

compile and run main (with verbose output):
```
Linux/MacOS

g++ -std=c++11 -o puzzle_solver main.cpp evol-puzzle.cpp -O3 && ./puzzle_solver -v

Windows

g++ -std=c++11 -o puzzle_solver main.cpp evol-puzzle.cpp -O3; ./puzzle_solver -v
```


compile and run test:
```
Linux/MacOS

g++ -std=c++11 -o test test.cpp evol-puzzle.cpp -O3 && ./test

Windows

g++ -std=c++11 -o test test.cpp evol-puzzle.cpp -O3; ./test
```

These commands compiles `main.cpp`/`test.cpp` and `evol-puzzle.cpp` into an executable named `puzzle_solver` or `test`.

## How to Run
After compiling, run the executable:

```bash
./puzzle_solver [options]
```

Example:

```bash
./puzzle_solver -v
```

This will run the program in verbose mode, providing detailed output during execution.

## Input File
The program expects an input file named `Ass1Input.txt` in the same directory. This file should contain the 64 puzzle tiles, formatted as 8 lines with 8 four-digit numbers per line.

Tile Representation:
- Each tile is represented by a four-digit number:
  - First digit: Top edge motif.
  - Second digit: Right edge motif.
  - Third digit: Bottom edge motif.
  - Fourth digit: Left edge motif.

Example `Ass1Input.txt`:
```yaml
0123 4567 8901 2345 6789 0123 4567 8901
... (7 more lines with similar format)
```

## Command-Line Arguments
- `-v`: Enables verbose output. The program will print additional information during execution, including intermediate puzzles and progress updates.

## Output

**Console Output**:
- The program will output the best puzzle found and its edge mismatch count.
- If verbose mode is enabled, it will print additional details each generation.
- Execution time in seconds.

**Output Files**:
- If a puzzle with 25 or fewer edge mismatches is found, it will be saved to the output directory.
- Filenames are in the format: `Ass1Output-<edge_mismatch_count>-YYYY-MM-DD-HH-MM-SS.txt`.
- The output directory is created if it does not exist.

Note: The output files contain the puzzle state and can be used for analysis or verification.

## Dependencies
- C++11 Standard Library components.
- No external libraries are required.

## License
This project is released under the MIT License.

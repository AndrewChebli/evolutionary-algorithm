#include <iostream>

/*
Problem Description. Your program must attempt to solve an 8x8 square puzzle containing 64
square pieces. The puzzle pieces are provided in an input file. The input file is 64 pieces in a random
arrangement, with eight 4-digit numbers per line (for a total of 8 lines). Note that when you create the
first population of puzzles (i.e., candidate solutions), each puzzle must contain all the 64 pieces but,
at least in the first population, the positions and orientations of the 64 pieces should be different, from
one puzzle to another.

Puzzle Representation. The are 64 pieces in the puzzle, arranged in an 8x8 square. Each tile has 4
edges and is represented by 4 numbers. Each number represent a motif (think of it as a pattern or a
colour) and there are a total of 7 motifs. The first number represents the top edge, the second number
represents the right edge, the third number represents the bottom edge, and the fourth number
represents the left edge.
*/

/*
The puzzle will be represented as a 1D array of 64 elements. Each element/tile will be a 4-element array.
*/
constexpr int TILE_SIZE = 4;
constexpr int TILES_IN_PUZZLE_COUNT = 64;

void rotateToLeftByOneIndex(int[TILE_SIZE]);
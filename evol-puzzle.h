#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <vector>
#include <assert.h>
#include <sstream>
using namespace std;
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

/**
 * @brief Swaps two randomly selected tiles(sub-arrays) in a 2D array.
 * 
 * This function selects two distinct random indices within the range of 
 * TILES_IN_PUZZLE_COUNT and swaps the corresponding rows (tiles) in the 
 * provided 2D array. The array is assumed to have dimensions 
 * TILES_IN_PUZZLE_COUNT x TILE_SIZE.
 * 
 * @param arr A 2D array representing the tiles to be swapped. The array 
 *            dimensions should be TILES_IN_PUZZLE_COUNT x TILE_SIZE.
 */
void swapTile(int[TILES_IN_PUZZLE_COUNT][TILE_SIZE]);

/**
 * @brief Reads a puzzle configuration from a file and stores it in a 2D array.
 * 
 * This function reads a file containing a puzzle configuration, where each line
 * represents a tile with digits. It parses the file content and stores the digits
 * in a 2D array.
 * 
 * @param filename The name of the file containing the puzzle configuration.
 * @param puzzle A 2D array to store the parsed puzzle configuration. The array
 *               should have dimensions [TILES_IN_PUZZLE_COUNT][TILE_SIZE].
 * 
 * @note The function assumes that the file contains the correct number of tiles
 *       and digits as specified by TILES_IN_PUZZLE_COUNT and TILE_SIZE.
 * 
 * @throws runtime_error if the file cannot be opened.
 */
void readInput(string, int[TILES_IN_PUZZLE_COUNT][TILE_SIZE]);
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <random>
#include <chrono>
#include <climits>
#include <assert.h>
#include <sstream>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <stdint.h>
#include <algorithm>
#include <utility>
#include <cmath>
#include <sys/stat.h>
#include <sys/types.h>
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


/**
 * @brief The size of each tile in the puzzle.
 * 
 * This constant defines the dimensions of each tile used in the puzzle.
 * It is set to a value of 4, meaning each tile is 4 units in size.
 */
constexpr int TILE_SIZE = 4;

/**
 * @brief The number of tiles in the puzzle.
 * 
 * This constant defines the total count of tiles present in the puzzle.
 * It is used throughout the code to ensure consistency when referring to
 * the number of tiles in the puzzle.
 */
constexpr int TILES_IN_PUZZLE_COUNT = 64;

pair<mt19937, uniform_int_distribution<int>> getRandomGen();

/**
 * @brief Rotates the elements of the given array to the left by one index.
 * 
 * This function takes an array and shifts all its elements one position to the left.
 * The first element of the array is moved to the last position.
 * 
 * @param arr The array to be rotated. The array should have a size of TILE_SIZE.
 */
void rotateToLeftByOneIndex(int[]);

/**
 * @brief Rotates the elements of the given vector to the left by one index.
 *
 * This function takes a reference to a vector of integers and rotates its elements
 * to the left by one position. The first element of the vector is moved to the end.
 *
 * @param tile A reference to a vector of integers to be rotated.
 * @return A vector of integers after rotating the elements to the left by one index.
 */
vector<int> rotateToLeftByOneIndexReturn(vector<int> &tile);

/**
 * @brief Converts an array of integers to a vector of integers.
 * 
 * This function takes an array of integers and converts it into a 
 * std::vector<int> of the same size. The size of the array is 
 * determined by the constant TILE_SIZE.
 * 
 * @param arr The input array of integers to be converted.
 * @return std::vector<int> A vector containing the elements of the input array.
 */
vector<int> convertTileToVector(int arr[]);

/**
 * @brief Converts a vector of integers representing a tile into a string.
 * 
 * This function takes a vector of integers and concatenates each integer
 * into a single string. The size of the vector is assumed to be TILE_SIZE.
 * 
 * @param vec A vector of integers representing the tile.
 * @return A string representation of the tile.
 */
string convertTileToString(vector<int> vec);

/**
 * @brief Records duplicate tiles in a puzzle.
 *
 * This function takes a 2D array representing a puzzle and records the number of duplicate tiles.
 * Each tile is converted to a vector and then to a string representation. The function considers
 * all possible rotations of each tile to identify duplicates.
 *
 * @param puzzle A 2D array representing the puzzle.
 * @return An unordered_map where the keys are string representations of tiles and the values are the counts of duplicates.
 */
unordered_map<string, int> recordDuplicateTiles(int** puzzle);

unordered_map <string, int> buildMapOfTiles(int** puzzle, const int start_index, const int end_index);

unordered_map <string, string> buildMapOfTiles(int** puzzle);
/**
 * @brief Swaps two random tiles in a 2D array.
 *
 * This function selects two distinct random indices within the range of the puzzle tiles
 * and swaps the tiles at these indices. The random selection is seeded using a high-resolution
 * clock to ensure variability.
 *
 * @param arr A pointer to a 2D array representing the puzzle tiles.
 *
 * @note The array is assumed to have a size of TILES_IN_PUZZLE_COUNT x TILE_SIZE.
 */
void swapTile(int** arr);

/**
 * @brief Reads a puzzle input from a file and stores it in a 2D array.
 * 
 * This function reads the contents of the specified file, parses it into a 2D array of integers,
 * and stores the result in the provided 2D array `puzzle`.
 * 
 * @param filename The path to the input file containing the puzzle data.
 * @param puzzle A pointer to a 2D array where the parsed puzzle data will be stored.
 * 
 * @note The input file should contain numbers arranged in a specific format that can be parsed
 *       into a 2D array of integers.
 * @note The dimensions of the `puzzle` array should match the expected dimensions defined by
 *       `TILES_IN_PUZZLE_COUNT` and `TILE_SIZE`.
 * 
 * @throws runtime_error If the file cannot be opened.
 */
void readInput(string, int** puzzle);

/**
 * @brief Allocates memory for a population of individuals.
 * 
 * This function allocates a 3D array to represent a population of individuals
 * for a genetic algorithm or evolutionary computation. Each individual in the 
 * population is represented by a 2D array.
 * 
 * @param population_size The number of individuals in the population.
 * @return A pointer to the allocated 3D array representing the population.
 */
int*** allocatePopulation(int population_size);

/**
 * @brief Allocates memory for a puzzle.
 * 
 * This function dynamically allocates a 2D array to represent a puzzle.
 * The puzzle is represented as an array of pointers, where each pointer
 * points to an array of integers. The size of the puzzle and the size
 * of each tile are determined by the constants TILES_IN_PUZZLE_COUNT
 * and TILE_SIZE, respectively.
 * 
 * @return int** A pointer to the allocated 2D array representing the puzzle.
 */
int** allocatePuzzle();

/**
 * @brief Frees the memory allocated for a 2D puzzle array.
 * 
 * This function deallocates the memory for each row of the puzzle
 * and then deallocates the memory for the array of row pointers.
 * 
 * @param puzzle A pointer to the 2D array representing the puzzle.
 */
void freePuzzle(int** puzzle);

/**
 * @brief Frees the memory allocated for a population array.
 * 
 * This function deallocates the memory used by a 3D array representing a population.
 * It iterates through the population array and frees each sub-array before freeing
 * the main population array itself.
 * 
 * @param population_arr A pointer to the 3D array representing the population.
 * @param population_size The size of the population (number of individuals).
 */
void freePopulation(int*** population_arr, int population_size);

/**
 * @brief Generates an initial population for the puzzle solver.
 *
 * This function initializes a population array with a given size, where each 
 * individual in the population is a variation of the initial puzzle configuration.
 *
 * @param population_arr A 3D array to store the generated population. The first 
 *                       dimension represents the population size, the second 
 *                       dimension represents the tiles in the puzzle, and the 
 *                       third dimension represents the size of each tile.
 * @param arr A 2D array representing the initial puzzle configuration. The first 
 *            dimension represents the tiles in the puzzle, and the second dimension 
 *            represents the size of each tile.
 * @param population_size The number of individuals in the population.
 */
void generatePopulation(int*** population_arr, int** puzzle, int population_size, pair<mt19937, uniform_int_distribution<int>> random);

/**
 * @brief Counts the number of edge mismatches in a given puzzle.
 *
 * This function checks the mismatches between adjacent tiles in a puzzle.
 * It considers both the left and top edges of each tile and compares them
 * with the corresponding edges of the neighboring tiles.
 *
 * @param puzzle A 2D array representing the puzzle, where each tile is an array of edges.
 *               The edges are assumed to be in the following order:
 *               [top, right, bottom, left].
 * @return The total number of edge mismatches in the puzzle.
 */
int countEdgeMismatch(int** puzzle);


/**
 * @brief Performs a one-point crossover on two parent matrices.
 * 
 * This function takes two parent matrices and performs a one-point crossover
 * to produce offspring. The crossover point is chosen randomly, and the 
 * elements of the matrices are swapped at that point to create new offspring.
 * 
 * @param parent1 A pointer to the first parent matrix.
 * @param parent2 A pointer to the second parent matrix.
 */
int onePointCrossover(int** parent1, int** parent2);


/**
 * @brief Performs a two-point crossover on two parent matrices.
 *
 * This function takes two parent matrices and performs a two-point crossover
 * to generate offspring. The crossover points are chosen randomly, and the
 * segments between these points are swapped between the two parents.
 *
 * @param parent1 A pointer to the first parent matrix.
 * @param parent2 A pointer to the second parent matrix.
 */
pair<int, int>  twoPointCrossover(int** parent1, int** parent2);

/**
 * @brief Evolves a population of solutions over a specified number of generations.
 *
 * This function performs genetic algorithm operations such as crossover and mutation
 * on a population of solutions. It evaluates the fitness of the population after each
 * generation and tracks the minimum edge mismatch count.
 *
 * @param population_arr A pointer to a 3D array representing the population of solutions.
 * @param NUM_OF_GENERATIONS The number of generations to evolve the population.
 * @param POPULATION_SIZE The size of the population.
 */
void evolve(int*** population_arr, int NUM_OF_GENERATIONS, const int POPULATION_SIZE, const unordered_map<string, int> &duplicatesMap, const unordered_map<string, string> &map_of_tiles,pair<mt19937, uniform_int_distribution<int>> random, bool print_flag);

/**
 * @brief Mutates a population of puzzles by performing random rotations and swaps.
 * 
 * This function iterates over each puzzle in the population and performs a series of 
 * random rotations and swaps on the tiles within each puzzle. The number of rotations 
 * and swaps is determined randomly for each puzzle.
 * 
 * @param population_arr A 3D array representing the population of puzzles.
 * @param POPULATION_SIZE The number of puzzles in the population.
 * 
 * The function uses the Mersenne Twister random number generator to ensure high-quality 
 * randomness. For each puzzle, it generates a random number of iterations and performs 
 * the following operations:
 * - Rotates a randomly selected tile to the left by one index.
 * - Swaps tiles within the puzzle.
 */
void mutate(int*** offspring_arr, const int POPULATION_SIZE, pair<mt19937, uniform_int_distribution<int>> random, int mutation_rate);

/**
 * @brief Performs crossover operation on a population array.
 * 
 * This function iterates through the population array in pairs and applies
 * a two-point crossover operation on each pair. The crossover is performed
 * only if there is a valid pair (i.e., the second individual in the pair exists).
 * 
 * @param population_arr A pointer to the population array, where each individual
 *                       is represented as a pointer to an array of integers.
 * @param POPULATION_SIZE The size of the population array.
 */
void crossover(int*** population_arr, const int POPULATION_SIZE, const vector<int> &parent_indexes_vec, int*** offspring_arr, const unordered_map<string, int> &duplicatesMap, const unordered_map<string,string> &map_of_tiles, int min_edge_mismatch_count, pair<mt19937, uniform_int_distribution<int>> random);

/**
 * @brief Evaluates the fitness of a population of puzzle solutions.
 *
 * This function iterates through a population of puzzle solutions and calculates
 * the edge mismatch count for each solution. It returns the minimum edge mismatch
 * count found in the population, which represents the best fitness score.
 *
 * @param population_arr A 3D array representing the population of puzzle solutions.
 * @param POPULATION_SIZE The number of puzzle solutions in the population.
 * @param min_edge_mismatch_count The initial minimum edge mismatch count to compare against.
 * @return The minimum edge mismatch count found in the population.
 */
vector<pair<int, int>> evaluateFitness(int*** population_arr, const int POPULATION_SIZE);

pair<vector<int>, vector<int>> selectParentsAndWorst(int*** population_arr, const int POPULATION_SIZE, const vector<pair<int, int>> &sorted_index_by_fitness_vec, const int ratratio_adjusted_pop_sizeio);

void selectSurvivorsAndReplace(int*** population_arr, const int POPULATION_SIZE, const vector<int> &worst_index_vec, int*** offspring_arr);

int calculateDiversity(int*** population_arr, const int POPULATION_SIZE);

void copyPuzzle(int** source_puzzle, int** copy_puzzle);

void copyTile(int* source_tile, int* dest_tile);

void writePuzzleIntoPopulation(int***, const int POPULATION_SIZE, int**);

void printPuzzle(int** puzzle);

void savePuzzle(int** puzzle, int edge_mismatch_count);

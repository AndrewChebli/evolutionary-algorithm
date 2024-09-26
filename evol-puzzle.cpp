#include "evol-puzzle.h"


/**
 * @brief Rotates the elements of the given array to the left by one index.
 * 
 * This function takes an array and shifts all its elements one position to the left.
 * The first element of the array is moved to the last position.
 * 
 * @param arr The array to be rotated. The array should have a size of TILE_SIZE.
 */
void rotateToLeftByOneIndex(int arr[]){
    int temp = arr[0];
    for (int i = 0; i < TILE_SIZE - 1; i++){
        arr[i] = arr[i+1];
    }
    arr[TILE_SIZE - 1] = temp;
}


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
void swapTile(int** arr){
    // using a high-resolution clock to seed the random number generator
    unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed); // Mersenne Twister random number generator
    std::uniform_int_distribution<int> distribution(0, TILES_IN_PUZZLE_COUNT - 1);

    int first_index = distribution(generator);
    int second_index = first_index;
    while (second_index == first_index){
        second_index = distribution(generator);
    }

    int temp_tile[TILE_SIZE];
    for (int i = 0; i < TILE_SIZE; i++){
        temp_tile[i] = arr[first_index][i];
    }
    
    for (int i = 0; i < TILE_SIZE; i++){
        arr[first_index][i] = arr[second_index][i];
    }

    for (int i = 0; i < TILE_SIZE; i++){
        arr[second_index][i] = temp_tile[i];
    }
}


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
void readInput(string filename, int** puzzle){
    ifstream file(filename);
    
    if (!file) {
        cerr << "Unable to open file numbers.txt";
    }
    
    // Reading file into a string
    stringstream buffer;
    buffer << file.rdbuf();
    string content = buffer.str();

    file.close();

    // Parsing the content into a 2D vector of digits
    vector<vector<int>> digitsArray;
    istringstream stream(content);
    string number;

    while (stream >> number) {  // Reading each number as a string
        vector<int> tile;  
        for (char digit : number) {  // Iterating through each character
            tile.push_back(digit - '0');  // Converting char to int and adding to row
        }
        // Adding the row of digits to the 2D array
        digitsArray.push_back(tile);
    }

    // copying from vector<vector<int>> to normal 2d int array
    for (int i = 0; i < TILES_IN_PUZZLE_COUNT; i++){
        for (int j = 0; j < TILE_SIZE; j++){
            puzzle[i][j] = digitsArray[i][j];
        }
    }
}


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
int*** allocatePopulation(int population_size) {
    int*** population = new int**[population_size];
    for (int i = 0; i < population_size; ++i) {
        population[i] = new int*[TILES_IN_PUZZLE_COUNT];
        for (int j = 0; j < TILES_IN_PUZZLE_COUNT; ++j) {
            population[i][j] = new int[TILE_SIZE];
        }
    }
    return population;
}


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
int** allocatePuzzle() {
    int** puzzle = new int*[TILES_IN_PUZZLE_COUNT];
    for (int i = 0; i < TILES_IN_PUZZLE_COUNT; ++i) {
        puzzle[i] = new int[TILE_SIZE];
    }
    return puzzle;
}


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
void freePopulation(int*** population_arr, int population_size) {
    for (int i = 0; i < population_size; ++i) {
        for (int j = 0; j < TILES_IN_PUZZLE_COUNT; ++j) {
            delete[] population_arr[i][j];
        }
        delete[] (*population_arr)[i]; 
    }
    delete[] *population_arr;
}


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
void generatePopulation(int*** population_arr, int** arr, int population_size){

        int** arr_copy = allocatePuzzle();

        for (int i = 0; i < TILES_IN_PUZZLE_COUNT; i++){
            for (int j = 0; j < TILE_SIZE; j++){
                arr_copy[i][j] = arr[i][j];
            }
        }

        for (int i = 0; i < TILES_IN_PUZZLE_COUNT; i++){
            for (int j = 0; j < TILE_SIZE; j++){
                population_arr[0][i][j] = arr_copy[i][j];
            }
        }

        for (int i = 1; i < population_size; i++){
            for (int j = 0; j < TILES_IN_PUZZLE_COUNT/2; j++){
                swapTile(arr_copy);
            }
            
            for (int j = 0; j < TILES_IN_PUZZLE_COUNT; j++){
                for (int p = 0; p < TILE_SIZE; p++){
                    population_arr[i][j][p] = arr_copy[j][p];
                }
            }
        }
}


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
int countEdgeMismatch(int** puzzle){
    int edge_mismatch = 0;
    
    // checking left edge mismatch
    for (int i = 0; i < TILES_IN_PUZZLE_COUNT; i++){
        if (i % 8 == 0){
            continue;
        }

        if (puzzle[i][3] != puzzle[i-1][1]){
            edge_mismatch++;
        }
    }

    // checking top edge mismatch
    for (int i = 8; i < TILES_IN_PUZZLE_COUNT; i++){
        if (puzzle[i][0] != puzzle[i-8][2]){
            edge_mismatch++;
        }
    }

    return edge_mismatch;
}

/**
 * @brief Performs a one-point crossover on two parent matrices.
 * 
 * This function takes two parent matrices and performs a one-point crossover
 * to generate new offsprings. The crossover point is chosen randomly, and the 
 * elements of the matrices are swapped at that point to create new offspring.
 * 
 * @param parent1 A pointer to the first parent matrix.
 * @param parent2 A pointer to the second parent matrix.
 */
void onePointCrossover(int** parent1, int** parent2){
    // TODO: Create function to take care of random number generation and seeding
    
    // using a high-resolution clock to seed the random number generator
    unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed); // Mersenne Twister random number generator
    std::uniform_int_distribution<int> distribution(0, TILES_IN_PUZZLE_COUNT - 1);

    // Generate the crossover point
    int crossover_point = distribution(generator);

    // Perform one-point crossover
    for (int i = crossover_point; i < TILES_IN_PUZZLE_COUNT; i++){
        for (int j = 0; j < TILE_SIZE; j++){
            int temp = parent1[i][j];
            parent1[i][j] = parent2[i][j];
            parent2[i][j] = temp;
        }
    }
}

/**
 * @brief Performs a two-point crossover on two parent matrices.
 *
 * This function takes two parent matrices and performs a two-point crossover
 * to generate new offsprings. The crossover points are randomly selected using
 * a high-resolution clock to seed the random number generator. The elements
 * between the two crossover points are swapped between the two parents.
 *
 * @param parent1 A pointer to the first parent matrix.
 * @param parent2 A pointer to the second parent matrix.
 */
void twoPointCrossover(int ** parent1, int** parent2){
    // using a high-resolution clock to seed the random number generator
    unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed); // Mersenne Twister random number generator
    std::uniform_int_distribution<int> distribution(0, TILES_IN_PUZZLE_COUNT - 1);

    // Generate the crossover points
    int crossover_point1 = distribution(generator);
    int crossover_point2 = distribution(generator);

    // Ensure CrossoverPoint1 < CrossoverPoint2
    if (crossover_point1 > crossover_point2){
        int temp = crossover_point1;
        crossover_point1 = crossover_point2;
        crossover_point2 = temp;
    }

    // Perform two-point crossover
    for (int i = crossover_point1; i < crossover_point2; i++){
        for (int j = 0; j < TILE_SIZE; j++){
            int temp = parent1[i][j];
            parent1[i][j] = parent2[i][j];
            parent2[i][j] = temp;
        }
    }

}
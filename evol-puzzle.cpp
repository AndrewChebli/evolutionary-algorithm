#include "evol-puzzle.h"

/**
 * @brief Rotates the elements of the given array to the left by one index.
 * 
 * This function takes an array of integers with a size defined by TILE_SIZE
 * and shifts all elements one position to the left. The first element of the
 * array is moved to the last position.
 * 
 * @param arr The array of integers to be rotated. The size of the array must be TILE_SIZE.
 */
void rotateToLeftByOneIndex(int arr[]){
    int temp = arr[0];
    for (int i = 0; i < TILE_SIZE - 1; i++){
        arr[i] = arr[i+1];
    }
    arr[TILE_SIZE - 1] = temp;
}

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
void swapTile(int** arr){
    // Use a high-resolution clock to seed the random number generator
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

// Allocate memory for a 3D array
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

// Allocate memory for a 2D array
int** allocatePuzzle() {
    int** puzzle = new int*[TILES_IN_PUZZLE_COUNT];
    for (int i = 0; i < TILES_IN_PUZZLE_COUNT; ++i) {
        puzzle[i] = new int[TILE_SIZE];
    }
    return puzzle;
}

void freePopulation(int*** population_arr, int population_size) {
    for (int i = 0; i < population_size; ++i) {
        for (int j = 0; j < TILES_IN_PUZZLE_COUNT; ++j) {
            delete[] population_arr[i][j];
        }
        delete[] (*population_arr)[i]; 
    }
    delete[] *population_arr;
}

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

    // checking right edge mismatch
    for (int i = 8; i < TILES_IN_PUZZLE_COUNT; i++){
        if (puzzle[i][0] != puzzle[i-8][2]){
            edge_mismatch++;
        }
    }

    return edge_mismatch;
}
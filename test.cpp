#include "evol-puzzle.h"
#include <assert.h>
#include <sstream>

/**
 * @brief Compares two arrays for equality.
 * 
 * This function checks if two arrays of integers are equal by comparing
 * each element. The arrays are assumed to have a size of TILE_SIZE.
 * 
 * @param arr1 The first array to compare.
 * @param arr2 The second array to compare.
 * @return true if all elements in both arrays are equal, false otherwise.
 */
bool assertArrayEqual(const int* arr1, const int* arr2){
    for (int i = 0; i < TILE_SIZE; i++){
        if (arr1[i] != arr2[i]){
            return false;
        }
    }
    return true;
}

int main(){
    // --- Test rotateToLeftByOneIndex
    int arr[] = {1,2,3,4};
    int expected[] = {2,3,4,1};
    rotateToLeftByOneIndex(arr);
    assert(assertArrayEqual(arr, expected));

    rotateToLeftByOneIndex(arr);
    int expected2[] = {3,4,1,2};
    assert(assertArrayEqual(arr, expected2));
    // -------------------------------

    // --- Test swapTile

    int** puzzle = allocatePuzzle();
    readInput("Ass1Input.txt", puzzle);

    // second copy for comparison
    int copy_puzzle[TILES_IN_PUZZLE_COUNT][TILE_SIZE];
    for (int i = 0; i < TILES_IN_PUZZLE_COUNT; i++){
        for (int j = 0; j < TILE_SIZE; j++){
            copy_puzzle[i][j] = puzzle[i][j];
        }
    }

    swapTile(puzzle);

    // checking if swaps happened properly
    int swap_count = 0;
    for (int i = 0; i < TILES_IN_PUZZLE_COUNT; i++){
        if (!assertArrayEqual(puzzle[i], copy_puzzle[i])){
            swap_count++;
        }
    }
    assert(swap_count == 2);
    // -------------------------------
    

    // --- Test generatePopulation
    readInput("Ass1Input.txt", puzzle);
    int POPULATION_SIZE = 1000;
    //int population_arr[POPULATION_SIZE][TILES_IN_PUZZLE_COUNT][TILE_SIZE];
    int*** population_arr = allocatePopulation(POPULATION_SIZE);
    generatePopulation(population_arr, puzzle, POPULATION_SIZE);

    swap_count = 0;
    for (int i = 1; i < POPULATION_SIZE; i++){
        for (int j = 0; j < TILES_IN_PUZZLE_COUNT; j++){
            if (!assertArrayEqual(population_arr[0][j], population_arr[i][j])){
                swap_count++;
            }
        }
        assert(swap_count >= 20);
        swap_count = 0;
    }
    // ----

    // --- Test countEdgeMismatch
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < POPULATION_SIZE; i++){
        countEdgeMismatch(population_arr[i]);
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    cout << "\nTime taken to count edge mismatches in " << POPULATION_SIZE << "puzzles: " << elapsed.count() << \
    " seconds \n---> " << elapsed.count()/POPULATION_SIZE << " s/puzzle" << endl;

    // --- Test OnePointCrossover
    int** parent1 = population_arr[0];
    int** parent2 = population_arr[1];

    int initialParent1[TILES_IN_PUZZLE_COUNT][TILE_SIZE];
    int initialParent2[TILES_IN_PUZZLE_COUNT][TILE_SIZE];

    for (int i = 0; i < TILES_IN_PUZZLE_COUNT; i++) {
        for (int j = 0; j < TILE_SIZE; j++) {
            initialParent1[i][j] = parent1[i][j];
            initialParent2[i][j] = parent2[i][j];
        }
    }

    int crossoverPoint = onePointCrossover(parent1, parent2);

    // Verify the crossover operation
    for (int i = 0; i < crossoverPoint; i++) {
        for (int j = 0; j < TILE_SIZE; j++) {
            assert(assertArrayEqual(parent1[i], initialParent1[i]));
            assert(assertArrayEqual(parent2[i], initialParent2[i]));
        }
    }

    for (int i = crossoverPoint; i < TILES_IN_PUZZLE_COUNT; i++) {
        for (int j = 0; j < TILE_SIZE; j++) {
            assert(assertArrayEqual(parent1[i], initialParent2[i]));
            assert(assertArrayEqual(parent2[i], initialParent1[i]));
        }
    }

    // --- Test TwoPointCrossover
    int** parent3 = population_arr[2];
    int** parent4 = population_arr[3];
   
   // Capture the initial state of parent3 and parent4
    int initialParent3[TILES_IN_PUZZLE_COUNT][TILE_SIZE];
    int initialParent4[TILES_IN_PUZZLE_COUNT][TILE_SIZE];
    for (int i = 0; i < TILES_IN_PUZZLE_COUNT; i++) {
        for (int j = 0; j < TILE_SIZE; j++) {
            initialParent3[i][j] = parent3[i][j];
            initialParent4[i][j] = parent4[i][j];
        }
    }
    pair<int, int> crossoverPoints = twoPointCrossover(parent3, parent4);
    int point1 = crossoverPoints.first;
    int point2 = crossoverPoints.second;

    // Verify the crossover operation
    for (int i = 0; i < point1; i++) {
        assert(assertArrayEqual(parent3[i], initialParent3[i]));
        assert(assertArrayEqual(parent4[i], initialParent4[i]));
    }

    for (int i = point1; i <= point2; i++) {
        assert(assertArrayEqual(parent3[i], initialParent4[i]));
        assert(assertArrayEqual(parent4[i], initialParent3[i]));
    }

    for (int i = point2 + 1; i < TILES_IN_PUZZLE_COUNT; i++) {
        assert(assertArrayEqual(parent3[i], initialParent3[i]));
        assert(assertArrayEqual(parent4[i], initialParent4[i]));
    }

// ---

    cout << "\n\n" << "All tests passed!" << "\n\n";
}
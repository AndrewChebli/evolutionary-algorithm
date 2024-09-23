#include "evol-puzzle.h"
#include <vector>
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
bool assertArrayEqual(int arr1[TILE_SIZE], int arr2[TILE_SIZE]){
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
    int puzzle[TILES_IN_PUZZLE_COUNT][TILE_SIZE];

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
    
    cout << "\n\n" << "All tests passed!" << "\n\n";
}
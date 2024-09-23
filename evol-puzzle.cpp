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
void rotateToLeftByOneIndex(int arr[TILE_SIZE]){
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
void swapTile(int arr[TILES_IN_PUZZLE_COUNT][TILE_SIZE]){
    srand(time(0));
    int first_index = rand() % TILES_IN_PUZZLE_COUNT;
    int second_index = first_index;
    while (second_index == first_index){
        second_index = rand() % TILES_IN_PUZZLE_COUNT;
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
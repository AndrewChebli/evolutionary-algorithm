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
    ifstream test_file("Ass1Input.txt");
    
    if (!test_file) {
        cerr << "Unable to open file numbers.txt";
        return 1;
    }
    
    // Reading file into a string
    stringstream buffer;
    buffer << test_file.rdbuf();
    string content = buffer.str();

    test_file.close();

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
    int puzzle[TILES_IN_PUZZLE_COUNT][TILE_SIZE];
    for (int i = 0; i < TILES_IN_PUZZLE_COUNT; i++){
        for (int j = 0; j < TILE_SIZE; j++){
            puzzle[i][j] = digitsArray[i][j];
        }
    }

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
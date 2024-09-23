#include "evol-puzzle.h"
#include <assert.h>

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
    // ---

    
    std::cout << "All tests passed!" << std::endl;
}
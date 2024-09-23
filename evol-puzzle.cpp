#include "evol-puzzle.h"

void rotateToLeftByOneIndex(int arr[TILE_SIZE]){
    int temp = arr[0];
    for (int i = 0; i < TILE_SIZE - 1; i++){
        arr[i] = arr[i+1];
    }
    arr[TILE_SIZE - 1] = temp;
}
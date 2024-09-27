#include <iostream>
#include "evol-puzzle.h"

int main(){
    auto start = chrono::high_resolution_clock::now();

    int** puzzle = allocatePuzzle();
    readInput("Ass1Input.txt", puzzle);
    int POPULATION_SIZE = 1000;
    int NUM_OF_GENERATIONS = 100;
    int*** population_arr = allocatePopulation(POPULATION_SIZE);

    // Step 1: Initialization
    generatePopulation(population_arr, puzzle, POPULATION_SIZE);

    // Step 2-6 
    evolve(population_arr, NUM_OF_GENERATIONS, POPULATION_SIZE);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    cout << "Time taken: " << elapsed.count() << " seconds" << endl;

    delete population_arr;

    return 0;
}

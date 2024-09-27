#include <iostream>
#include "evol-puzzle.h"

int main(){
    auto start = chrono::high_resolution_clock::now();

    int** puzzle = allocatePuzzle();
    readInput("Ass1Input.txt", puzzle);
    int POPULATION_SIZE = 10000;
    int NUM_OF_GENERATIONS = 1000;
    int*** population_arr = allocatePopulation(POPULATION_SIZE);
    generatePopulation(population_arr, puzzle, POPULATION_SIZE);

    evolve(population_arr, NUM_OF_GENERATIONS, POPULATION_SIZE);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    cout << "Time taken: " << elapsed.count() << " seconds" << endl;

    return 0;
}

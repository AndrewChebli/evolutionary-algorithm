#include <iostream>
#include "evol-puzzle.h"

int main(){
    auto start = chrono::high_resolution_clock::now();

    int** puzzle = allocatePuzzle();
    readInput("Ass1Input.txt", puzzle);
    int POPULATION_SIZE = 100;
    int*** population_arr = allocatePopulation(POPULATION_SIZE);
    generatePopulation(population_arr, puzzle, POPULATION_SIZE);

    int generation = 1;
    int min = INT_MAX;
    while (generation > 0){
        for (int i = 0; i < POPULATION_SIZE; i++){
            unsigned seed = chrono::high_resolution_clock::now().time_since_epoch().count();
            mt19937 generator(seed); // Mersenne Twister random number generator
            uniform_int_distribution<int> distribution(0, TILES_IN_PUZZLE_COUNT - 1);

            int num_iterations = distribution(generator);
            for (int j = 0; j < num_iterations; j++){
                rotateToLeftByOneIndex(population_arr[i][distribution(generator)]);
            }

            for (int j = 0; j < num_iterations; j++){
                swapTile(population_arr[i]);
            }
        }

        // Perform crossovers
        for (int i = 0; i < POPULATION_SIZE; i += 2) {
            if (i + 1 < POPULATION_SIZE) {
                twoPointCrossover(population_arr[i], population_arr[i + 1]);
            }
        }
        int edge_mismatch_count = INT_MAX;

        for (int i = 0; i < POPULATION_SIZE; i++){
            edge_mismatch_count = countEdgeMismatch(population_arr[i]);
            if (edge_mismatch_count <= min){
                min = edge_mismatch_count;
            }
        }

        cout << "GEN " << generation << " " << "lowest edge mismatch: "  << min << endl;
        generation++;
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    cout << "Time taken: " << elapsed.count() << " seconds" << endl;

    return 0;
}

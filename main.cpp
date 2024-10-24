/**
 * @file main.cpp
 * @brief Main entry point for the puzzle solver application.
 * 
 * This file contains the main function which initializes the puzzle solver,
 * reads input, generates an initial population, and evolves the population
 * over a specified number of generations.
 * 
 * @details
 * The program expects an optional command-line argument:
 * - `-v` : Enables verbose output.
 * 
 * The user is prompted to input the population size and the number of generations.
 * The program then measures the time taken to evolve the population and outputs
 * the elapsed time.
 * 
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return int Exit status of the program.
 */
#include <iostream>
#include "evol-puzzle.h"


int main(int argc, char** argv){
    bool print_flag = false;
    if (argc > 1){
        if (string(argv[1]) == "-v"){
            print_flag = true;
        }
    }

    int POPULATION_SIZE;
    int NUM_OF_GENERATIONS;
    cout << "\n\nSelect population size: ";
    cin >> POPULATION_SIZE;
    cout << "Select number of generations: ";
    cin >> NUM_OF_GENERATIONS;
    auto start = chrono::high_resolution_clock::now();

    pair<mt19937, uniform_int_distribution<int>> random = getRandomGen();
    
    int** puzzle = allocatePuzzle();
    readInput("Ass1Input.txt", puzzle);
    unordered_map<string, string> map_of_tiles = buildMapOfTiles(puzzle);
    unordered_map<string, int> duplicatesMap = recordDuplicateTiles(puzzle);
    int*** population_arr = allocatePopulation(POPULATION_SIZE);

    // Step 1: Initialization
    generatePopulation(population_arr, puzzle, POPULATION_SIZE, random);

    // Step 2-6 
    evolve(population_arr, NUM_OF_GENERATIONS, POPULATION_SIZE, duplicatesMap, map_of_tiles, random, print_flag);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    cout << "Time taken: " << elapsed.count() << " seconds" << endl;

    delete population_arr;

    return 0;
}

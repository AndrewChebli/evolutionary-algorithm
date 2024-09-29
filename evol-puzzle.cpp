#include "evol-puzzle.h"


pair<mt19937, uniform_int_distribution<int>> getRandomGen(){
    // using a high-resolution clock to seed the random number generator
    unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed); // Mersenne Twister random number generator
    std::uniform_int_distribution<int> distribution(0, TILES_IN_PUZZLE_COUNT - 1);

    return make_pair(generator, distribution);
}


/**
 * @brief Rotates the elements of the given array to the left by one index.
 * 
 * This function takes an array and shifts all its elements one position to the left.
 * The first element of the array is moved to the last position.
 * 
 * @param arr The array to be rotated. The array should have a size of TILE_SIZE.
 */
void rotateToLeftByOneIndex(int arr[]){
    int temp = arr[0];
    for (int i = 0; i < TILE_SIZE - 1; i++){
        arr[i] = arr[i+1];
    }
    arr[TILE_SIZE - 1] = temp;
}

/**
 * @brief Rotates the elements of the given vector to the left by one index.
 *
 * This function takes a reference to a vector of integers and rotates its elements
 * to the left by one position. The first element of the vector is moved to the end.
 *
 * @param tile A reference to a vector of integers to be rotated.
 * @return A vector of integers after rotating the elements to the left by one index.
 */
vector<int> rotateToLeftByOneIndexReturn(vector<int> &tile){
    int temp = tile[0];
    for (int i = 0; i < TILE_SIZE - 1; i++){
        tile[i] = tile[i+1];
    }
    tile[TILE_SIZE - 1] = temp; 
    
    return tile;
}

/**
 * @brief Converts an array of integers to a vector of integers.
 * 
 * This function takes an array of integers and converts it into a 
 * std::vector<int> of the same size. The size of the array is 
 * determined by the constant TILE_SIZE.
 * 
 * @param arr The input array of integers to be converted.
 * @return std::vector<int> A vector containing the elements of the input array.
 */
vector<int> convertTileToVector(int arr[]){
    vector<int> vec(TILE_SIZE);
    
    for (int i = 0; i < TILE_SIZE; i++){
        vec[i] = arr[i];
    }

    return vec;
}

/**
 * @brief Converts a vector of integers representing a tile into a string.
 * 
 * This function takes a vector of integers and concatenates each integer
 * into a single string. The size of the vector is assumed to be TILE_SIZE.
 * 
 * @param vec A vector of integers representing the tile.
 * @return A string representation of the tile.
 */
string convertTileToString(vector<int> vec){
    string result;
    for (int i = 0; i < TILE_SIZE; i++){
        result += to_string(vec[i]);
    }
    return result;
}

string convertTileToString(int arr[]){
    string result;
    for (int i = 0; i < TILE_SIZE; i++){
        result += to_string(arr[i]);
    }
    return result;
}


/**
 * @brief Records duplicate tiles in a puzzle.
 *
 * This function takes a 2D array representing a puzzle and records the number of duplicate tiles.
 * Each tile is converted to a vector and then to a string representation. The function considers
 * all possible rotations of each tile to identify duplicates.
 *
 * @param puzzle A 2D array representing the puzzle.
 * @return An unordered_map where the keys are string representations of tiles and the values are the counts of duplicates.
 */
unordered_map<string, int> recordDuplicateTiles(int** puzzle){
    unordered_map<string, int> duplicatesMap;

    for (int i = 0; i < TILES_IN_PUZZLE_COUNT; i++){
        vector<int> tile = convertTileToVector(puzzle[i]);
        vector<string> tile_rotations_vec(TILE_SIZE);
        
        tile_rotations_vec[0] = convertTileToString(tile);

        for (int j = 1; j < TILE_SIZE; j++){
            tile_rotations_vec[j] = convertTileToString(rotateToLeftByOneIndexReturn(tile));
        }

        string hit_key = "";
        for (int j = 0; j < tile_rotations_vec.size(); j++){
            if (duplicatesMap.find(tile_rotations_vec[j]) != duplicatesMap.end()){
                hit_key = tile_rotations_vec[j];
            }
        }

        if (hit_key == ""){
            duplicatesMap[tile_rotations_vec[0]] = 1;
        }
        else{
            duplicatesMap[hit_key] = duplicatesMap[hit_key] + 1;
        }
    }

    // removing elements from map that are not duplicates
    // for (auto it = duplicatesMap.begin(); it != duplicatesMap.end();){
    //     if (it->second == 1){
    //         it = duplicatesMap.erase(it);
    //     }
    //     else{
    //         it++;
    //     }
    // }

    return duplicatesMap; 
}

unordered_map <string, string> buildMapOfTiles(int** puzzle){
    unordered_map <string, string> map_of_tiles;
    
    for (int i = 0; i < TILES_IN_PUZZLE_COUNT; i++){
        vector<int> tile = convertTileToVector(puzzle[i]);
        
        string id_tile = convertTileToString(tile);
        if (map_of_tiles.find(id_tile) == map_of_tiles.end()){
            map_of_tiles[id_tile] = id_tile;

            for (int j = 1; j < TILE_SIZE; j++){
                map_of_tiles[convertTileToString(rotateToLeftByOneIndexReturn(tile))] = id_tile;
            }
        }   
    }

    return map_of_tiles;
}


unordered_map <string, int> buildMapOfTiles(int** puzzle, const int start_index, const int end_index){
    unordered_map <string, int> map_of_tiles;

    for (int i = start_index; i < end_index; i++){
        vector<int> tile = convertTileToVector(puzzle[i]);
        vector<string> tile_rotations_vec(TILE_SIZE);
        
        tile_rotations_vec[0] = convertTileToString(tile);

        for (int j = 1; j < TILE_SIZE; j++){
            tile_rotations_vec[j] = convertTileToString(rotateToLeftByOneIndexReturn(tile));
        }

        string hit_key = "";
        for (int j = 0; j < tile_rotations_vec.size(); j++){
            if (map_of_tiles.find(tile_rotations_vec[j]) != map_of_tiles.end()){
                hit_key = tile_rotations_vec[j];
            }
        }

        if (hit_key == ""){
            map_of_tiles[tile_rotations_vec[0]] = 1;
        }
        else{
            map_of_tiles[hit_key] = map_of_tiles[hit_key] + 1;
        }
    }

    return map_of_tiles;
}

pair<bool, string> isTileInMap(const unordered_map<string, int> &map_to_search, vector<int> tile){
    vector<string> tile_rotations_vec(TILE_SIZE);

    tile_rotations_vec[0] = convertTileToString(tile);

    for (int j = 1; j < TILE_SIZE; j++){
        tile_rotations_vec[j] = convertTileToString(rotateToLeftByOneIndexReturn(tile));
    }

    int tile_rotations_vec_size = tile_rotations_vec.size();
    for (int i = 0; i < tile_rotations_vec_size; i++){
        if (map_to_search.find(tile_rotations_vec[i]) != map_to_search.end()){
            return make_pair(true, tile_rotations_vec[i]);
        }
    }
    return make_pair(false, "");
}

pair<bool, string> isTileInMap(const unordered_map<string, int> &map_to_search, string tile){
    if (map_to_search.find(tile) != map_to_search.end()){
        return make_pair(true, tile);
    }
    return make_pair(false, "");
}

pair<bool, string> isTileInMap(const unordered_map<string, string> &map_to_search, string tile){
    if (map_to_search.find(tile) != map_to_search.end()){
        return make_pair(true, map_to_search.at(tile));
    }
    return make_pair(false, "");
}


/**
 * @brief Swaps two random tiles in a 2D array.
 *
 * This function selects two distinct random indices within the range of the puzzle tiles
 * and swaps the tiles at these indices. The random selection is seeded using a high-resolution
 * clock to ensure variability.
 *
 * @param arr A pointer to a 2D array representing the puzzle tiles.
 *
 * @note The array is assumed to have a size of TILES_IN_PUZZLE_COUNT x TILE_SIZE.
 */
void swapTile(int** arr, pair<mt19937, uniform_int_distribution<int>> random){
    // using a high-resolution clock to seed the random number generator

    int first_index = random.second(random.first);
    int second_index = first_index;
    while (second_index == first_index){
        second_index = random.second(random.first);
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


/**
 * @brief Reads a puzzle input from a file and stores it in a 2D array.
 * 
 * This function reads the contents of the specified file, parses it into a 2D array of integers,
 * and stores the result in the provided 2D array `puzzle`.
 * 
 * @param filename The path to the input file containing the puzzle data.
 * @param puzzle A pointer to a 2D array where the parsed puzzle data will be stored.
 * 
 * @note The input file should contain numbers arranged in a specific format that can be parsed
 *       into a 2D array of integers.
 * @note The dimensions of the `puzzle` array should match the expected dimensions defined by
 *       `TILES_IN_PUZZLE_COUNT` and `TILE_SIZE`.
 * 
 * @throws runtime_error If the file cannot be opened.
 */
void readInput(string filename, int** puzzle){
    ifstream file(filename);
    
    if (!file) {
        cerr << "Unable to open file numbers.txt";
    }
    
    // Reading file into a string
    stringstream buffer;
    buffer << file.rdbuf();
    string content = buffer.str();

    file.close();

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
    for (int i = 0; i < TILES_IN_PUZZLE_COUNT; i++){
        for (int j = 0; j < TILE_SIZE; j++){
            puzzle[i][j] = digitsArray[i][j];
        }
    }
}


/**
 * @brief Allocates memory for a population of individuals.
 * 
 * This function allocates a 3D array to represent a population of individuals
 * for a genetic algorithm or evolutionary computation. Each individual in the 
 * population is represented by a 2D array.
 * 
 * @param population_size The number of individuals in the population.
 * @return A pointer to the allocated 3D array representing the population.
 */
int*** allocatePopulation(int population_size) {
    int*** population = new int**[population_size];
    for (int i = 0; i < population_size; ++i) {
        population[i] = new int*[TILES_IN_PUZZLE_COUNT];
        for (int j = 0; j < TILES_IN_PUZZLE_COUNT; ++j) {
            population[i][j] = new int[TILE_SIZE];
        }
    }
    return population;
}


/**
 * @brief Allocates memory for a puzzle.
 * 
 * This function dynamically allocates a 2D array to represent a puzzle.
 * The puzzle is represented as an array of pointers, where each pointer
 * points to an array of integers. The size of the puzzle and the size
 * of each tile are determined by the constants TILES_IN_PUZZLE_COUNT
 * and TILE_SIZE, respectively.
 * 
 * @return int** A pointer to the allocated 2D array representing the puzzle.
 */
int** allocatePuzzle() {
    int** puzzle = new int*[TILES_IN_PUZZLE_COUNT];
    for (int i = 0; i < TILES_IN_PUZZLE_COUNT; ++i) {
        puzzle[i] = new int[TILE_SIZE];
    }
    return puzzle;
}

/**
 * @brief Frees the memory allocated for a 2D puzzle array.
 * 
 * This function deallocates the memory for each row of the puzzle
 * and then deallocates the memory for the array of row pointers.
 * 
 * @param puzzle A pointer to the 2D array representing the puzzle.
 */
void freePuzzle(int** puzzle) {
    for (int i = 0; i < TILES_IN_PUZZLE_COUNT; ++i) {
        delete[] puzzle[i];
    }
    delete[] puzzle;
}


void freePopulation(int*** population_arr, int population_size) {
    for (int i = 0; i < population_size; i++) {
        for (int j = 0; j < TILES_IN_PUZZLE_COUNT; j++) {
            delete[] population_arr[i][j];
        }
        delete[] population_arr[i];
    }
    delete[] population_arr;
}


/**
 * @brief Generates an initial population for the puzzle solver.
 *
 * This function initializes a population array with a given size, where each 
 * individual in the population is a variation of the initial puzzle configuration.
 *
 * @param population_arr A 3D array to store the generated population. The first 
 *                       dimension represents the population size, the second 
 *                       dimension represents the tiles in the puzzle, and the 
 *                       third dimension represents the size of each tile.
 * @param arr A 2D array representing the initial puzzle configuration. The first 
 *            dimension represents the tiles in the puzzle, and the second dimension 
 *            represents the size of each tile.
 * @param population_size The number of individuals in the population.
 */
void generatePopulation(int*** population_arr, int** arr, int population_size, pair<mt19937, uniform_int_distribution<int>> random){

        int** arr_copy = allocatePuzzle();

        for (int i = 0; i < TILES_IN_PUZZLE_COUNT; i++){
            for (int j = 0; j < TILE_SIZE; j++){
                arr_copy[i][j] = arr[i][j];
            }
        }

        for (int i = 0; i < TILES_IN_PUZZLE_COUNT; i++){
            for (int j = 0; j < TILE_SIZE; j++){
                population_arr[0][i][j] = arr_copy[i][j];
            }
        }

        #pragma omp parallel for
        for (int i = 1; i < population_size; i++){
            for (int j = 0; j < TILES_IN_PUZZLE_COUNT/2; j++){
                swapTile(arr_copy, random);
            }
            
            for (int j = 0; j < TILES_IN_PUZZLE_COUNT; j++){
                for (int p = 0; p < TILE_SIZE; p++){
                    population_arr[i][j][p] = arr_copy[j][p];
                }
            }
        }
        
        freePuzzle(arr_copy);
}


/**
 * @brief Counts the number of edge mismatches in a given puzzle.
 *
 * This function checks the mismatches between adjacent tiles in a puzzle.
 * It considers both the left and top edges of each tile and compares them
 * with the corresponding edges of the neighboring tiles.
 *
 * @param puzzle A 2D array representing the puzzle, where each tile is an array of edges.
 *               The edges are assumed to be in the following order:
 *               [top, right, bottom, left].
 * @return The total number of edge mismatches in the puzzle.
 */
int countEdgeMismatch(int** puzzle){
    int edge_mismatch = 0;
    
    // checking left edge mismatch
    for (int i = 0; i < TILES_IN_PUZZLE_COUNT; i++){
        if (i % 8 == 0){
            continue;
        }

        if (puzzle[i][3] != puzzle[i-1][1]){
            edge_mismatch++;
        }
    }

    // checking top edge mismatch
    for (int i = 8; i < TILES_IN_PUZZLE_COUNT; i++){
        if (puzzle[i][0] != puzzle[i-8][2]){
            edge_mismatch++;
        }
    }

    return edge_mismatch;
}

/**
 * @brief Performs a one-point crossover on two parent matrices.
 * 
 * This function takes two parent matrices and performs a one-point crossover
 * to generate new offsprings. The crossover point is chosen randomly, and the 
 * elements of the matrices are swapped at that point to create new offspring.
 * 
 * @param parent1 A pointer to the first parent matrix.
 * @param parent2 A pointer to the second parent matrix.
 */
int onePointCrossover(int** offspring1, int** offspring2){
    // TODO: Create function to take care of random number generation and seeding
    
    // using a high-resolution clock to seed the random number generator
    unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed); // Mersenne Twister random number generator
    std::uniform_int_distribution<int> distribution(0, TILES_IN_PUZZLE_COUNT - 1);

    // Generate the crossover point
    int crossover_point = distribution(generator);

    // Perform one-point crossover
    for (int i = crossover_point; i < TILES_IN_PUZZLE_COUNT; i++){
        for (int j = 0; j < TILE_SIZE; j++){
            int temp = offspring1[i][j];
            offspring1[i][j] = offspring2[i][j];
            offspring2[i][j] = temp;
        }
    }

    return crossover_point;
}


/**
 * @brief Performs a two-point crossover on two parent matrices.
 *
 * This function takes two parent matrices and performs a two-point crossover
 * to generate new offsprings. The crossover points are randomly selected using
 * a high-resolution clock to seed the random number generator. The elements
 * between the two crossover points are swapped between the two parents.
 *
 * @param parent1 A pointer to the first parent matrix.
 * @param parent2 A pointer to the second parent matrix.
 */
pair<int, int>  twoPointCrossover(int** offspring1, int** offspring2){
    // using a high-resolution clock to seed the random number generator
    unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed); // Mersenne Twister random number generator
    std::uniform_int_distribution<int> distribution(0, TILES_IN_PUZZLE_COUNT - 1);

    // Generate the crossover points
    int crossover_point1 = distribution(generator);
    int crossover_point2 = distribution(generator);

    // Ensure CrossoverPoint1 < CrossoverPoint2
    if (crossover_point1 > crossover_point2){
        int temp = crossover_point1;
        crossover_point1 = crossover_point2;
        crossover_point2 = temp;
    }

    // Perform two-point crossover
    for (int i = crossover_point1; i <= crossover_point2; i++){
        for (int j = 0; j < TILE_SIZE; j++){
            int temp = offspring1[i][j];
            offspring1[i][j] = offspring2[i][j];
            offspring2[i][j] = temp;
        }
    }

    return make_pair(crossover_point1, crossover_point2);
}

void orderCrossover(int** offspring1, int** offspring2, const unordered_map<string, int> &duplicatesMap, const unordered_map<string, string> &map_of_tiles, pair<mt19937, uniform_int_distribution<int>> random){

    int** parent1 = allocatePuzzle();
    int** parent2 = allocatePuzzle();
    copyPuzzle(offspring1, parent1);
    copyPuzzle(offspring2, parent2);

    unordered_map<string, int> trackedDuplicates1 = duplicatesMap;
    for (auto it = trackedDuplicates1.begin(); it != trackedDuplicates1.end(); it++){
        it->second = 0;
    }
    unordered_map<string, int> trackedDuplicates2 = trackedDuplicates1;

    // Generate the crossover points
    int crossover_point1 = random.second(random.first);
    int crossover_point2 = random.second(random.first);

    // Ensure CrossoverPoint1 < CrossoverPoint2
    if (crossover_point1 > crossover_point2){
        int temp = crossover_point1;
        crossover_point1 = crossover_point2;
        crossover_point2 = temp;
    }
    
    // Perform two-point crossover
    for (int i = crossover_point1; i < crossover_point2; i++){
        copyTile(parent1[i], offspring2[i]);
        copyTile(parent2[i], offspring1[i]);
    }

    // updating trackedDuplicates maps based on what's in between crossover points.
    for (int i = crossover_point1; i < crossover_point2; i++){
        string parent1_tile = convertTileToString(parent1[i]);
        string parent2_tile = convertTileToString(parent2[i]);

        pair<bool, string> tile1_found = isTileInMap(map_of_tiles, parent1_tile);
        if (tile1_found.first){
            trackedDuplicates1[tile1_found.second]++;
        }

        pair<bool, string> tile2_found = isTileInMap(map_of_tiles, parent2_tile);
        if (tile2_found.first){
            trackedDuplicates2[tile2_found.second]++;
        }
    }

    //copy what is not between crossover points from parent2 to offspring2
    int count_limit = TILES_IN_PUZZLE_COUNT - (crossover_point2 - crossover_point1);
    for (int i = crossover_point2, j = i, count = 0; count < count_limit; i = (i + 1) % TILES_IN_PUZZLE_COUNT){
        pair<bool, string> tile_found = isTileInMap(trackedDuplicates2, map_of_tiles.at(convertTileToString(parent2[i])));

        if ((trackedDuplicates1[tile_found.second] < duplicatesMap.at(tile_found.second))){
            copyTile(parent2[i], offspring2[j]);
            trackedDuplicates1[tile_found.second]++;
            j = (j + 1) % TILES_IN_PUZZLE_COUNT;
            count++;
        }

    }

    //copy what is not between crossover points from parent1 to offspring1
    for (int i = crossover_point2, j = i, count = 0; count < count_limit; i = (i + 1) % TILES_IN_PUZZLE_COUNT){
        pair<bool, string> tile_found = isTileInMap(trackedDuplicates2, map_of_tiles.at(convertTileToString(parent1[i])));

        if ((trackedDuplicates2[tile_found.second] < duplicatesMap.at(tile_found.second))){
            copyTile(parent1[i], offspring1[j]);
            trackedDuplicates2[tile_found.second]++;
            j = (j + 1) % TILES_IN_PUZZLE_COUNT;
            count++;
        }

    }
    freePuzzle(parent1);
    freePuzzle(parent2);

}

/**
 * @brief Evolves a population of solutions over a specified number of generations.
 *
 * This function performs genetic algorithm operations such as crossover and mutation
 * on a population of solutions. It evaluates the fitness of the population after each
 * generation and tracks the minimum edge mismatch count.
 *
 * @param population_arr A pointer to a 3D array representing the population of solutions.
 * @param NUM_OF_GENERATIONS The number of generations to evolve the population.
 * @param POPULATION_SIZE The size of the population.
 */
void evolve(int*** population_arr, int NUM_OF_GENERATIONS, const int POPULATION_SIZE, const unordered_map<string, int> &duplicatesMap, const unordered_map<string, string> &map_of_tiles,pair<mt19937, uniform_int_distribution<int>> random){
    int min_edge_mismatch_count = INT_MAX;
    int generations_performed = 1;
    int stagnated_generation_count = 0;
    float ratio = 0.5;
    int** best_puzzle_so_far = allocatePuzzle();
    int*** offspring_arr = allocatePopulation(POPULATION_SIZE * ratio);
    while (min_edge_mismatch_count != 0){
    //while (generations_performed <= NUM_OF_GENERATIONS){
        //refreshing random gen
        random = getRandomGen();
        
        // Step 2: Evaluate Fitness
        vector<pair<int, int>> sorted_index_by_fitness_vec = evaluateFitness(population_arr, POPULATION_SIZE); //<index, edgeMismatchCount>

        if (sorted_index_by_fitness_vec.back().second < min_edge_mismatch_count){
            best_puzzle_so_far = population_arr[sorted_index_by_fitness_vec.back().first];
            printPuzzle(best_puzzle_so_far);
            if (sorted_index_by_fitness_vec.back().second <= 25){
                savePuzzle(best_puzzle_so_far, sorted_index_by_fitness_vec.back().second);
            }
            stagnated_generation_count = 0;
        }

        // when fitness plateaus, will regenerate population with the best puzzle so far as the seed
        if (++stagnated_generation_count == 1000 || stagnated_generation_count == 10000 || stagnated_generation_count == 100000){
            generatePopulation(population_arr, best_puzzle_so_far, POPULATION_SIZE, random);
            if (stagnated_generation_count == 100000){
                stagnated_generation_count = 0;
            }
        }

        min_edge_mismatch_count = min(min_edge_mismatch_count, sorted_index_by_fitness_vec.back().second);

        // Step 3: Termination Criteria (either best solution found or all generations elapsed)
        if (min_edge_mismatch_count == 0){
            break;
        }
        
        // Step 4: Select Parents
        pair<vector<int>, vector<int>> parents_and_worst_indexes_pair = selectParentsAndWorst(population_arr, POPULATION_SIZE, sorted_index_by_fitness_vec, ratio);
        vector<int> parent_index_vec = parents_and_worst_indexes_pair.first;
        vector<int> worst_index_vec = parents_and_worst_indexes_pair.second;

        // Step 5: Offspring generation
        crossover(population_arr, POPULATION_SIZE, parent_index_vec, offspring_arr, duplicatesMap, map_of_tiles, random);
        mutate(offspring_arr, POPULATION_SIZE * ratio, random);

        // Step 6: Survivor Selection
        selectSurvivorsAndReplace(population_arr, POPULATION_SIZE, worst_index_vec, offspring_arr);

        cout << "GEN " << generations_performed << " " << " edge mismatch: "  << sorted_index_by_fitness_vec.back().second \
        << " ... lowest edge mismatch: " << min_edge_mismatch_count << endl;
        generations_performed++;
    }

    freePuzzle(best_puzzle_so_far);
    freePopulation(offspring_arr, POPULATION_SIZE * ratio);
}

/**
 * @brief Mutates a population of puzzles by performing random rotations and swaps.
 * 
 * This function iterates over each puzzle in the population and performs a series of 
 * random rotations and swaps on the tiles within each puzzle. The number of rotations 
 * and swaps is determined randomly for each puzzle.
 * 
 * @param population_arr A 3D array representing the population of puzzles.
 * @param POPULATION_SIZE The number of puzzles in the population.
 * 
 * The function uses the Mersenne Twister random number generator to ensure high-quality 
 * randomness. For each puzzle, it generates a random number of iterations and performs 
 * the following operations:
 * - Rotates a randomly selected tile to the left by one index.
 * - Swaps tiles within the puzzle.
 */
void mutate(int*** offspring_arr, const int POPULATION_SIZE, pair<mt19937, uniform_int_distribution<int>> random){
    for (int i = 0; i < POPULATION_SIZE; i++){

        int num_iterations = random.second(random.first);
        for (int j = 0; j < num_iterations; j++){
            rotateToLeftByOneIndex(offspring_arr[i][random.second(random.first)]);
        }

        for (int j = 0; j < num_iterations; j++){
            swapTile(offspring_arr[i], random);
        }
    }
}

/**
 * @brief Performs crossover operation on a population array.
 * 
 * This function iterates through the population array in pairs and applies
 * a two-point crossover operation on each pair. The crossover is performed
 * only if there is a valid pair (i.e., the second individual in the pair exists).
 * 
 * @param population_arr A pointer to the population array, where each individual
 *                       is represented as a pointer to an array of integers.
 * @param POPULATION_SIZE The size of the population array.
 */
void crossover(int*** population_arr, const int POPULATION_SIZE, const vector<int> &parent_index_vec, int*** offspring_arr, const unordered_map<string, int> &duplicatesMap, const unordered_map<string, string> &map_of_tiles, pair<mt19937, uniform_int_distribution<int>> random){
    int parent_index_vec_size = parent_index_vec.size();

    int** offspring1 = allocatePuzzle();
    int** offspring2 = allocatePuzzle();

    for (int i = 0; i < parent_index_vec_size; i += 2) {
        if (i + 1 < parent_index_vec_size) {
            copyPuzzle(population_arr[parent_index_vec[i]], offspring1);
            copyPuzzle(population_arr[parent_index_vec[i + 1]], offspring2);

            orderCrossover(offspring1, offspring2, duplicatesMap, map_of_tiles, random);

            copyPuzzle(offspring1, offspring_arr[i]);
            copyPuzzle(offspring2, offspring_arr[i + 1]);
        }
    }

    freePuzzle(offspring1);
    freePuzzle(offspring2);

}


/**
 * @brief Evaluates the fitness of a population of puzzle solutions.
 *
 * This function takes a population of puzzle solutions and evaluates their fitness
 * by counting the edge mismatches for each solution. It returns a vector of pairs,
 * where each pair contains the index of the solution and its corresponding fitness
 * value (edge mismatch count). The vector is sorted in descending order of fitness.
 *
 * @param population_arr A 3D array representing the population of puzzle solutions.
 * @param POPULATION_SIZE The size of the population.
 * @return A vector of pairs, where each pair contains the index of the solution and
 *         its corresponding fitness value, sorted in descending order of fitness.
 */
vector<pair<int, int>> evaluateFitness(int*** population_arr, const int POPULATION_SIZE){

    vector<pair<int, int>> sorted_index_by_fitness_vec;

    for (int i = 0; i < POPULATION_SIZE; i++){
        sorted_index_by_fitness_vec.push_back(make_pair(i, countEdgeMismatch(population_arr[i])));
    }

    sort(sorted_index_by_fitness_vec.begin(), sorted_index_by_fitness_vec.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second; // sort by edge mismatch count
    });

    return sorted_index_by_fitness_vec;
}

pair<vector<int>, vector<int>> selectParentsAndWorst(int*** population_arr, const int POPULATION_SIZE, const vector<pair<int, int>> &sorted_index_by_fitness_vec, const float ratio){
    
    // ratio is percentage of top ranking puzzles to select as parents
    int starting_point_parents = POPULATION_SIZE - POPULATION_SIZE * ratio;
    int threshold_worst = POPULATION_SIZE * ratio;

    vector<int> parents_index_vec;
    for (int i = starting_point_parents; i < POPULATION_SIZE; i++){
        parents_index_vec.push_back(sorted_index_by_fitness_vec[i].first);
    }

    vector<int> worst_index_vec;
    for (int i = 0; i < threshold_worst; i++){
        worst_index_vec.push_back(sorted_index_by_fitness_vec[i].first);
    }

    return make_pair(parents_index_vec, worst_index_vec);
}

void selectSurvivorsAndReplace(int*** population_arr, const int POPULATION_SIZE, const vector<int> &worst_index_vec, int*** offspring_arr){
    int size = worst_index_vec.size();
    for (int i = 0; i < size; i++){
        copyPuzzle(offspring_arr[i], population_arr[worst_index_vec[i]]);
    }
}

int calculateDiversity(int*** population_arr, const int POPULATION_SIZE) {
    // TODO

    return 0;
}

void copyPuzzle(int** source_puzzle, int** dest_puzzle){
    for (int i = 0; i < TILES_IN_PUZZLE_COUNT; i++){
        for (int j = 0; j < TILE_SIZE; j++){
            dest_puzzle[i][j] = source_puzzle[i][j];
        }
    }
}

void copyTile(int* source_tile, int* dest_tile){
    for (int i = 0; i < TILE_SIZE; i++){
        dest_tile[i] = source_tile[i];
    }
}

void writePuzzleIntoPopulation(int*** destination_population, int POPULATION_SIZE, int** source_puzzle){
    for (int i = 0; i < POPULATION_SIZE; i++){
        for (int j = 0; j < TILES_IN_PUZZLE_COUNT; j++){
            for (int p = 0; p < TILE_SIZE; p++){
                destination_population[i][j][p] = source_puzzle[j][p];
            }
        }
    }
}

void printPuzzle(int** puzzle){
    for (int i = 0; i < TILES_IN_PUZZLE_COUNT; i++){
        if (i % 8 == 0){
            cout << endl;
        }
        for (int j = 0; j < TILE_SIZE; j++){
            cout << puzzle[i][j];
        }
        cout << " ";
    }
    cout << "\n\n";
}

void savePuzzle(int** puzzle, int edge_mismatch_count) {
    int status = mkdir("output", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    if (status != 0 && errno != EEXIST) {
        cerr << "Unable to create directory 'output'";
        return;
    }
    // get current time and date
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm* now_tm = std::localtime(&now_time);

    // format the time and date
    char time_buffer[100];
    std::strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d-%H-%M-%S", now_tm);

    std::ostringstream filename;
    filename << "output/Ass1Output-" << edge_mismatch_count << "-" << time_buffer << ".txt";

    ofstream file(filename.str());
    if (!file) {
        cerr << "Unable to open file " << filename.str() << " for writing";
        return;
    }

    for (int i = 0; i < TILES_IN_PUZZLE_COUNT; i++) {
        if (i % 8 == 0 && i != 0) {
            file << endl;
        }
        for (int j = 0; j < TILE_SIZE; j++) {
            file << puzzle[i][j];
        }
        if ((i + 1) % 8 != 0) {
            file << " ";
        }
    }
    file << "\n\n";
    file.close();
}
#pragma once
#include <string>

inline int NODES_NUMBER;
inline const int POPULATION_SIZE = 200;
inline const int NUMBER_OF_ITERATIONS = 50;
inline const double IS_SOLUTION_POINTS = 40;
inline const double INERTIA = 1;
inline const bool GLOBAL_BEST_SELECTED = false;
inline const double LIMIT_FOR_NEIGHBOURHOOD{ 5 };

inline const std::string FILE_PATH_TO_GRAPH{ "intrare.txt" };
inline std::string FILE_PATH_TO_RESULTS{ "iesire.txt" };
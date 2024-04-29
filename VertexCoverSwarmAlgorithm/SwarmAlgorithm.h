#pragma once
#include <map>
#include "Individual.h"
class SwarmAlgorithm 
{
public:
	SwarmAlgorithm(Graph* graph);
private:
	Graph* workingGraph;
	std::vector<Individual*> population;
	std::map<double, std::vector <Individual* >> mapOfScores;
};
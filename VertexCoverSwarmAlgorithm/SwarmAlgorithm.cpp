#include "SwarmAlgorithm.h"

SwarmAlgorithm::SwarmAlgorithm(Graph* graph)
{
	workingGraph = graph;
	while (population.size() != POPULATION_SIZE)
	{
		population.emplace_back(new Individual{ graph });
	}
}
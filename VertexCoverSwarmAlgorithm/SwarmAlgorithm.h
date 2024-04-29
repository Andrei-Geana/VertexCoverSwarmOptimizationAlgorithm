#pragma once
#include <map>
#include <chrono>
#include <fstream>
#include "Individual.h"
class SwarmAlgorithm 
{
public:
	SwarmAlgorithm(Graph* graph);
	~SwarmAlgorithm();
	void RunAlgorithm();
	void MakeIteration();
	void ResetBestIndividualForGlobalBest();
	void ResetBestIndividualForNeighbourBest();
	void RemakeMapOfScores();
	void UpdateAllGenes();

	void PrintPopulation() const;

	void SaveResults(const std::string& FilePath = FILE_PATH_TO_RESULTS) const;
private:
	Individual* GetBestIndividualInPopulation() const;

private:
	Graph* workingGraph;
	std::vector<Individual*> population;
	std::map<double, std::vector <Individual* >> mapOfScores;
	Individual* bestIndividualInPopulation;
	std::vector<Individual*> bestIndividualAcrossAlgorithm;
};
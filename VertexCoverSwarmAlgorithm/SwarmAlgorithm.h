#pragma once
#include <map>
#include <chrono>
#include <fstream>
#include "Individual.h"
class SwarmAlgorithm 
{
public:
	SwarmAlgorithm(Graph* graph);
	SwarmAlgorithm(Graph* graph, const std::vector<Individual*>& newPopulation);
	~SwarmAlgorithm();
	Individual* RunAlgorithm();
	void MakeIteration();

	//Global selection
	void ResetBestIndividualForGlobalBest();
	void RemakeMapOfScores();
	//Neighbourhood selection
	void ResetBestIndividualForNeighbourBest();
	//Selection + Mutation
	void UpdateAllGenes();


	void PrintPopulation() const;

	void SaveResults(const std::string& FilePath = FILE_PATH_TO_RESULTS) const;

public:

	static std::vector<Individual*> GeneratePopulation(Graph* graph);

private:
	Individual* GetBestIndividualInPopulation() const;

private:
	Graph* workingGraph;
	std::vector<Individual*> population;
	std::map<double, std::vector <Individual* >> mapOfScores;
	Individual* bestIndividualInPopulation;
	std::vector<Individual*> bestIndividualAcrossAlgorithm;
};
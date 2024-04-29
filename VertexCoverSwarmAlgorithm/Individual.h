#pragma once
#include "Genes.h"
#include "Graph.h"

#include <iostream>
#include <vector>
#include <random>

class Individual
{
public:
    Individual(Graph* workingGraph, Genes* chromosomes);
    Individual(Graph* workingGraph);
    Individual(Individual* i);
    void SetBestIndividualInPopulation(Individual* individ);
    void UpdateGenes();
public:

    friend std::ostream& operator<<(std::ostream& out, const Individual& individ);

private:
    double GetFitnessScore() const;

    int GetNumberOf1s() const;


private:
    Graph* baseGraph;
    Genes* genes;
    std::vector<double> velocity;
    Genes* bestPreviousGenes;
    Individual* bestIndividualInPopulation;
    double currentScore;
    double bestPreviousScore;
};


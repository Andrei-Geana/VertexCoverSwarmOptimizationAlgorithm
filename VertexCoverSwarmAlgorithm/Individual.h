#pragma once
#include <iostream>
#include <vector>
#include <random>
#include "Genes.h"
#include "Graph.h"
#include "AlgorithmData.h"

class Individual
{
public:
    Individual() {/*EMPTY*/ }

    Individual(Graph* workingGraph, Genes* chromosomes);

    Individual(Individual* i);

public:

    friend std::ostream& operator<<(std::ostream& out, const Individual& individ);

    static double GetChance(double min = 0, double max = 1);

private:
    double GetFitnessScore() const;

    int GetNumberOf1s() const;

private:
    Graph* baseGraph;
    Genes* genes;
    Genes* bestPreviousGenes;
    Genes* bestGenesInPopulation;
    double currentScore;
    double bestPreviousScore;
};


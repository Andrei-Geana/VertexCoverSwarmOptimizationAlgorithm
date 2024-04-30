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
    Individual(Individual* i, bool choice);
    void SetBestIndividualInPopulation(Individual* individ);
    void UpdateGenes();

    Genes* GetGenes() const;

    double GetScore() const;

public:
    class IsEqual
    {
    public:
        bool operator()(const Individual& a, const Individual& b) const
        {
            return a.genes->chromosome == b.genes->chromosome;
        }
    };

    class Hash
    {
    public:
        size_t operator()(const Individual& p) const
        {
            std::hash<bool> hasher;
            size_t answer = 0;
            for (const bool& i : p.genes->chromosome)
            {
                answer ^= hasher(i) + 0x9e3779b9 +
                    (answer << 6) + (answer >> 2);
            }
            return answer;
        }
    };
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


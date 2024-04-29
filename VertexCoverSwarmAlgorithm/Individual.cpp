#include "Individual.h"

inline Individual::Individual(Graph* workingGraph, Genes* chromosomes)
{
    baseGraph = workingGraph;
    genes = chromosomes;
    currentScore = GetFitnessScore();
}

inline Individual::Individual(Individual* i)
{
    baseGraph = i->baseGraph;
    genes = i->genes;
    bestPreviousGenes = i->bestPreviousGenes;
    bestGenesInPopulation = i->bestGenesInPopulation;
    currentScore = i->currentScore;
    bestPreviousScore = i->bestPreviousScore;
}

inline double Individual::GetChance(double min, double max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distrib(min, max);
    return distrib(gen);
}

double Individual::GetFitnessScore() const
{
    double score{ 0.0 };
    score = ((int)genes->chromosome.size() - GetNumberOf1s());
    score += (baseGraph->GetNumberOfArches() - baseGraph->GetNumberOfNotVerifiedArch(genes));
    score += baseGraph->IsSolution(genes) * IsSolutionPoints;
    return score;
}

int Individual::GetNumberOf1s() const
{
    int count{ 0 };
    for (const auto& chromosome : genes->chromosome)
    {
        if (chromosome)
            count++;
    }
    return count;

}

std::ostream& operator<<(std::ostream& out, const Individual& individ)
{
    out << "Genes: ";
    for (const auto& chromosome : individ.genes->chromosome)
    {
        out << chromosome << ' ';
    }
    out << "\tScore: " << individ.currentScore << std::endl;
    return out;
}

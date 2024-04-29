#include "Individual.h"

inline Individual::Individual(): baseGraph{nullptr}, genes{nullptr}, bestPreviousGenes{nullptr}, bestIndividualInPopulation{nullptr}
{
    /*EMPTY*/
}

inline Individual::Individual(Graph* workingGraph, Genes* chromosomes)
{
    baseGraph = workingGraph;
    genes = chromosomes;
    currentScore = GetFitnessScore();
    velocity.resize(NODES_NUMBER, 0);
}

inline Individual::Individual(Graph* workingGraph) : baseGraph{ workingGraph }, genes{ Genes::GetGenes(NODES_NUMBER)}, bestPreviousGenes{nullptr}, bestIndividualInPopulation{nullptr},
currentScore{ GetFitnessScore() }, bestPreviousScore{ 0.0 }
{
    velocity.resize(NODES_NUMBER, 0);
}

inline Individual::Individual(Individual* i): baseGraph { i->baseGraph }, genes{ i->genes }, bestPreviousGenes{ i->bestPreviousGenes }, bestIndividualInPopulation{ i->bestIndividualInPopulation },
currentScore{ i->currentScore }, bestPreviousScore{ i->bestPreviousScore }
{
    /*EMTPY*/
}

void Individual::SetBestIndividualInPopulation(Individual* individ)
{
    bestIndividualInPopulation = individ;
}


double Individual::GetFitnessScore() const
{
    double score{ 0.0 };
    score = ((int)genes->chromosome.size() - GetNumberOf1s());
    score += (baseGraph->GetNumberOfArches() - baseGraph->GetNumberOfNotVerifiedArch(genes));
    score += baseGraph->IsSolution(genes) * IS_SOLUTION_POINTS;
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

void Individual::UpdateGenes()
{
    double newValue{ 0.0 }, phi1{ 0.0 }, phi2{ 0.0 };
    for (size_t index{ 0u }; index < genes->chromosome.size(); ++index)
    {
        newValue = INERTIA * velocity[index];
        if (bestPreviousGenes != nullptr)
        {
            phi1 = Helper::GetChance();
            newValue += phi1 * (bestPreviousGenes->chromosome[index] - genes->chromosome[index]);
        }

        if (bestIndividualInPopulation != nullptr)
        {
            phi2 = Helper::GetChance();
            newValue += phi2 * (bestIndividualInPopulation->genes->chromosome[index] - genes->chromosome[index]);
        }

        velocity[index] = newValue;
        if (Helper::GetChance() < Helper::SigmoidFunction(velocity[index]))
        {
            genes[index] = 1;
        }
        else
        {
            genes[index] = 0;
        }
    }
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

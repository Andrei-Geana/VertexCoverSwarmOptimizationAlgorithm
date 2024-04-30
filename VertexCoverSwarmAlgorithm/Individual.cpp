#include "Individual.h"

Individual::Individual(Graph* workingGraph, Genes* chromosomes)
{
    baseGraph = workingGraph;
    genes = new Genes{ chromosomes };
    currentScore = GetFitnessScore();
    velocity.resize(NODES_NUMBER, 0);
}

Individual::Individual(Graph* workingGraph) : baseGraph{ workingGraph }, genes{ Genes::GetGenes(NODES_NUMBER)}, bestPreviousGenes{nullptr}, bestIndividualInPopulation{nullptr},
currentScore{ GetFitnessScore() }, bestPreviousScore{ 0.0 }
{
    velocity.resize(NODES_NUMBER, 0);
}

Individual::Individual(Individual* i, bool choice) : baseGraph{ i->baseGraph }, genes{ new Genes{i->genes} }, bestPreviousGenes{ i->bestPreviousGenes }, bestIndividualInPopulation{ i->bestIndividualInPopulation },
currentScore{ i->currentScore }, bestPreviousScore{ i->bestPreviousScore }, velocity{ i->velocity }
{
    //if i want just the genes and score
    if (choice == true)
    {
        baseGraph = i->baseGraph;
        genes = new Genes{ i->genes };
        currentScore = i->currentScore;
    }
    //if i want "deep" copy
    else
    {
        baseGraph = i->baseGraph;
        genes = new Genes{ i->genes };
        currentScore = i->currentScore;
        bestPreviousGenes = i->bestPreviousGenes;
        bestIndividualInPopulation = i->bestIndividualInPopulation;
        bestPreviousScore = i->bestPreviousScore;
        velocity = i->velocity;
    }
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
    Genes* copyOfCurrentGenes = new Genes{ genes };

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

        auto s = Helper::SigmoidFunction(velocity[index]);
        auto chance = Helper::GetChance();
        if (chance < s)
        {
            genes->chromosome[index] = 1;
        }
        else
        {
            genes->chromosome[index] = 0;
        }
    }

    if (currentScore > bestPreviousScore)
    {
        if(bestPreviousGenes != nullptr)
            delete(bestPreviousGenes);
        bestPreviousGenes = copyOfCurrentGenes;
        bestPreviousScore = currentScore;
    }

    currentScore = GetFitnessScore();

}

Genes* Individual::GetGenes() const
{
    return genes;
}

double Individual::GetScore() const
{
    return currentScore;
}

std::ostream& operator<<(std::ostream& out, const Individual& individ)
{
    out << "Genes: ";
    for (const auto& chromosome : individ.genes->chromosome)
    {
        out << chromosome << ' ';
    }
    out << "\tScore: " << individ.currentScore;
    return out;
}

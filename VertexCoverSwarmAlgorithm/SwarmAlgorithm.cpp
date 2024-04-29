#include "SwarmAlgorithm.h"

SwarmAlgorithm::SwarmAlgorithm(Graph* graph)
{
	workingGraph = graph;
	while (population.size() != POPULATION_SIZE)
	{
		population.emplace_back(new Individual{ graph });
	}
}

SwarmAlgorithm::~SwarmAlgorithm()
{
	for (const auto& individual : population)
		delete(individual);
	mapOfScores.clear();
}

void SwarmAlgorithm::RunAlgorithm()
{
    std::cout << "---------------------------------------------------------------" << std::endl << "EPOCHS: " << std::endl;

    auto startTime = std::chrono::high_resolution_clock::now();

    size_t indexOfIteration{ 0u };
    while (indexOfIteration < NUMBER_OF_ITERATIONS)
    {
        MakeIteration();
        indexOfIteration++;
		try 
		{
			SaveResults();
		}
		catch (std::exception w)
		{
			std::cout << w.what();
		}
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    std::cout << "Time taken: " << duration << " milliseconds\n";
}

void SwarmAlgorithm::MakeIteration()
{
	ResetBestIndividualForGlobalBest();

	bestIndividualAcrossAlgorithm.emplace_back(new Individual{ bestIndividualInPopulation });
	std::cout << *bestIndividualInPopulation << std::endl;

	RemakeMapOfScores();
	UpdateAllGenes();
}

void SwarmAlgorithm::ResetBestIndividualForGlobalBest()
{
	bestIndividualInPopulation = population[0];
	for (const auto& individual : population) 
	{
		if (individual->GetScore() > bestIndividualInPopulation->GetScore())
		{
			bestIndividualInPopulation = individual;
		}
	}
	for (auto& individual : population)
	{
		individual->SetBestIndividualInPopulation(bestIndividualInPopulation);
	}
}

void SwarmAlgorithm::RemakeMapOfScores()
{
	mapOfScores.clear();
	for (const auto& individual : population)
	{
		mapOfScores[individual->GetScore()].emplace_back(individual);
	}
}

void SwarmAlgorithm::UpdateAllGenes()
{
	for (auto& individual : population)
	{
		if (individual == bestIndividualInPopulation)
			continue;
		individual->UpdateGenes();
	}
	bestIndividualInPopulation->UpdateGenes();
}

void SwarmAlgorithm::SaveResults(const std::string& FilePath) const
{
	std::ofstream out(FilePath);
	if (!out)
		throw std::exception("Unable to open file to write results.\n");
	for (const auto& individ : bestIndividualAcrossAlgorithm)
	{
		out << *individ << std::endl;
	}
	out.close();
}

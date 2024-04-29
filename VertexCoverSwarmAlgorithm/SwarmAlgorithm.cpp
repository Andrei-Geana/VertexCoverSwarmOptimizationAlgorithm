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
	if (GLOBAL_BEST_SELECTED)
	{
		ResetBestIndividualForGlobalBest();
		bestIndividualAcrossAlgorithm.emplace_back(new Individual{ bestIndividualInPopulation });
	}
	else
	{
		RemakeMapOfScores();
		ResetBestIndividualForNeighbourBest();
		bestIndividualInPopulation = mapOfScores.rbegin()->second[0];
		bestIndividualAcrossAlgorithm.emplace_back(new Individual{ bestIndividualInPopulation });
	}
	std::cout << *bestIndividualInPopulation << std::endl;

	UpdateAllGenes();
}

void SwarmAlgorithm::ResetBestIndividualForGlobalBest()
{
	bestIndividualInPopulation = GetBestIndividualInPopulation();
	for (auto& individual : population)
	{
		individual->SetBestIndividualInPopulation(bestIndividualInPopulation);
	}
}

void SwarmAlgorithm::ResetBestIndividualForNeighbourBest()
{
	for(auto& individual : population)
	{
		Individual* bestNeighbour = nullptr;
		for (auto iterator = mapOfScores.rbegin(); iterator != mapOfScores.rend(); ++iterator)
		{
			auto& score = iterator->first;
			auto& neighbour = iterator->second[0];
			if (score > individual->GetScore() - LIMIT_FOR_NEIGHBOURHOOD && score < individual->GetScore() + LIMIT_FOR_NEIGHBOURHOOD)
			{
				bestNeighbour = neighbour;
				break;
			}
		}
		individual->SetBestIndividualInPopulation(bestNeighbour);

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

void SwarmAlgorithm::PrintPopulation() const
{
	for (const auto& individual : population) 
	{
		std::cout << *individual << std::endl;
	}
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

Individual* SwarmAlgorithm::GetBestIndividualInPopulation() const
{
	Individual* bestIndividualInPopulation = population[0];
	for (auto& individual : population)
	{
		if (individual->GetScore() > bestIndividualInPopulation->GetScore())
			bestIndividualInPopulation = individual;
	}
	return bestIndividualInPopulation;
}

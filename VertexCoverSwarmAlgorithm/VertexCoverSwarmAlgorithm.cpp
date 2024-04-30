// VertexCoverSwarmAlgorithm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "SwarmAlgorithm.h"
#include <iostream>

//
/*
* Folosesc individul(numit ca "vectorul de gene") de la genetic algorithm
* x <=> vectorul de gene curent al individului i
* pi <=> vectorul de gene cel mai bun anterior pentru individul i
* pg <=> vectorul de gene cel mai bun din populatie
* f <=> functia de fitness
* vi <=> initial nula, se calculeaza 
* fi1 si fi2 <=> vector de gene generat random
* c1 si c2 <=> "acceleratie", variabile pre-stabilite
* w <=> variabila de intertie, spune cat de relevanta este vi anterioara
*/

/*
* selectia <=> daca se considera pg global sau din vecini? daca din vecini,
* vecinii sunt considerati cei cu scoruri apropiate?
* mutatia <=> regasirea lui pg, actualizare pi si vi
*/

/*
* Individul :
*               vector de gene
*               vector anterior cel mai bun de gene
*               pointer la vector cel mai bun curent (pentru a implementa ambele variante)
*               vectorul de velocitate/viteza
*               fi1 si fi2 (daca sunt diferite la fiecare individ)
*/

/*
* Populatia:
*   -vector de pointeri catre indivizi / vector de indivizi
*   -la fiecare iteratie, se reface un map<double, pointer la individ> pentru a defini/a gasi mai usor vecinii si pe cel mai bun
*   -se actualizeaza datele
*   
*/

//score => numberOfIndividualsWithScore
void WriteResultsToFile(const std::map<double, int>& percentages, const std::map<double, std::unordered_set<Individual, Individual::Hash, Individual::IsEqual>>& individuals)
{
    std::ofstream out(FILE_PATH_TO_RESULTS);
    if (!out)
        throw std::exception("Unable to open file.");

    int totalNumberOfIndividuals{ 0 };
    for (const auto& element : percentages)
    {
        totalNumberOfIndividuals += element.second;
    }

    for (const auto& element : percentages)
    {
        double percentage{ static_cast<double>(element.second) / totalNumberOfIndividuals * 100.0 };

        out << "SCORE: " << element.first << " =>" << "\tNUMBER OF INDIVIDUALS: " << element.second << "\tPERCENTAGE: " << percentage << "%" << std::endl;

        for (const auto& individual : individuals.at(element.first))
        {
            out << individual << std::endl;
        }
        out << std::endl;
    }

    out.close();
}

int main()
{
	Graph* graph = Graph::GetGraphFromFile();
    std::vector<Individual*> basePopulation{ SwarmAlgorithm::GeneratePopulation(graph) };

	//SwarmAlgorithm algorithm{ graph, basePopulation };

    std::map<double, int> results;
    std::map<double, std::unordered_set<Individual, Individual::Hash, Individual::IsEqual>> individuals;
    Individual* individual = nullptr;
    for (size_t _{ 0u }; _ < NUMBER_OF_RUNS; ++_)
    {
        SwarmAlgorithm algorithm{ graph, basePopulation };
        std::cout << std::endl;
        individual = algorithm.RunAlgorithm();
        auto score = individual->GetScore();
        results[score]++;
        individuals[score].insert(Individual{ individual, true });
        WriteResultsToFile(results, individuals);
    }
   // WriteResultsToFile(results, individuals);
	return 0;
}

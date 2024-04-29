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

int main()
{
	Graph* graph = Graph::GetGraphFromFile();
	SwarmAlgorithm algorithm{ graph };
	algorithm.RunAlgorithm();
	return 0;
}

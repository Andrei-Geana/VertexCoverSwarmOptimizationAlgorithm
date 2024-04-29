#pragma once

#include "Helper.h"

#include <vector>
struct Genes 
{
	Genes(size_t size)
	{
		chromosome.resize(size);
	}

	static Genes* GetGenes(size_t size = NODES_NUMBER)
	{
		Genes* currentGenes = new Genes{ size };
		for (size_t i{ 0u }; i < size; ++i)
		{
			if (auto possibility = Helper::ShouldChange(); possibility)
				currentGenes->chromosome[i] = !currentGenes->chromosome[i];
		}
		return currentGenes;
	}

	std::vector<bool> chromosome;
};
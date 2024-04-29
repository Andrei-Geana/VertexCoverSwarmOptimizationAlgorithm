#pragma once

#include <vector>
struct Genes 
{
	Genes(size_t size)
	{
		chromosome.resize(size);
	}

	std::vector<bool> chromosome;
};
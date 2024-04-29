#pragma once
#include <iostream>
#include <fstream>
#include <unordered_set>

#include "Arch.h"
#include "Genes.h"

class Graph
{
public:
    static Graph* GetGraphFromFile(const std::string& FilePath = FILE_PATH_TO_GRAPH);
public:
    Graph(int n);

    void AddArch(int from, int to);

    bool IsSolution(const Genes* genes) const;

    int GetNumberOfNotVerifiedArch(const Genes* genes) const;

    void PrintAllArches();

    int GetNumberOfArches() const;

private:
    std::unordered_set<int> nodes;
    std::unordered_set<Arch, Arch::Hash, Arch::IsEqual> arches;

};

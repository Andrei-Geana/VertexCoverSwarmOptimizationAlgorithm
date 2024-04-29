#include "Graph.h"

inline Graph::Graph() {/*EMPTY*/ }

inline Graph::Graph(int n)
{
    for (int i = 0; i < n; ++i)
    {
        nodes.insert(i);
    }
}

inline void Graph::AddArch(int from, int to)
{
    if (!nodes.contains(from))
        throw std::exception("start node not in graph");
    if (!nodes.contains(to))
        throw std::exception("destination node not in graph");

    arches.insert(Arch{ from, to });
}

inline bool Graph::IsSolution(const Genes* genes) const
{
    if (genes->chromosome.size() != nodes.size())
        throw std::exception("genes size not equal to number of nodes in graph");

    for (const Arch& arc : arches)
    {
        if (genes->chromosome[arc.From()])
            continue;
        if (genes->chromosome[arc.To()])
            continue;
        return false;
    }

    return true;
}

inline int Graph::GetNumberOfNotVerifiedArch(const Genes* genes) const
{
    int count{ 0 };
    for (const Arch& arc : arches)
    {
        if (genes->chromosome[arc.From()])
            continue;
        if (genes->chromosome[arc.To()])
            continue;
        count++;
    }
    return count;
}

inline void Graph::PrintAllArches()
{
    for (const Arch& elem : arches)
    {
        std::cout << elem.From() << "," << elem.To() << std::endl;
    }
}

inline int Graph::GetNumberOfArches() const
{
    return (int)arches.size();
}

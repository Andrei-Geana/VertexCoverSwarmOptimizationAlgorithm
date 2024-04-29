#include "Graph.h"

Graph* Graph::GetGraphFromFile(const std::string& FilePath)
{
    std::ifstream fin{ FilePath };
    if (!fin.is_open())
    {
        throw std::exception("unable to open file to read graph");
    }
    fin >> NODES_NUMBER;
    Graph* graph = new Graph{ NODES_NUMBER };
    int from{}, to{};
    while (fin >> from >> to)
    {
        try
        {
            graph->AddArch(from, to);
        }
        catch (std::exception ex)
        {
            std::cout << ex.what() << " for arch: (" << from << ", " << to << ")" << std::endl;
        }
    }
    fin.close();
    return graph;
}

Graph::Graph(int n)
{
    for (int i = 0; i < n; ++i)
    {
        nodes.insert(i);
    }
}

void Graph::AddArch(int from, int to)
{
    if (!nodes.contains(from))
        throw std::exception("start node not in graph");
    if (!nodes.contains(to))
        throw std::exception("destination node not in graph");

    arches.insert(Arch{ from, to });
}

bool Graph::IsSolution(const Genes* genes) const
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

int Graph::GetNumberOfNotVerifiedArch(const Genes* genes) const
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

void Graph::PrintAllArches()
{
    for (const Arch& elem : arches)
    {
        std::cout << elem.From() << "," << elem.To() << std::endl;
    }
}

int Graph::GetNumberOfArches() const
{
    return (int)arches.size();
}

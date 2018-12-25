//
// Created by liza_shch on 22.12.18.
//

#include "CListGraph.h"

bool CListGraph::isValid(int index) const {
    return (index >= 0 && index < VerticesCount());
}

void CListGraph::AddWeightEdge(int from, int to, double weight) {
    assert(isValid(from));
    assert(isValid(to));

    adjacencyListFromTo[from].push_back(EdgeInfo(to, weight));
    adjacencyListFromTo[to].push_back(EdgeInfo(from, weight));
}

std::vector<IGraph::EdgeInfo> CListGraph::GetNextWeightVertices(int vertex) const {
    assert(isValid(vertex));

    return adjacencyListFromTo[vertex];
}

std::vector<IGraph::EdgeInfo> CListGraph::GetPrevWeightVertices(int vertex) const {
    assert(isValid(vertex));

    return adjacencyListFromTo[vertex];
}

double CListGraph::GetWeight(int from, int to) const {
    for (int i = 0; i < adjacencyListFromTo.size(); i++) {
        if (adjacencyListFromTo[from][i].vertex == to) {
            return adjacencyListFromTo[from][i].weight;
        }
    }

    return -1;
}
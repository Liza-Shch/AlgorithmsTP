//
// Created by liza_shch on 14.12.18.
//

#include "CListGraph.h"

CListGraph::CListGraph(const IGraph *other): CListGraph(other->VerticesCount()) {
    for (int i = 0; i < adjacencyListFromTo.size(); i++) {
        std::vector<int> currentNextVertices = other->GetNextVertices(i);
        std::copy(currentNextVertices.begin(), currentNextVertices.end(), std::back_inserter(adjacencyListFromTo[i]));

        std::vector<int> currentPrevVertices = other->GetPrevVertices(i);
        std::copy(currentPrevVertices.begin(), currentPrevVertices.end(), std::back_inserter(adjacencyListToFrom[i]));
    }
}

bool CListGraph::isValid(int index) const {
    return (index >= 0 && index < VerticesCount());
}

void CListGraph::AddEdge(int from, int to) {
    assert(isValid(from));
    assert(isValid(to));

    adjacencyListFromTo[from].push_back(to);
    adjacencyListToFrom[to].push_back(from);
}

std::vector<int> CListGraph::GetNextVertices(int vertex) const {
    assert(isValid(vertex));
    return adjacencyListFromTo[vertex];
}

std::vector<int> CListGraph::GetPrevVertices(int vertex) const {
    assert(isValid(vertex));
    return adjacencyListToFrom[vertex];
}
//
// Created by liza_shch on 14.12.18.
//

#include "CSetGraph.h"

CSetGraph::CSetGraph(const IGraph *other): CSetGraph(other->VerticesCount()) {
    for (int i = 0; i < VerticesCount(); i++) {
        std::vector<int> nextVertices = other->GetNextVertices(i);
        for (auto vertex : nextVertices) {
            adjacencyHashTablesFromTo[i].Add(vertex);
            adjacencyHashTablesToFrom[vertex].Add(i);
        }
    }
}

bool CSetGraph::isValid(int index) const {
    return (index >= 0 && index < VerticesCount());
}

void CSetGraph::AddEdge(int from, int to) {
    assert(isValid(from));
    assert(isValid(to));

    adjacencyHashTablesFromTo[from].Add(to);
    adjacencyHashTablesToFrom[to].Add(from);
}

std::vector<int> CSetGraph::GetNextVertices(int vertex) const {
    assert(isValid(vertex));

    std::vector<int> nextVertices;
    for (int i = 0; i < VerticesCount(); i++) {
        if (adjacencyHashTablesFromTo[vertex].Has(i)) {
            nextVertices.push_back(i);
        }
    }

    return nextVertices;
}

std::vector<int> CSetGraph::GetPrevVertices(int vertex) const {
    assert(isValid(vertex));

    std::vector<int> prevVertices;
    for (int i = 0; i < VerticesCount(); i++) {
        if (adjacencyHashTablesToFrom[vertex].Has(i)) {
            prevVertices.push_back(i);
        }
    }

    return prevVertices;
}
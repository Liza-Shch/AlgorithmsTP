//
// Created by liza_shch on 14.12.18.
//

#include "CMatrixGraph.h"

CMatrixGraph::CMatrixGraph(const IGraph *other): CMatrixGraph(other->VerticesCount()) {
    for (int row = 0; row < VerticesCount(); row++) {
        std::vector<int> nextVertices = other->GetNextVertices(row);
        for (int column : nextVertices) {
            adjacencyMatrix[row][column] = true;
        }
    }
}

bool CMatrixGraph::isValid(int index) const {
    return (index >= 0 && index < VerticesCount());
}

void CMatrixGraph::AddEdge(int from, int to) {
    assert(isValid(from));
    assert(isValid(to));

    adjacencyMatrix[from][to] = true;
}

std::vector<int> CMatrixGraph::GetNextVertices(int vertex) const {
    assert(isValid(vertex));

    std::vector<int> nextVertices;
    for (int i = 0; i < VerticesCount(); i++) {
        if (adjacencyMatrix[vertex][i]) {
            nextVertices.push_back(i);
        }
    }

    return nextVertices;
}

std::vector<int> CMatrixGraph::GetPrevVertices(int vertex) const {
    assert(isValid(vertex));

    std::vector<int> prevVertices;
    for (int i = 0; i < VerticesCount(); i++) {
        if (adjacencyMatrix[i][vertex]) {
            prevVertices.push_back(i);
        }
    }

    return prevVertices;
}
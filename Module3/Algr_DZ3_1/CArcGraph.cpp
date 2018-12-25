//
// Created by liza_shch on 14.12.18.
//

#include "CArcGraph.h"

CArcGraph::CArcGraph(const IGraph *other): CArcGraph(other->VerticesCount()) {
    for (int from = 0; from < verticesCount; from++) {
        std::vector<int> nextVertices = other->GetNextVertices(from);
        for (int to = 0; to < nextVertices.size(); to++) {
            edgesArray.emplace_back(from, nextVertices[to]);
        }
    }
}

bool CArcGraph::isValid(int index) const {
    return (index >= 0 && index < verticesCount);
}

void CArcGraph::AddEdge(int from, int to) {
    assert(isValid(from));
    assert(isValid(to));

    edgesArray.emplace_back(from, to);
}

std::vector<int> CArcGraph::GetNextVertices(int vertex) const {
    assert(isValid(vertex));

    std::vector<int> nextVertices;
    for (auto edge : edgesArray) {
        if (edge.from == vertex) {
            nextVertices.push_back(edge.to);
        }
    }

    return  nextVertices;
}

std::vector<int> CArcGraph::GetPrevVertices(int vertex) const {
    assert(isValid(vertex));

    std::vector<int> prevVertices;
    for (auto edge : edgesArray) {
        if (edge.to == vertex) {
            prevVertices.push_back(edge.from);
        }
    }

    return prevVertices;
}

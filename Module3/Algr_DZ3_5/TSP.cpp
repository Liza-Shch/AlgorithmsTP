//
// Created by liza_shch on 22.12.18.
//

#include "TSP.h"

double TSP::Prime(const CListGraph& graph, CListGraph& mst) {
    int verticesCount = graph.VerticesCount();
    assert(verticesCount > 0);
    std::set<std::pair<double, int>> verticesPriority;
    std::vector<int> parent(verticesCount, -1);
    std::vector<double> minWeight(verticesCount, RAND_MAX);
    std::vector<bool> isInMST(verticesCount, false);
    verticesPriority.insert(std::pair<int, int>(0, 0));
    minWeight[0] = 0;
    while (!verticesPriority.empty()) {
        std::pair<int, int> from = *verticesPriority.begin();
        verticesPriority.erase(verticesPriority.begin());
        isInMST[from.second] = true;
        std::vector<CListGraph::EdgeInfo> nextVertices = graph.GetNextWeightVertices(from.second);
        for (auto nextVertex : nextVertices) {
            if (!isInMST[nextVertex.vertex] && (minWeight[nextVertex.vertex] > nextVertex.weight)) {
                std::pair<double, int> findNextVertex(minWeight[nextVertex.vertex], nextVertex.vertex);
                auto nextVertexInQueue = verticesPriority.find(findNextVertex);
                if (*nextVertexInQueue == findNextVertex) {
                    verticesPriority.erase(nextVertexInQueue);
                }
                verticesPriority.insert(std::pair<int, int>(nextVertex.weight, nextVertex.vertex));
                minWeight[nextVertex.vertex] = nextVertex.weight;
                parent[nextVertex.vertex] = from.second;
            }
        }
    }

    double mstWeight = 0;
    for (int i = 1; i < verticesCount; i++) {
        mst.AddWeightEdge(parent[i], i, minWeight[i]);
        mstWeight += minWeight[i];
    }

    return mstWeight;
}

double TSP::TSP(const CListGraph& graph) {
    CListGraph mst(graph.VerticesCount());
    return TSP::Prime(graph, mst);
}

double TSP::BruteForce(const CListGraph& graph) {
    int verticesCount = graph.VerticesCount();
    std::vector<int> vertices;
    for (int i = 0; i < verticesCount; i++) {
        vertices.push_back(i);
    }

    std::vector<double> weights;
    do {
        double weight = 0;
        double edgeWeight = 0;
        for (int i = 0; i < verticesCount; i++) {
            edgeWeight = graph.GetWeight(i, i + 1);
            if (edgeWeight != -1) {
                weight += edgeWeight;
            }
        }

        weights.push_back(weight);
    } while (std::next_permutation(vertices.begin(), vertices.end()));

    return *std::min_element(weights.begin(), weights.end());
}
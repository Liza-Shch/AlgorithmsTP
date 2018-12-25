//
// Created by liza_shch on 14.12.18.
//

#ifndef ALGR_DZ3_1_CLISTGRAPH_H
#define ALGR_DZ3_1_CLISTGRAPH_H

#include "IGraph.h"

#include <cassert>

class CListGraph: public IGraph {
public:
    CListGraph(int verticesCount): adjacencyListFromTo(verticesCount), adjacencyListToFrom(verticesCount) {}
    CListGraph(const IGraph* other);
    CListGraph(const CListGraph& other) = delete;
    CListGraph(CListGraph&& other) = delete;
    ~CListGraph() {}
    CListGraph&operator=(const CListGraph& other) = delete;
    CListGraph&operator=(CListGraph&& other) = delete;

    void AddEdge(int from, int to) override;
    int VerticesCount() const override { return adjacencyListFromTo.size(); }
    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::vector<int>> adjacencyListFromTo;
    std::vector<std::vector<int>> adjacencyListToFrom;
    bool isValid(int index) const;
};


#endif //ALGR_DZ3_1_CLISTGRAPH_H

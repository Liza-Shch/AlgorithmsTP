//
// Created by liza_shch on 22.12.18.
//

#ifndef ALGR_DZ3_5_CLISTGRAPH_H
#define ALGR_DZ3_5_CLISTGRAPH_H

#include <cassert>
#include "IGraph.h"

class CListGraph: public IGraph {
public:
    CListGraph(int verticesCount): adjacencyListFromTo(verticesCount) {}
    CListGraph(const CListGraph& other) = delete;
    CListGraph(CListGraph&& other) = delete;
    ~CListGraph() {}
    CListGraph&operator=(const CListGraph& other) = delete;
    CListGraph&operator=(CListGraph&& other) = delete;

    void AddWeightEdge(int from, int to, double weight) override;
    int VerticesCount() const override { return adjacencyListFromTo.size(); }
    std::vector<EdgeInfo> GetNextWeightVertices(int vertex) const override;
    std::vector<EdgeInfo> GetPrevWeightVertices(int vertex) const override;
    double GetWeight(int from, int to) const;

private:
    std::vector<std::vector<EdgeInfo>> adjacencyListFromTo;
    bool isValid(int index) const;
};


#endif //ALGR_DZ3_5_CLISTGRAPH_H

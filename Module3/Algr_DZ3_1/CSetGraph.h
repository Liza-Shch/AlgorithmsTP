//
// Created by liza_shch on 14.12.18.
//

#ifndef ALGR_DZ3_1_CSETGRAPH_H
#define ALGR_DZ3_1_CSETGRAPH_H

#include "IGraph.h"
#include "HashTable.h"
#include <cassert>

class CSetGraph: public IGraph {
public:
    CSetGraph(int verticesCount) : adjacencyHashTablesFromTo(verticesCount), adjacencyHashTablesToFrom(verticesCount) {}
    CSetGraph(const IGraph* other);
    CSetGraph(const CSetGraph& other) = delete;
    CSetGraph(CSetGraph&& other) = delete;
    ~CSetGraph() {}
    CSetGraph&operator=(const CSetGraph& other) = delete;
    CSetGraph&operator=(CSetGraph&& other) = delete;

    void AddEdge(int from, int to) override;
    int VerticesCount() const override { return adjacencyHashTablesFromTo.size(); }
    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;
private:
    std::vector<HashTable<int>> adjacencyHashTablesFromTo;
    std::vector<HashTable<int>> adjacencyHashTablesToFrom;
    bool isValid(int index) const;
};


#endif //ALGR_DZ3_1_CSETGRAPH_H

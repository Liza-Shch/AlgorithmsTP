//
// Created by liza_shch on 14.12.18.
//

#ifndef ALGR_DZ3_1_CMATRIXGRAPH_H
#define ALGR_DZ3_1_CMATRIXGRAPH_H

#include "IGraph.h"
#include <cassert>

class CMatrixGraph: public IGraph {
public:
    CMatrixGraph(int verticesCount): adjacencyMatrix(verticesCount) {
        for (int row = 0; row < VerticesCount(); row++) {
            for (int column = 0; column < VerticesCount(); column++) {
                adjacencyMatrix[row].push_back(false);
            }
        }
    }
    CMatrixGraph(const IGraph* other);
    CMatrixGraph(const CMatrixGraph& other) = delete;
    CMatrixGraph(CMatrixGraph&& other) = delete;
    ~CMatrixGraph() {}
    CMatrixGraph&operator=(const CMatrixGraph& other) = delete;
    CMatrixGraph&operator=(CMatrixGraph&& other) = delete;

    void AddEdge(int from, int to) override;
    int VerticesCount() const override { return adjacencyMatrix.size(); }
    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::vector<bool>> adjacencyMatrix;
    bool isValid(int index) const;
};


#endif //ALGR_DZ3_1_CMATRIXGRAPH_H

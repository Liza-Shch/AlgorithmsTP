//
// Created by liza_shch on 14.12.18.
//

#ifndef ALGR_DZ3_1_IGRAPH_H
#define ALGR_DZ3_1_IGRAPH_H

#include <vector>

struct IGraph {
    virtual ~IGraph() {}

    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

#endif //ALGR_DZ3_1_IGRAPH_H

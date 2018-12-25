//
// Created by liza_shch on 14.12.18.
//

#ifndef ALGR_DZ3_1_CARCGRAPH_H
#define ALGR_DZ3_1_CARCGRAPH_H

#include "IGraph.h"
#include <cassert>

class CArcGraph: public IGraph {
public:
    CArcGraph(int verticesCount): verticesCount(verticesCount) {}
    CArcGraph(const IGraph* other);
    CArcGraph(const CArcGraph& other) = delete;
    CArcGraph(CArcGraph&& other) = delete;
    ~CArcGraph() {}
    CArcGraph&operator=(const CArcGraph& other) = delete;
    CArcGraph&operator=(CArcGraph&& other) = delete;

    void AddEdge(int from, int to) override;
    int VerticesCount() const { return verticesCount; }
    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    struct Pair {
        Pair(): from(0), to(0) {}
        Pair(int from, int to) : from(from), to(to) {}
        Pair(const Pair& other): Pair(other.from, other.to) {}
        Pair(Pair&& other) = delete;
        ~Pair() = default;
        Pair&operator=(const Pair& other) = delete;
        Pair&operator=(Pair&& other) = delete;

        int from;
        int to;
    };
    std::vector<Pair> edgesArray;
    int verticesCount;
    bool isValid(int index) const;
};


#endif //ALGR_DZ3_1_CARCGRAPH_H

//
// Created by liza_shch on 22.12.18.
//

#ifndef ALGR_DZ3_5_IGRAPH_H
#define ALGR_DZ3_5_IGRAPH_H

#include <vector>

struct IGraph {
    virtual ~IGraph() {}

    virtual void AddWeightEdge(int from, int to, double weight) = 0;

    virtual int VerticesCount() const = 0;

    struct EdgeInfo {
        EdgeInfo(int to, double weight) : vertex(to), weight(weight) {}
        EdgeInfo (const EdgeInfo& other) : vertex(other.vertex), weight(other.weight) {}
        EdgeInfo (EdgeInfo&& other) { *this = std::move(other); }
        ~EdgeInfo() {}
        EdgeInfo& operator=(const EdgeInfo& other) {
            if (this != &other) {
                vertex = other.vertex;
                weight = other.weight;
            }
            return *this;
        }

        EdgeInfo& operator=(EdgeInfo&& other) {
            if (this != &other ) {
                vertex = other.vertex;
                weight = other.weight;
                other.vertex = 0;
                other.weight = 0;
            }
            return *this;
        }
        bool operator<(const EdgeInfo& edgeInfo) const { return this->weight <= edgeInfo.weight; }
        bool operator==(const EdgeInfo& edgeInfo) const { return (this->weight == edgeInfo.weight) &&
                                                                 (this->vertex == edgeInfo.vertex);
        }

        bool operator!=(const EdgeInfo& edgeInfo) const { return (this->weight != edgeInfo.weight) &&
                                                                 (this->vertex != edgeInfo.vertex);
        }

        bool operator<=(const EdgeInfo& edgeInfo) const { return (this->weight <= edgeInfo.weight); }

        int vertex;
        double weight;
    };

    virtual std::vector<EdgeInfo> GetNextWeightVertices(int vertex) const = 0;
    virtual std::vector<EdgeInfo> GetPrevWeightVertices(int vertex) const = 0;
};

#endif //ALGR_DZ3_5_IGRAPH_H

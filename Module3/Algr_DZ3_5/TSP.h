//
// Created by liza_shch on 22.12.18.
//

#ifndef ALGR_DZ3_5_TSP_H
#define ALGR_DZ3_5_TSP_H

#include <algorithm>
#include <set>
#include "CListGraph.h"

namespace TSP {
    double Prime(const CListGraph& graph, CListGraph& mst);
    double TSP(const CListGraph& graph);
    double BruteForce(const CListGraph& graph);
};


#endif //ALGR_DZ3_5_TSP_H

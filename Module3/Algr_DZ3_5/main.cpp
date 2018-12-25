#include <iostream>
#include <vector>
#include <cassert>
#include <set>
#include <algorithm>

#include "BoxMuller.h"
#include "CListGraph.h"
#include "Experiment.h"
#include "TSP.h"

std::pair<double, double> experiment(int count) {
    int experimentCount = 10;
    std::vector<double> experimentResults;
    for (int i = 0; i < experimentCount; i++) {
        Points points(count);
        CListGraph graph(count);
        for (int from = 0; from < count; from++) {
            for (int to = from + 1; to < count; to++) {
                graph.AddWeightEdge(from, to, points.GetWeight(from, to));
            }
        }

        double TSP_MST = TSP::TSP(graph);
        double TSP_BF = TSP::BruteForce(graph);
        experimentResults.push_back(Experiment::approximation(TSP_BF, TSP_MST));
    }

    std::pair<double, double> result;
    Experiment::standartDeviation(experimentResults, result);
    return result;
}

int main() {
    for (int count = 2; count < 11; count++) {
        std::pair<double, double> result = experiment(count);
        std::cout << count << ": average value = " << result.first
                  << " standart deviation = " << result.second << std::endl;
    }
    return 0;
}
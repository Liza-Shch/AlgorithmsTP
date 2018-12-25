//
// Created by liza_shch on 22.12.18.
//

#ifndef ALGR_DZ3_5_EXPERIMENT_H
#define ALGR_DZ3_5_EXPERIMENT_H

#include <algorithm>

namespace Experiment {
    double approximation(double realCost, double algrCost);
    double averageValue(const std::vector<double>& values);
    void standartDeviation(const std::vector<double>& values, std::pair<double, double>& result);
};


#endif //ALGR_DZ3_5_EXPERIMENT_H

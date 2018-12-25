//
// Created by liza_shch on 22.12.18.
//

#include "Experiment.h"

double Experiment::approximation(double realCost, double algrCost) {
    return std::max(realCost / algrCost, algrCost / realCost);
}

double Experiment::averageValue(const std::vector<double>& values) {
    double valueSum = 0;
    for (auto value : values) {
        valueSum += value;
    }
    return valueSum / values.size();
}

void Experiment::standartDeviation(const std::vector<double>& values, std::pair<double, double>& result) {
    double average = averageValue(values);
    double dispersion = 0;
    for (double value : values) {
        dispersion += std::pow(value - average, 2);
    }
    dispersion /= values.size();
    double standartDeviation_ =  std::sqrt(dispersion);
    result = std::make_pair(average, standartDeviation_);
}
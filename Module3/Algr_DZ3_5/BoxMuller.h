//
// Created by liza_shch on 21.12.18.
//

#ifndef ALGR_DZ3_5_BOXMULLER_H
#define ALGR_DZ3_5_BOXMULLER_H

#include <cmath>
#include <cstdlib>
#include <vector>
#include <ctime>

struct Points {
public:
    Points(int count);
    double GetWeight(int from, int to) { return from == to ? 0 : getDistance(points[from], points[to]); }
private:
    std::vector<std::pair<double, double>> points;
    double getDistance(std::pair<double, double> point1, std::pair<double, double> point2);
};

Points::Points(int count) {
    std::srand(std::time(nullptr));
    for (int i = 0; i < count; i++) {
        double x = 0;
        double y = 0;
        double s = 0;
        do {
            x = (double) std::rand() / RAND_MAX;
            y = (double) std::rand() / RAND_MAX;
            s = x * x + y * y;
        } while (s > 1 || s == 0);

        double _x = x * std::sqrt(-2 * std::log(s) / s);
        double _y = y * std::sqrt(-2 * std::log(y) / s);
        points.emplace_back(std::make_pair(_x, _y));
    }
}

double Points::getDistance(std::pair<double, double> point1, std::pair<double, double> point2) {
    return std::sqrt(std::pow(point1.first - point2.second, 2) + std::pow(point1.second - point2.second, 2));
}

#endif //ALGR_DZ3_5_BOXMULLER_H

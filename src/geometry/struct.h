#pragma once

#include <string>
#include <vector>

struct figure {
    int id;
    std::string name;
    std::vector<double> points;
    double perimetr;
    double square;
    std::vector<figure*> intersections;
};

#pragma once

#include <geometry/struct.h>
#include <string>
#include <vector>

double takePerimetr(std::string figureName, std::vector<double> points);
double takeSquare(std::string figureName, std::vector<double> points);
void calculateInterscapes(std::vector<figure>& figures);

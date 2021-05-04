#pragma once

#include <geometry/struct.h>
#include <string>
#include <vector>

double takePerimetr(std::string figureName, std::vector<double> points);
double takeSquare(std::string figureName, std::vector<double> points);
void calculateInterscapes(std::vector<figure>& figures);
bool isIntersectionSections(
        double start1x,
        double start1y,
        double end1x,
        double end1y,
        double start2x,
        double start2y,
        double end2x,
        double end2y);
bool isIntersectionTwoCircles(std::vector<double> circle1, std::vector<double> circle2);
bool isIntersectionCirclePoligon(
        std::vector<double> poligon, std::vector<double> circle);
bool isIntersectionTwoPoligones(
        std::vector<double> poligon1, std::vector<double> poligon2);
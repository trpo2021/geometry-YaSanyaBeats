#include <cmath>
#include <geometry/struct.h>
#include <string>
#include <vector>

using namespace std;

const double PI = 3.141592653589793;

double takePerimetr(string figureName, vector<double> points)
{
    double perim = 0;
    if (figureName == "circle") {
        perim = 2 * PI * points[2];
    } else {
        for (int i = 0; i < (int)points.size() - 2; i += 2) {
            perim
                    += sqrt(pow(points[i + 2] - points[i], 2)
                            + pow(points[i + 1] - points[i + 3], 2));
        }
    }
    return perim;
}

double takeSquare(string figureName, vector<double> points)
{
    double square = 0;
    if (figureName == "circle") {
        square = PI * pow(points[2], 2);
    } else {
        for (int i = 0; i < (int)points.size() - 2; i += 2) {
            square += points[i] * points[i + 3];
        }
        for (int i = 0; i < (int)points.size() - 2; i += 2) {
            square -= points[i + 1] * points[i + 2];
        }
        square = abs(square) / 2;
    }
    return square;
}

bool isIntersectionSections(
        double start1x,
        double start1y,
        double end1x,
        double end1y,
        double start2x,
        double start2y,
        double end2x,
        double end2y)
{
    double dir1x = end1x - start1x;
    double dir1y = end1y - start1y;
    double dir2x = end2x - start2x;
    double dir2y = end2y - start2y;

    //считаем уравнения прямых проходящих через отрезки
    float a1 = -dir1y;
    float b1 = +dir1x;
    float d1 = -(a1 * start1x + b1 * start1y);

    float a2 = -dir2y;
    float b2 = +dir2x;
    float d2 = -(a2 * start2x + b2 * start2y);

    //подставляем концы отрезков, для выяснения в каких полуплоскотях они
    float seg1_line2_start = a2 * start1x + b2 * start1y + d2;
    float seg1_line2_end = a2 * end1x + b2 * end1y + d2;

    float seg2_line1_start = a1 * start2x + b1 * start2y + d1;
    float seg2_line1_end = a1 * end2x + b1 * end2y + d1;

    //если концы одного отрезка имеют один знак, значит он в одной полуплоскости
    //и пересечения нет.
    if (seg1_line2_start * seg1_line2_end >= 0
        || seg2_line1_start * seg2_line1_end >= 0)
        return false;

    return true;
}

bool isIntersectionTwoCircles(vector<double> circle1, vector<double> circle2)
{
    double radius1 = circle1[2];
    double radius2 = circle2[2];

    double distanse
            = sqrt(pow((circle1[0] - circle2[0]), 2)
                   + pow((circle1[1] - circle2[1]), 2));

    if ((radius1 + radius2) < distanse) {
        return false;
    }
    if (abs(radius1 - radius2)
        > distanse) { // Если центр одной окружности лежит в другой
        return false;
    }
    return true;
}

bool isIntersectionCirclePoligon(vector<double> poligon, vector<double> circle)
{
    bool isPointInside;
    double distance
            = sqrt(pow((poligon[0] - circle[0]), 2)
                   + pow((poligon[1] - circle[1]), 2));
    if (distance < circle[2]) {
        isPointInside = true;
    } else {
        isPointInside = false;
    }
    for (int i = 2; i < (int)poligon.size(); i += 2) {
        distance
                = sqrt(pow((poligon[i] - circle[0]), 2)
                       + pow((poligon[i + 1] - circle[1]), 2));
        if ((distance < circle[2]) != isPointInside) {
            return true;
        }
    }
    return false;
}

bool isIntersectionTwoPoligones(
        vector<double> poligon1, vector<double> poligon2)
{
    for (int i = 0; i < (int)poligon1.size() - 3; i += 2) {
        for (int j = 0; j < (int)poligon2.size() - 3; j += 2) {
            if (isIntersectionSections(
                        poligon1[i],
                        poligon1[i + 1],
                        poligon1[i + 2],
                        poligon1[i + 3],
                        poligon2[j],
                        poligon2[j + 1],
                        poligon2[j + 2],
                        poligon2[j + 3])) {
                return true;
            }
        }
    }
    return false;
}

void calculateInterscapes(vector<figure>& figures)
{
    for (int i = 0; i < (int)figures.size(); i++) {
        for (int j = i + 1; j < (int)figures.size(); j++) {
            if (figures[i].name == "circle") {
                if (figures[j].name == "circle") {
                    if (isIntersectionTwoCircles(
                                figures[j].points, figures[i].points)) {
                        figures[j].intersections.push_back(&figures[i]);
                        figures[i].intersections.push_back(&figures[j]);
                    }
                } else {
                    if (isIntersectionCirclePoligon(
                                figures[j].points, figures[i].points)) {
                        figures[j].intersections.push_back(&figures[i]);
                        figures[i].intersections.push_back(&figures[j]);
                    }
                }
            } else {
                if (figures[j].name == "circle") {
                    if (isIntersectionCirclePoligon(
                                figures[i].points, figures[j].points)) {
                        figures[j].intersections.push_back(&figures[i]);
                        figures[i].intersections.push_back(&figures[j]);
                    }
                } else {
                    if (isIntersectionTwoPoligones(
                                figures[j].points, figures[i].points)) {
                        figures[j].intersections.push_back(&figures[i]);
                        figures[i].intersections.push_back(&figures[j]);
                    }
                }
            }
        }
    }
}

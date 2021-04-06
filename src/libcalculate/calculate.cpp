#include <cmath>
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

#include <iostream>
#include <string>
#include <vector>

#include <geometry/struct.h>
#include <libcalculate/calculate.h>
#include <libinput/input.h>

using namespace std;

void addNewFigure(vector<figure>& figures, string s)
{
    figure tmp;

    tmp.id = figures.size() + 1;
    tmp.name = takeFigureName(s);

    string points = takePointsString(tmp.name, s);
    tmp.points = takePoints(points);

    tmp.perimetr = takePerimetr(tmp.name, tmp.points);
    tmp.square = takeSquare(tmp.name, tmp.points);

    figures.push_back(tmp);
}

void printFigures(vector<figure> figures)
{
    for (int i = 0; i < (int)figures.size(); i++) {
        cout << figures[i].id << ". " << figures[i].name << ": ";
        for (int j = 0; j < (int)figures[i].points.size(); j++) {
            cout << figures[i].points[j] << " ";
        }
        cout << endl;
        cout << "perimetr = " << figures[i].perimetr << endl;
        cout << "square = " << figures[i].square << endl;
        for (int j = 0; j < (int)figures[i].intersections.size(); j++) {
            cout << "\t" << figures[i].intersections[j]->id << ". "
                 << figures[i].intersections[j]->name << endl;
        }
        cout << endl;
    }
}

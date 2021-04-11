#include <cmath>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <geometry/struct.h>
#include <geometry/structFunctions.h>
#include <libcalculate/calculate.h>
#include <libinput/input.h>

using namespace std;

int main()
{
    setlocale(LC_CTYPE, "Russian");
    vector<figure> figures;
    string s;

    cout << "Enter tokens" << endl;

    while (getline(cin, s)) {
        if (s == "") {
            break;
        }

        if (checkInput(s)) {
            addNewFigure(figures, s);
        }
    }

    printFigures(figures);

    system("PAUSE");

    return 1;
}

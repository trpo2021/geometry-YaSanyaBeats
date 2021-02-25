#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

void error(int code, int column)
{
    for (int i = 0; i < column; i++) {
        cout << " ";
    }
    cout << "^" << endl;

    switch (code) {
    case 1:
        cout << "Error at column " << column
             << ": expected 'triangle', 'circle' or 'poligon'; code = " << code << endl;
        break;
    case 2:
        cout << "Error at column " << column
             << ": expected '<double>'; code = " << code << endl;
        break;
    case 3:
        cout << "Error at column " << column
             << ": expected ')'; code = " << code << endl;
        break;
    case 4:
        cout << "Error at column " << column
             << ": expected '('; code = " << code << endl;
        break;
    case 5:
        cout << "Error at column " << column
             << ": expected ' '; code = " << code << endl;
        break;
    case 6:
        cout << "Error at column " << column
             << ": expected ','; code = " << code << endl;
        break;
    case 7:
        cout << "Error at column " << column
             << ": unexpected token; code = " << code << endl;
        break;
    }
}

string takeFigureName(string& s)
{
    int begin = s.find("(");

    for (int i = 0; i < (int)s.length(); i++) {
        s[i] = tolower(s[i]); //приводим к одному регистру(строчный)
    }

    string figure = "";
    figure.append(s, 0, begin);
    return figure;
}

bool isCorrectSymbol(char s)
{
    if (((s >= 48) && (s <= 57)) || ((s >= 44) && (s <= 46)) || (s == 32) || (s == 41)){
        return true;
    }
    return false;
}

vector<double> takeFigurePoints(string& str, string& figureName, int countPoints){
    vector<double> points;
    string s = "", tmp = "";
    int column = 0, isNumber = -1, index, countBrackets;
    bool nowPairPoint = true;

    if ((figureName == "triangle") || (figureName == "poligon")) {
        index = str.find("((");
        if (index + 1) {
            s.append(str, index + 2, str.length() - index + 1);
        } 
        else {
            if (str.find("(") + 1) {
                error(4, figureName.length() + 1);
            } 
            else {
                error(4, figureName.length());
            }
            points.clear();
            return points;
        }
    } 
    else if (figureName == "circle") {
        index = str.find("(");
        if (index + 1) {
            s.append(str, index + 1, str.length() - index + 1);
        } 
        else {
            error(4, figureName.length());
            points.clear();
            return points;
        }
    } 
    else {
        error(1, 0);
        points.clear();
        return points;
    }

    for (int i = 0; i < (int)s.length(); i++) {

        if (figureName == "circle") {
            countBrackets = 1;
            column = i + figureName.length() + countBrackets;
        } 
        else {
            countBrackets = 2;
            column = i + figureName.length() + countBrackets;
        }
        

        if (isCorrectSymbol(s[i])) {
            if (countPoints > 0) {
                if (((s[i] >= 48) && (s[i] <= 57)) || (s[i] == 46)
                    || (s[i] == 45)) {
                    if (isNumber == -1) {
                        isNumber = i;
                    }
                }
                if ((s[i] == 32) && (nowPairPoint)) {
                    if (isNumber != -1) {
                        tmp.append(s, isNumber, i - isNumber);
                        points.push_back(stod(tmp));
                        isNumber = -1;
                        nowPairPoint = false;
                        tmp = "";
                        countPoints--;
                    }
                } else if ((s[i] == 44) && (!nowPairPoint)) {
                    if (isNumber != -1) {
                        tmp.append(s, isNumber, i - isNumber);
                        points.push_back(stod(tmp));
                        isNumber = -1;
                        nowPairPoint = true;
                        tmp = "";
                        countPoints--;
                    }
                } else if ((s[i] == 41) && (countPoints == 1)) {
                    if (isNumber != -1) {
                        tmp.append(s, isNumber, i - isNumber);
                        points.push_back(stod(tmp));
                        isNumber = -1;
                        nowPairPoint = true;
                        tmp = "";
                        countPoints--;
                        i += countBrackets - 1;
                    }
                } 
                else if ((s[i] == 32) && (!nowPairPoint)) {
                    error(6, column);
                    points.clear();
                    return points;
                } 
                else if ((s[i] == 44) && (nowPairPoint)) {
                    error(5, column);
                    points.clear();
                    return points;
                } 
                else if ((s[i] == 41) && (countPoints != 0) && !nowPairPoint) {
                    error(6, column);
                    points.clear();
                    return points;
                } 
                else if ((s[i] == 41) && (countPoints != 0) && nowPairPoint) {
                    error(5, column);
                    points.clear();
                    return points;
                }
            }
            else {
                error(7, column);
                points.clear();
                return points;
            }
        } 
        else {
            error(2, column);
            points.clear();
            return points;
        }
    }

    if (countPoints) {
        error(2, str.length());
        points.clear();
        return points;
    }
    return points;
}

int main()
{
    setlocale(LC_CTYPE, "Russian");
    vector<pair<string, vector<double>>> figures;
    pair<string, vector<double>> figure;
    vector<double> figurePoints;
    string s, figureName;

    cout << "Enter tokens" << endl;

    while (getline(cin, s)) {
        if (s == "") {
            break;
        }

        figureName = takeFigureName(s);
        if (figureName == "triangle") {
            figurePoints = takeFigurePoints(s, figureName, 8);
        } 
        else if (figureName == "circle") {
            figurePoints = takeFigurePoints(s, figureName, 3);
        } 
        else {
            error(1, 0);
            continue;
        }

        if (figurePoints.size() > 0) {
            figure.first = figureName;
            figure.second = figurePoints;
            figures.push_back(figure);
        }
    }

    for (int i = 0; i < (int)figures.size(); i++) {
        cout << i + 1 << ". " << figures[i].first << ": ";
        for (int j = 0; j < (int)figures[i].second.size(); j++) {
            cout << figures[i].second[j] << " ";
        }
        cout << endl;
    }

    system("PAUSE");
}

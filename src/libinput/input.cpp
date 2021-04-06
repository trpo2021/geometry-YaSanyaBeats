#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

#define EXPECTEDFIGURENAME 1
#define EXPECTEDFIRSTBRACKET 2
#define EXPECTEDSECONDBRACKET 3
#define UNEXPECTEDTOKEN 4
#define EXPECTEDCOMMA 5
#define EXPECTEDSPACE 6

vector<string> split(string s, string sep) {
    vector<string> res;
    string tmp;
    int pos = 0;
    while (pos + 1) {
        pos = s.find(sep);
        if (pos + 1) {
            tmp.append(s, 0, pos);
        }
        else {
            tmp = s;
        }
        res.push_back(tmp);
        s.erase(0, pos + sep.length());
        tmp = "";
    }
    return res;
}

void error(int code, int column) {
    for (int i = 0; i < column; i++) {
        cout << " ";
    }
    cout << "^" << endl;
    cout << "Error at column " << column << ": ";
    switch (code)
    {
    case EXPECTEDFIGURENAME:
        cout << "expected 'triangle' or 'circle' or 'poligon'";
        break;
    case EXPECTEDFIRSTBRACKET:
        cout << "expected '('";
        break;
    case EXPECTEDSECONDBRACKET:
        cout << "expected ')'";
        break;
    case UNEXPECTEDTOKEN:
        cout << "unexpected token";
        break;
    case EXPECTEDCOMMA:
        cout << "expected ','";
        break;
    case EXPECTEDSPACE:
        cout << "expected ' '";
        break;
    }
    cout << endl << endl;
}

bool isFigureName(string s) {
    if (!(s == "triangle" || s == "circle" || s == "poligon")) {
        error(EXPECTEDFIGURENAME, 0);
        return false;
    }
    return true;
}

string takeFigureName(string s) {
    string figureName;
    int pos = s.find('(');
    if (pos + 1) {
        figureName.append(s, 0, pos);
        if (isFigureName(figureName)) {
            return figureName;
        }
        else {
            return "";
        }
    }
    else {
        error(EXPECTEDFIRSTBRACKET, s.length());
        return "";
    }
}

bool checkBrackets(string figureName, string s) {
    string bracketFirst = "((", bracketSecond = "))";
    if (figureName == "circle") {
        bracketFirst = "(";
        bracketSecond = ")";
    }

    if (s.find(bracketFirst) + 1) {
        if (s.find(bracketSecond) + 1) {
            return 1;
        }
        else {
            error(EXPECTEDSECONDBRACKET, s.length());
            return 0;
        }
    }
    else {
        error(EXPECTEDFIRSTBRACKET, figureName.length());
        return 0;
    }
}

bool checkExcess(string s) {
    int pos = s.find(")") + 1;
    int len = s.length();
    while (pos < len) {
        if (s[pos] != ' ' && s[pos] != ')') {
            error(UNEXPECTEDTOKEN, pos);
            return 0;
        }
        pos++;
    }
    return 1;
}

bool checkAlternation(string figureName, string s) {
    int len = s.length();
    bool nowNumber = false;
    bool nowPair = false;
    int brackets;
    if (figureName == "circle") {
        brackets = 1;
    }
    else {
        brackets = 2;
    }

    for (int i = 0; i < len; i++) {
        if (s[i] != ',' && s[i] != ' ' && !nowNumber) {
            nowNumber = true;
        }
        if (s[i] == ' ' && nowNumber) {
            if (!nowPair) {
                nowNumber = false;
                nowPair = true;
            }
            else {
                error(EXPECTEDCOMMA, figureName.length() + brackets + i);
                return 0;
            }
        }
        if (s[i] == ',' && nowNumber) {
            if (nowPair) {
                nowNumber = false;
                nowPair = false;
            }
            else {
                error(EXPECTEDSPACE, figureName.length() + brackets + i);
                return 0;
            }
        }
    }
    return 1;
}

bool checkValid(string figureName, string points) {
    bool valid;
    set<char> validChars{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '(', ')', ' ', ',', '.', '-' };
    int len = points.length();
    for (int i = 0; i < len; i++) {
        valid = false;
        for (const auto& item : validChars) {
            if (points[i] == item) {
                valid = true;
                break;
            }
        }
        if (!valid) {
            if (figureName == "circle") {
                error(UNEXPECTEDTOKEN, figureName.length() + i + 1);
            }
            else {
                error(UNEXPECTEDTOKEN, figureName.length() + i + 2);
            }
            return 0;
        }
    }
    return 1;
}

string takePointsString(string figureName, string s) {
    string points;
    if (figureName == "circle") {
        points.append(s, figureName.length() + 1, s.find(")") - figureName.length() - 1);
    }
    else {
        points.append(s, figureName.length() + 2, s.find("))") - figureName.length() - 2);
    }

    return points;
}

vector<double> takePoints(string s) {
    vector<double> points;

    int len = s.length();
    int pos = -1;
    string tmp;

    for (int i = 0; i < len; i++) {
        if (s[i] != ' ' && s[i] != ',' && pos == -1) {
            pos = i;
        }
        if ((s[i] == ' ' || s[i] == ',') && pos != -1) {
            tmp.append(s, pos, i - pos);
            points.push_back(stod(tmp));
            tmp = "";
            pos = -1;
        }
    }

    tmp.append(s, pos, len);
    points.push_back(stod(tmp));

    return points;
}

bool checkPoints(string figureName, string s) {

    string points = takePointsString(figureName, s);

    if (checkValid(figureName, points) && checkAlternation(figureName, points)) {
        return 1;
    }
    return 0;
}

bool checkInput(string s) {
    int len = s.length();
    for (int i = 0; i < len; i++) {
        s[i] = tolower(s[i]);
    }

    string figureName = takeFigureName(s);

    if (figureName != "") {
        if (checkBrackets(figureName, s)) {
            if (checkExcess(s)) {
                if (checkPoints(figureName, s)) {
                    return 1;
                }
            }
        }
    }
    return 0;
}


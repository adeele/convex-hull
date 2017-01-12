#include <iostream>
#include <fstream>
#include <vector>
#include "Point.h"

using namespace std;

int main() {
    ifstream input;
    ofstream output;

    input.open("../in.txt");
    output.open("../out.txt");

    double num, a, b, c;
    vector<Point*> list;
    Point *p;

    input >> num;

    while (!input.eof()) {
        input >> a;
        input >> b;
        input >> c;
        p = new Point(a, b, c);
        list.push_back(p);
    }

    for(int i = 0; i < list.size(); i++) {
        list[i]->print();
        delete(list[i]);
    }

    output.close();
    input.close();

    return 0;
}
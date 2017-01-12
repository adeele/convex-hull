//
// Created by adele on 1/12/17.
//

#include <fstream>
#include <vector>
#include "Generator.h"

using namespace std;

Generator::Generator() {}

// Randomizes double number from -99.99 to 99.99
double randDoubleNumber() {
    return rand() % 20000 / 100.0 - 100.0;
}

vector<Point> Generator::generateDataInCube(int amount) {
    ofstream output;
    output.open("../static/cube.js");
    double a, b, c;
    vector<Point> points;

    output << "var cube = [";

    while (amount--) {
        a = randDoubleNumber();
        b = randDoubleNumber();
        c = randDoubleNumber();
        output << endl << "[" << a << ", " << b << ", " << c << "],";

        Point p(a, b, c);
        points.push_back(p);
    }

    output << endl << "]";
    output.close();

    return points;
}

void Generator::generateDataInBall(int amount) {
    ofstream output;
    output.open("../static/ball.js");
    double a, b, c;

    output << "var ball = [";

    while (amount) {
        a = randDoubleNumber();
        b = randDoubleNumber();
        c = randDoubleNumber();

        Point p(a, b, c);

        if (p.isInBall(radius_outer)) {
            output << endl << "[" << a << ", " << b << ", " << c << "],";
            amount--;
        }
    }

    output << endl << "]";
    output.close();
}

void Generator::generateDataInSphere(int amount) {
    ofstream output;
    output.open("../static/sphere.js");
    double a, b, c;

    output << "var sphere = [";

    while (amount) {
        a = randDoubleNumber();
        b = randDoubleNumber();
        c = randDoubleNumber();

        Point p(a, b, c);

        if (p.isInSphere(radius_outer, radius_inner)) {
            output << endl << "[" << a << ", " << b << ", " << c << "],";
            amount--;
        }
    };

    output << endl << "]";
    output.close();
}

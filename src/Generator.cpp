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

vector<Vector> Generator::generateDataInCube(int amount) {
    double a, b, c;
    vector<Vector> points;
    ofstream output;

    output.open("../static/cube.js");
    output << "var cube = [";

    while (amount--) {
        a = randDoubleNumber();
        b = randDoubleNumber();
        c = randDoubleNumber();
        output << endl << "[" << a << ", " << b << ", " << c << "],";

        Vector p(a, b, c);
        points.push_back(p);
    }

    output << endl << "]";
    output.close();

    return points;
}

vector<Vector> Generator::generateDataInBall(int amount) {
    double a, b, c;
    vector<Vector> points;
    ofstream output;

    output.open("../static/ball.js");
    output << "var ball = [";

    while (amount) {
        a = randDoubleNumber();
        b = randDoubleNumber();
        c = randDoubleNumber();

        Vector p(a, b, c);

        if (p.isInBall(radius_outer)) {
            output << endl << "[" << a << ", " << b << ", " << c << "],";
            amount--;

            points.push_back(p);
        }
    }

    output << endl << "]";
    output.close();

    return points;
}

vector<Vector> Generator::generateDataInSphere(int amount) {
    double a, b, c;
    vector<Vector> points;
    ofstream output;

    output.open("../static/sphere.js");
    output << "var sphere = [";

    while (amount) {
        a = randDoubleNumber();
        b = randDoubleNumber();
        c = randDoubleNumber();

        Vector p(a, b, c);

        if (p.isInSphere(radius_outer, radius_inner)) {
            output << endl << "[" << a << ", " << b << ", " << c << "],";
            amount--;

            points.push_back(p);
        }
    };

    output << endl << "]";
    output.close();

    return points;
}

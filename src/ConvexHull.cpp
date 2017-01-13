//
// Created by adele on 1/12/17.
//

#include <fstream>
#include "ConvexHull.h"

ConvexHull::ConvexHull(double a) {
    accuracy = a;
}

void ConvexHull::print() {
    for (int i = 0; i < chpoints.size(); i++) {
        chpoints[i].print();
    }
}

void ConvexHull::exportToFile(const string s) {
    ofstream output;
    output.open("../static/" + s + ".js");
    double a, b, c;

    output << "var " + s + " = [";

    for(Point &p : chpoints) {
        output << endl << p << ",";
    }

    output << endl << "]";
    output.close();
}

void ConvexHull::incrementalDevelopment(vector<Point> points) {
    int i;

    for(i = 0; i < 4; i++) {
        chpoints.push_back(points[i]);
    }

    // TODO consider accuracy
    chfaces.push_back(Face(chpoints[0], chpoints[1], chpoints[2]));
    chfaces.push_back(Face(chpoints[0], chpoints[1], chpoints[3]));
    chfaces.push_back(Face(chpoints[0], chpoints[2], chpoints[3]));
    chfaces.push_back(Face(chpoints[1], chpoints[2], chpoints[3]));

    for(; i < points.size(); i++) {
        if (!isInHull(points[i])) {
            // TODO complete
            chpoints.push_back(points[i]);
        }
    }
}

vector<Point> ConvexHull::giftWrapping(vector<Point> points) {
    // TODO implement
    return points;
}

vector<Point> ConvexHull::quickHull(vector<Point> points) {
    // TODO implement
    return vector<Point>();
}

// TODO refactor
bool ConvexHull::isInHull(Point &point) {
    for (Face f : chfaces) {
        Point p2f = f.getA() - point;
        double d = p2f.dot(f.normal());
        cout << d << endl;
        //d /= p2f.norm();

        if (abs((int)d) > accuracy)
            return false;
    }

    return true;
}

//
// Created by adele on 1/12/17.
//

#include "Point.h"

Point::Point(double a, double b, double c) {
    x = a;
    y = b;
    z = c;
}

void Point::print() {
    cout << "(" << x << ", " << y << ", " << z << ") ";
}

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

bool Point::isInBall(int radius) {
    return x * x + y * y + z * z <= radius * radius;
}

bool Point::isInSphere(int radiusOuter, int radiusInner) {
    double distance = x * x + y * y + z * z;
    return distance <= radiusOuter * radiusOuter && distance >= radiusInner * radiusInner;
}

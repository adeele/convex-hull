//
// Created by adele on 1/12/17.
//

#include <cmath>
#include "Point.h"

Point::Point() {
    x = 0;
    y = 0;
    z = 0;
}

Point::Point(double a, double b, double c) {
    x = a;
    y = b;
    z = c;
}

double Point::getX() {
    return x;
}

double Point::getY() {
    return y;
}

double Point::getZ() {
    return z;
}

ostream& operator<< (ostream& os, const Point& obj) {
    os << "[" << obj.x << ", " << obj.y << ", " << obj.z << "]";
    return os;
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

// TODO refactor
Point Point::cross(Point p) {
    return Point(y * p.z - p.y * z, z * p.x - p.z * x, x * p.y - p.x * y);
}

// TODO refactor
double Point::dot(Point p) {
    return x * p.x + y * p.y + z * p.z;
}

// TODO refactor
double Point::norm() {
    return sqrt(x*x + y*y + z*z);
}
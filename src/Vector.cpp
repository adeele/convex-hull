//
// Created by adele on 1/12/17.
//

#include <cmath>
#include <vector>
#include "Vector.h"
#include "Face.h"

Vector::Vector() {
    x = 0;
    y = 0;
    z = 0;
}

Vector::Vector(double a, double b, double c) {
    x = a;
    y = b;
    z = c;
}

Vector Vector::operator- (const Vector &p)const {
    return Vector(x - p.x, y - p.y, z - p.z);
}

bool Vector::operator== (const Vector &p) const{
    return x == p.x && y == p.y && z == p.z;
}

ostream& operator<< (ostream& os, const Vector& obj) {
    os << "[" << obj.x << ", " << obj.y << ", " << obj.z << "]";
    return os;
}

// TODO CLEANUP remove print
void Vector::print() const {
    cout << "(" << x << ", " << y << ", " << z << ") ";
}

bool Vector::isInBall(int radius) const {
    return x * x + y * y + z * z <= radius * radius;
}

bool Vector::isInSphere(int radiusOuter, int radiusInner) const {
    double distance = x * x + y * y + z * z;
    return distance <= radiusOuter * radiusOuter && distance >= radiusInner * radiusInner;
}

double Vector::getLength()const {
    return sqrt(x * x + y * y + z * z);
}

double Vector::scalarProduct(const Vector &p) {
    return x * p.x + y * p.y + z * p.z;
}

Vector Vector::crossProduct(Vector &p) {
    return Vector(y * p.z - p.y * z, z * p.x - p.z * x, x * p.y - p.x * y);
}

Vector Vector::normalise() {
    double d = getLength();
    return Vector(x / d, y / d, z / d);
}

double Vector::getDistance(const Vector &a)const {
    Vector v = *this - a;
    return v.getLength();
}

double Vector::getDistance(const Vector &a, const Vector &b)const {
    Vector pointToLine = *this - a;
    Vector line = b - a;
    return line.crossProduct(pointToLine).getLength() / line.getLength();
}

double Vector::getDistance(const Vector &a, const Vector &b, const Vector &c)const {
    Vector normal = Face::normal(a, b, c);
    Vector diffVec = *this - a;
    return abs(normal.scalarProduct(diffVec) / normal.getLength());
}

Vector Vector::getFliped() {
    return Vector(-x, -y, -z);
}

bool Vector::smallerYThan(const Vector &toCompare) const {
    return y < toCompare.y;
}

bool Vector::isOnTheRight(const Vector a, const Vector b) const{
    return (b.x - a.x) * (y - a.y) - (b.y - a.y) * (x - a.x) < 0;
}

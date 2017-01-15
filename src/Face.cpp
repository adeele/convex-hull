//
// Created by adele on 1/13/17.
//

#include <vector>
#include "Vector.h"
#include "Face.h"

Face::Face() {}

Face::Face(const Vector &x, const Vector &y, const Vector &z) {
    a = x;
    b = y;
    c = z;
    n = normal();
}

Vector Face::normal() {
    return normal(a, b, c);
}

Vector Face::normal(const Vector &a, const Vector &b, const Vector &c) {
    Vector v1 = b - a;
    Vector v2 = c - a;
    Vector n = v1.crossProduct(v2);
    return n.normalise();
}

double Face::getSignedDistance(const Vector &p) {
    Vector diffVec = p - a;
    return n.scalarProduct(diffVec) / n.getLength();
}

bool Face::isDirectedTowardsPoint(const Vector &p) {
    Vector diffVec = p - a;
    double ret = diffVec.scalarProduct(n);
    return  ret > -0.01;
}

Vector Face::getA()const {
    return a;
}

Vector Face::getB()const {
    return b;
}

Vector Face::getC()const {
    return c;
}

ostream &operator<<(ostream &os, const Face &obj) {
    os << "[" << obj.getA() << ", " << obj.getB() << ", " << obj.getC() << "]";
    return os;
}

void Face::setDisc(const Vector &vector1) {
    disc = n.scalarProduct(vector1);
}

double Face::getScalarWithNormal(const Vector &vector) {
    return n.scalarProduct(vector);
}

double Face::getDisc() {
    return disc;
}

void Face::flipNormal() {
    n = n.getFliped();
}

void Face::flipDisc() {
    disc = -disc;
}

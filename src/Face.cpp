//
// Created by adele on 1/13/17.
//

#include "Point.h"
#include "Face.h"

Face::Face() {}

Face::Face(Point x, Point y, Point z) {
    a = x;
    b = y;
    c = z;
}

// TODO refactor
Point Face::getA() {
    return Point(a);
}

// TODO refactor
Point Face::normal() {
    Point dir1 = b - a;
    Point dir2 = c - a;
    Point n  = dir1.cross(dir2);
    double d = n.norm();
    return Point(n.getX() / d, n.getY() / d, n.getZ() / d);
}

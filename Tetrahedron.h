//
// Created by adele on 1/12/17.
//

#ifndef AAL_TETRAHEDRON_H
#define AAL_TETRAHEDRON_H

#include "Point.h"

class Tetrahedron {
    Point a;
    Point b;
    Point c;
    Point d;

public:
    Tetrahedron(Point a, Point b, Point c, Point d);
};

#endif //AAL_TETRAHEDRON_H

//
// Created by adele on 1/12/17.
//

#ifndef AAL_PLANE_H
#define AAL_PLANE_H

#include "Point.h"

class Plane {
    Point a;
    Point b;
    Point c;

public:
    Plane(Point a, Point b, Point c);
};

#endif //AAL_PLANE_H

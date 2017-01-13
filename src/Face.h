//
// Created by adele on 1/12/17.
//

#ifndef AAL_PLANE_H
#define AAL_PLANE_H

#include "Point.h"

class Face {
    Point a;
    Point b;
    Point c;

public:
    Face();
    Face(Point x, Point y, Point z);
    Point getA();
    Point normal();
};

#endif //AAL_PLANE_H

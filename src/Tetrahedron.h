//
// Created by adele on 1/12/17.
//

#ifndef AAL_TETRAHEDRON_H
#define AAL_TETRAHEDRON_H

#include "Vector.h"

class Tetrahedron {
    Vector a;
    Vector b;
    Vector c;
    Vector d;

public:
    Tetrahedron(Vector a, Vector b, Vector c, Vector d);
};

#endif //AAL_TETRAHEDRON_H

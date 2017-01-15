//
// Created by adele on 1/12/17.
//

#ifndef AAL_PLANE_H
#define AAL_PLANE_H

#include "Vector.h"

class Face {
    Vector a;
    Vector b;
    Vector c;
    Vector n;
    double disc;

public:
    Face();
    Face(const Vector &x, const Vector &y, const Vector &z);
    Vector normal();
    bool isDirectedTowardsPoint(const Vector &vector);
    double getSignedDistance(const Vector &p);
    Vector getA()const;
    Vector getB()const;
    Vector getC()const;
    static Vector normal(const Vector &a, const Vector &b, const Vector &c);
    friend ostream& operator<< (ostream& os, const Face& obj);
    void setDisc(const Vector &vector1);
    double getScalarWithNormal(const Vector &vector);

    double getDisc();

    void flipNormal();

    void flipDisc();
};

#endif //AAL_PLANE_H

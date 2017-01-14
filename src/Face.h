//
// Created by adele on 1/12/17.
//

#ifndef AAL_PLANE_H
#define AAL_PLANE_H

#include "Vector.h"
typedef std::vector<Vector>::const_iterator it;

class Face {
    it a;
    it b;
    it c;
    Vector n;
    double disc;

public:
    Face();
    Face(it x, it y, it z);
    Vector normal();
    bool isDirectedTowardsPoint(const Vector &vector);
    double getSignedDistance(const Vector &p);
    it getA()const;
    it getB()const;
    it getC()const;
    static Vector normal(const Vector &a, const Vector &b, const Vector &c);
    friend ostream& operator<< (ostream& os, const Face& obj);
    void setDisc(const Vector &vector1);
    double getScalarWithNormal(const Vector &vector);

    double getDisc();

    void flipNormal();

    void flipDisc();
};

#endif //AAL_PLANE_H

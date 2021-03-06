//
// Created by adele on 1/12/17.
//

#ifndef AAL_POINT_H
#define AAL_POINT_H

#include <iostream>

using namespace std;

class Vector {
    double x;
    double y;
    double z;

public:
    Vector();
    Vector(double a, double b, double c);

    Vector operator- (const Vector &p)const;
    bool operator== (const Vector &p) const;
    friend ostream& operator<< (ostream& os, const Vector& obj);

    // TODO CLEANUP remove print
    void print() const;
    bool isInSphere(int radiusOuter, int radiusInner) const;
    bool isInBall(int radius) const;
    double getLength() const;
    Vector normalise();
    double getDistance(const Vector &a)const;
    double getDistance(const Vector &a, const Vector &b)const;
    double getDistance(const Vector &a, const Vector &b, const Vector &c)const;
    Vector crossProduct(Vector &p);
    double scalarProduct(const Vector &p);
    Vector getFliped();
    bool smallerYThan(const Vector &toCompare) const;
    bool isOnTheRight(const Vector a, const Vector b) const;
};


namespace std {
    template <>
    class hash<Vector>{
    public :
        size_t operator()(const Vector &v) const{
            return hash<double>() (v.getLength());
        }
    };
};

#endif //AAL_POINT_H
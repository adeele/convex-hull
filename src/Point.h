//
// Created by adele on 1/12/17.
//

#ifndef AAL_POINT_H
#define AAL_POINT_H

#include <iostream>

using namespace std;

class Point {
    double x;
    double y;
    double z;

public:
    Point(double a, double b, double c);
    void print();
    bool isInSphere(int radiusOuter, int radiusInner);
    bool isInBall(int radius);
};

#endif //AAL_POINT_H

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
    Point();
    Point(double a, double b, double c);
    double getX();
    double getY();
    double getZ();

    // TODO move definition
    Point operator- (Point &p) {
        return Point(x - p.x, y - p.y, z - p.z);
    }

    friend ostream& operator<< (ostream& os, const Point& obj);
    void print();
    bool isInSphere(int radiusOuter, int radiusInner);
    bool isInBall(int radius);
    Point cross(Point p);
    double norm();
    double dot(Point p);
};

#endif //AAL_POINT_H
//
// Created by adele on 1/12/17.
//

#ifndef AAL_CONVEXHULL_H
#define AAL_CONVEXHULL_H

#include <vector>
#include "Point.h"
#include "Face.h"

class ConvexHull {
    vector<Point> chpoints;
    vector<Face> chfaces;
    double accuracy;

public:
    ConvexHull(double d);
    void print();
    void incrementalDevelopment(vector<Point> points);
    vector<Point> giftWrapping(vector<Point> points);
    vector<Point> quickHull(vector<Point> points);
    bool isInHull(Point &point);
    void exportToFile(const string s);
};

#endif //AAL_CONVEXHULL_H
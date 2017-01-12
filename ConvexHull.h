//
// Created by adele on 1/12/17.
//

#ifndef AAL_CONVEXHULL_H
#define AAL_CONVEXHULL_H


#include <vector>
#include "Point.h"

class ConvexHull {
    vector<Point> convexHullPoints;

public:
    ConvexHull();
    vector<Point> incrementalDevelopment(vector<Point> points, double accuracy);
    vector<Point> giftWrapping(vector<Point> points, double accuracy);
    vector<Point> quickHull(vector<Point> points, double accuracy);
};


#endif //AAL_CONVEXHULL_H

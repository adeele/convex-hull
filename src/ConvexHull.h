//
// Created by adele on 1/12/17.
//

#ifndef AAL_CONVEXHULL_H
#define AAL_CONVEXHULL_H

#include <vector>
#include <unordered_map>
#include <list>
#include "Vector.h"
#include "Face.h"

class ConvexHull {
    vector<Vector> chpoints;
    list<Face> chfaces;
    double accuracy;

public:
    ConvexHull(double d);

    // TODO CLEANUP remove print
    void print();
    void exportToFile(const string s);
    void incrementalDevelopment(const vector<Vector> &points);
    bool isInHull(const Vector &point);
    void giftWrapping(vector<Vector> points);
    vector<Vector> quickHull(vector<Vector> points);
    void removeFaceEdges(const Face &face, unordered_map<Vector, unordered_map<Vector, int>> &tab);
    void addFaceEdges(Face &face, unordered_map<Vector, unordered_map<Vector, int>> &tab, Vector &additional);
};

#endif //AAL_CONVEXHULL_H
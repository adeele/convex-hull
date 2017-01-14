//
// Created by adele on 1/12/17.
//

#ifndef AAL_CONVEXHULL_H
#define AAL_CONVEXHULL_H

#include <vector>
#include <list>
#include "Vector.h"
#include "Face.h"

typedef vector<it> vit;

class ConvexHull {
    vit chpoints;
    list<Face> chfaces;
    double accuracy;
    vector<Vector> pts;

public:
    ConvexHull(double d);

    // TODO CLEANUP remove print
    void print();
    void exportToFile(const string s);
    void incrementalDevelopment(const vector<Vector> &points);
    bool isInHull(const Vector &point);
    vector<Vector> giftWrapping(vector<Vector> points);
    vector<Vector> quickHull(vector<Vector> points);
    void removeFaceEdges(Face face, int **tab, it vector1);

    void addFaceEdges(Face &face, int **tab, it vector1, it additional);
};

#endif //AAL_CONVEXHULL_H
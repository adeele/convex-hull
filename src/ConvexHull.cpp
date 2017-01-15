//
// Created by adele on 1/12/17.
//

#include <fstream>
#include <unordered_set>
#include <functional>
#include <queue>
#include <unordered_map>
#include "ConvexHull.h"

ConvexHull::ConvexHull(double a) {
    accuracy = a;
}

// TODO CLEANUP remove print
void ConvexHull::print() {
    for (int i = 0; i < chpoints.size(); i++) {
        chpoints[i].print();
    }
}

void ConvexHull::exportToFile(const string s) {
    ofstream output("../static/" + s + ".js");

    output << "var " + s + " = [";

    for(auto p : chpoints) {
        output << endl << p << ",";
    }

    output << endl << "]";
    output.close();
}


void ConvexHull::incrementalDevelopment(const vector<Vector> &points) {
    unordered_map<Vector, unordered_map<Vector, int>> edgesMap(points.size());

    int i = 0;
    Vector tetrahedron[4] = {points[0]};
    while (points[++i].getDistance(tetrahedron[0]) < accuracy);
    tetrahedron[1] = points[i];
    while (points[++i].getDistance(tetrahedron[0], tetrahedron[1]) < accuracy);
    tetrahedron[2] = points[i];
    while (points[++i].getDistance(tetrahedron[0], tetrahedron[1], tetrahedron[2]) < accuracy);
    tetrahedron[3] = points[i];

    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            for (int k = j + 1; k < 4; k++) {
                Face f(tetrahedron[i], tetrahedron[j], tetrahedron[k]);
                addFaceEdges(f, edgesMap, tetrahedron[6 - i - j - k]);
                chfaces.push_back(f);
            }
        }
    }

    for(i++; i < points.size(); i++) {
        if (!isInHull(points[i])) {
            list<Face> pom;

            for (auto f : chfaces) {
                if (f.isDirectedTowardsPoint(points[i])) {
                    removeFaceEdges(f, edgesMap);
                } else {
                    pom.push_back(f);
                }
            }

            chfaces = pom;

            for (auto &f : chfaces) {
                auto a = f.getA();
                auto b = f.getB();
                auto c = f.getC();

                if (edgesMap[a][b] == 1) {
                    Face f(a, b, points[i]);
                    addFaceEdges(f, edgesMap, c);
                    chfaces.push_back(f);
                }

                if (edgesMap[b][c] == 1) {
                    Face f(b, c, points[i]);
                    addFaceEdges(f, edgesMap, a);
                    chfaces.push_back(f);
                }

                if (edgesMap[a][c] == 1) {
                    Face f(a, c, points[i]);
                    addFaceEdges(f, edgesMap, b);
                    chfaces.push_back(f);
                }
            }
        }
    }

    unordered_set<Vector> set(10);

    for (auto f : chfaces) {
        if (set.count(f.getA()) == 0) {
            set.insert(f.getA());
            chpoints.push_back(f.getA());
        }

        if (set.count(f.getB()) == 0) {
            set.insert(f.getB());
            chpoints.push_back(f.getB());
        }

        if (set.count(f.getC()) == 0) {
            set.insert(f.getC());
            chpoints.push_back(f.getC());
        }
    }
}

bool ConvexHull::isInHull(const Vector &point) {
    for (Face f : chfaces) {
        double signedDistance = f.getSignedDistance(point);

        if (signedDistance > accuracy) {
            return false;
        }
    }

    return true;
}

void ConvexHull::giftWrapping(vector<Vector> points) {
    /*
    pts = points;
    it min1 = pts.begin();
    it min2 = pts.begin();

    for (it i = pts.begin(); i < pts.end(); i++) {
        if (i->smallerYThan(*min1)) {
            min1 = i;
        }
    }

    for (it i = pts.begin(); i < pts.end(); i++) {
        if (i->isOnTheRight(*min1, *min2)) {
            min2 = i;
        }
    }

    chpoints.push_back(min1);
    chpoints.push_back(min2);

    queue<pair<it, it>> q;
    q.push(make_pair(min1, min2));

    while (q.size()) {
        for (it i = pts.begin(); i < pts.end(); i++) {

        }
    }
    */

        // dla kazdego z pozostalych punktow: czy wszytskie punkty leza po lewej stronie sciany PQC
}

vector<Vector> ConvexHull::quickHull(vector<Vector> points) {
    // TODO LATER implement
    return vector<Vector>();
}

void ConvexHull::addFaceEdges(Face &face, unordered_map<Vector, unordered_map<Vector, int>> &tab, Vector &additional) {
    Vector a = face.getA();
    Vector b = face.getB();
    Vector c = face.getC();
    tab[a][b]++;
    tab[b][a]++;
    tab[c][b]++;
    tab[b][c]++;
    tab[a][c]++;
    tab[c][a]++;

    face.setDisc(a);
    double d = face.getScalarWithNormal(additional);

    if (d > face.getDisc()) {
        face.flipNormal();
        face.flipDisc();
    }
}

void ConvexHull::removeFaceEdges(const Face &face, unordered_map<Vector, unordered_map<Vector, int>> &tab) {
    Vector a = face.getA();
    Vector b = face.getB();
    Vector c = face.getC();
    tab[a][b]--;
    tab[b][a]--;
    tab[c][b]--;
    tab[b][c]--;
    tab[a][c]--;
    tab[c][a]--;
}

//
// Created by adele on 1/12/17.
//

#include <fstream>
#include <unordered_set>
#include <algorithm>
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

    for (i++; i < points.size(); i++) {
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
    int i;
    Vector min1 = points[0];

    for (i = 1; i < points.size(); i++) {
        if (points[i].smallerYThan(min1)) {
            min1 = points[i];
        }
    }

    chpoints.push_back(min1);

    Vector min2 = points[0];

    for (i = 1; i < points.size(); i++) {
        if (points[i].isOnTheRight(min1, min2)) {
            min2 = points[i];
        }
    }

    chpoints.push_back(min2);

    queue<pair<Vector, Vector>> q;
    q.push(make_pair(min1, min2));

    while (q.size() > 0) {
        Vector c = points[0];

        for (i = 1; i < points.size(); i++) {
            Face f(q.front().first, q.front().second, c);

            double x = f.getSignedDistance(points[i]);
            if (f.getSignedDistance(points[i]) > accuracy) {
                c = points[i];
            }
        }

        vector<Vector>::iterator it = find(chpoints.begin(), chpoints.end(), c);

        if (it == chpoints.end()) {
            chpoints.push_back(c);
            q.push(make_pair(q.front().first, c));
            q.push(make_pair(c, q.front().second));
        }

        q.pop();
    }
}

void ConvexHull::quickHull(vector<Vector> points) {
    int i;
    Vector min1 = points[0];

    for (i = 1; i < points.size(); i++) {
        if (points[i].smallerYThan(min1)) {
            min1 = points[i];
        }
    }

    chpoints.push_back(min1);
    Vector min2 = points[0];

    for (i = 1; i < points.size(); i++) {
        if (points[i].getDistance(min1) > min2.getDistance(min1) + accuracy) {
            min2 = points[i];
        }
    }

    chpoints.push_back(min2);
    Vector min3 = points[0];

    for (i = 1; i < points.size(); i++) {
        if (points[i].getDistance(min1, min2) > min3.getDistance(min1, min2) + accuracy) {
            min3 = points[i];
        }
    }

    chpoints.push_back(min3);

    Face f1(min1, min2, min3);
    vector<Vector> pts1, pts2;

    for (Vector v : points) {
        if (f1.getSignedDistance(v) < (-1)*accuracy) {
            pts1.push_back(v);
        } else if (f1.getSignedDistance(v) > accuracy) {
            pts2.push_back(v);
        }
    }

    int x = pts1.size();
    int y = pts2.size();
    quickHullRecursion(f1, pts1);
    f1.flipNormal();
    quickHullRecursion(f1, pts2);
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

void ConvexHull::quickHullRecursion(Face &face, vector<Vector> points) {
    if (points.size() == 0) {
        return;
    }

    Vector v = points[0];

    for (int i = 1; i < points.size(); i++) {
        double x = face.getSignedDistance(points[i]);
        double y = face.getSignedDistance(v) + accuracy;
        if (face.getSignedDistance(points[i]) > face.getSignedDistance(v) + accuracy) {
            v = points[i];
        }
    }

    chpoints.push_back(v);

    vector<Vector> pts1, pts2, pts3;

    Face f1(face.getA(), face.getB(), v);
    f1.setDisc(face.getA());
    double d = f1.getScalarWithNormal(face.getC());

    if (d > f1.getDisc()) {
        f1.flipNormal();
        f1.flipDisc();
    }

    Face f2(face.getA(), face.getC(), v);
    f2.setDisc(face.getA());
    d = f2.getScalarWithNormal(face.getB());

    if (d > f2.getDisc()) {
        f2.flipNormal();
        f2.flipDisc();
    }

    Face f3(face.getC(), face.getB(), v);
    f3.setDisc(face.getC());
    d = f3.getScalarWithNormal(face.getA());

    if (d > f3.getDisc()) {
        f3.flipNormal();
        f3.flipDisc();
    }

    for (Vector v : points) {
        if (f1.getSignedDistance(v) > accuracy) {
            pts1.push_back(v);
        }

        if (f2.getSignedDistance(v) > accuracy) {
            pts2.push_back(v);
        }

        if (f3.getSignedDistance(v) > accuracy) {
            pts3.push_back(v);
        }
    }

    chfaces.push_back(f1);
    chfaces.push_back(f2);
    chfaces.push_back(f3);

    quickHullRecursion(f1, pts1);
    quickHullRecursion(f2, pts2);
    quickHullRecursion(f3, pts3);
}

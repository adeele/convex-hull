//
// Created by adele on 1/12/17.
//

#include <fstream>
#include <unordered_set>
#include <functional>
#include "ConvexHull.h"

ConvexHull::ConvexHull(double a) {
    accuracy = a;
}

// TODO CLEANUP remove print
void ConvexHull::print() {
    for (int i = 0; i < chpoints.size(); i++) {
        chpoints[i]->print();
    }
}

void ConvexHull::exportToFile(const string s) {
    ofstream output("../static/" + s + ".js");

    output << "var " + s + " = [";

    for(auto p : chpoints) {
        output << endl << *p << ",";
    }

    output << endl << "]";
    output.close();
}

void ConvexHull::incrementalDevelopment(const vector<Vector> &points) {
    pts = points;

    int **edges = new int *[pts.size()];
    for (int i = 0; i < pts.size(); i++) {
        edges[i] = new int[pts.size()]();
    }

    int i = 0;
    chpoints.push_back(pts.begin() + i);
    while (pts[++i].getDistance(*chpoints[0]) < accuracy);
    chpoints.push_back(pts.begin() + i);
    while (pts[++i].getDistance(*chpoints[0], *chpoints[1]) < accuracy);
    chpoints.push_back(pts.begin() + i);
    while (pts[++i].getDistance(*chpoints[0], *chpoints[1], *chpoints[2]) < accuracy);
    chpoints.push_back(pts.begin() + i);

    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            for (int k = j + 1; k < 4; k++) {
                Face f(chpoints[i], chpoints[j], chpoints[k]);
                addFaceEdges(f, edges, pts.begin(), chpoints[6 - i - j - k]);
                chfaces.push_back(f);
            }
        }
    }

    for(i++; i < pts.size(); i++) {
        if (!isInHull(pts[i])) {
            chpoints.push_back(pts.begin() + i);

            list<Face> pom;

            for (auto f : chfaces) {
                if (f.isDirectedTowardsPoint(pts[i])) {
                    removeFaceEdges(f, edges, pts.begin());
                } else {
                    pom.push_back(f);
                }
            }

            chfaces = pom;

            for (auto &f : chfaces) {
                auto a = f.getA();
                auto b = f.getB();
                auto c = f.getC();
                auto v = pts.begin();

                unsigned x = a - v;
                unsigned y = b - v;
                unsigned z = c - v;
                if (edges[a - v][b - v] == 1) {
                    Face f(a, b, pts.begin() + i);
                    addFaceEdges(f, edges, pts.begin(), c);
                    chfaces.push_back(f);
                }

                if (edges[b - v][c - v] == 1) {
                    Face f(b, c, pts.begin() + i);
                    addFaceEdges(f, edges, pts.begin(), a);
                    chfaces.push_back(f);
                }

                if (edges[a - v][c - v] == 1) {
                    Face f(a, c, pts.begin() + i);
                    addFaceEdges(f, edges, pts.begin(), b);
                    chfaces.push_back(f);
                }
            }
        }
    }

    unordered_set<Vector, function<size_t (const Vector &v)>> set(10, [](const Vector &v){
        return hash<double>() (v.getLength());
    });

    vit tmp;
    for (auto f : chfaces) {
        if (set.count(*f.getA()) == 0) {
            set.insert(*f.getA());
            tmp.push_back(f.getA());
        }

        if (set.count(*f.getB()) == 0) {
            set.insert(*f.getB());
            tmp.push_back(f.getB());
        }

        if (set.count(*f.getC()) == 0) {
            set.insert(*f.getC());
            tmp.push_back(f.getC());
        }
    }

    chpoints = tmp;
    cout << chpoints.size();
}

bool ConvexHull::isInHull(const Vector &point) {
    for (Face f : chfaces) {
        double signedDistance = f.getSignedDistance(point);

        if (signedDistance < accuracy) {
            return false;
        }
    }

    return true;
}

vector<Vector> ConvexHull::giftWrapping(vector<Vector> points) {
    // TODO LATER implement
    return points;
}

vector<Vector> ConvexHull::quickHull(vector<Vector> points) {
    // TODO LATER implement
    return vector<Vector>();
}

void ConvexHull::addFaceEdges(Face &face, int **tab, it v, it additonal) {
    it a = face.getA();
    it b = face.getB();
    it c = face.getC();
    tab[a - v][b - v]++;
    tab[b - v][a - v]++;
    tab[c - v][b - v]++;
    tab[b - v][c - v]++;
    tab[a - v][c - v]++;
    tab[c - v][a - v]++;

    face.setDisc(*a);
    double d = face.getScalarWithNormal(*additonal);

    if (d > face.getDisc()) {
        face.flipNormal();
        face.flipDisc();
    }
}

void ConvexHull::removeFaceEdges(Face face, int **tab, it v) {
    it a = face.getA();
    it b = face.getB();
    it c = face.getC();
    tab[a - v][b - v]--;
    tab[b - v][a - v]--;
    tab[c - v][b - v]--;
    tab[b - v][c - v]--;
    tab[a - v][c - v]--;
    tab[c - v][a - v]--;
}

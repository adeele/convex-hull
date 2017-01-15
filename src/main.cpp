#include <iostream>
#include <vector>
#include "Vector.h"
#include "Generator.h"
#include "ConvexHull.h"

using namespace std;

int main(int argc, char *argv[]) {
    int pointsAmount;
    double accuracy;

    sscanf(argv[1], "%d", &pointsAmount);
    sscanf(argv[2], "%lf", &accuracy);

    if (argc > 3) {
        int seed;
        sscanf(argv[3], "%d", &seed);
        srand(seed);
    } else {
        srand(time(NULL));
    }

    Generator g;
    vector<Vector> points = g.generateDataInCube(pointsAmount);

    ConvexHull ch(accuracy);
    /*
    ConvexHull ch(0.1);
    ch.incrementalDevelopment({
                                      Vector(0.0, 0.0, -0.5),
                                      Vector(1.0, 0.0, 0.0),
                                      Vector(0.0, 1.0, 0.0),
                                      Vector(1.0, 1.0, -0.5),
                                      Vector(0.5, 0.5, 0.5),
                                      Vector(0.5, 0.5, 1)
                              });
                              */
    ch.incrementalDevelopment(points);
    ch.exportToFile("incdev");

    // TODO LATER solve ball and sphere as well
     g.generateDataInBall(pointsAmount);
     g.generateDataInSphere(pointsAmount);

    return 0;
}
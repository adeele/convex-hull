#include <iostream>
#include <vector>
#include "Point.h"
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
    vector<Point> points = g.generateDataInCube(pointsAmount);

    ConvexHull ch;
    points = ch.incrementalDevelopment(points, accuracy);

    points[0].print();

    // TODO solve ball and sphere as well
//  g.generateDataInBall(pointsAmount);
//  g.generateDataInSphere(pointsAmount);

    return 0;
}
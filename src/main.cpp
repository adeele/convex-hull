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

    /*
    ConvexHull cubeCH(accuracy);
    vector<Vector> cubePoints = g.generateDataInCube(pointsAmount);
    cubeCH.incrementalDevelopment(cubePoints);
    cubeCH.exportToFile("incdevcube");

    ConvexHull ballCH(accuracy);
    vector<Vector> ballPoints = g.generateDataInBall(pointsAmount);
    ballCH.incrementalDevelopment(ballPoints);
    ballCH.exportToFile("incdevball");

    ConvexHull sphereCH(accuracy);
    vector<Vector> spherePoints = g.generateDataInSphere(pointsAmount);
    sphereCH.incrementalDevelopment(spherePoints);
    sphereCH.exportToFile("incdevsphere");
     */

    /*
    ConvexHull cubeCH(accuracy);
    vector<Vector> cubePoints = g.generateDataInCube(pointsAmount);
    cubeCH.giftWrapping(cubePoints);
    cubeCH.exportToFile("giftwrapcube");

    ConvexHull ballCH(accuracy);
    vector<Vector> ballPoints = g.generateDataInBall(pointsAmount);
    ballCH.giftWrapping(ballPoints);
    ballCH.exportToFile("giftwrapball");

    ConvexHull sphereCH(accuracy);
    vector<Vector> spherePoints = g.generateDataInSphere(pointsAmount);
    sphereCH.giftWrapping(spherePoints);
    sphereCH.exportToFile("giftwrapsphere");
     */

    ConvexHull cubeCH(accuracy);
    vector<Vector> cubePoints = g.generateDataInCube(pointsAmount);

    /*
    vector <Vector> cubePoints;
    cubePoints.push_back(Vector(0, 0, 0));
    cubePoints.push_back(Vector(0, 100, 0));
    cubePoints.push_back(Vector(100, 0, 0));
    cubePoints.push_back(Vector(50, 50, 50));
    cubePoints.push_back(Vector(50, 50, 100));
    cubePoints.push_back(Vector(100, 100, 30));
     */

    cubeCH.quickHull(cubePoints);
    cubeCH.exportToFile("quickcube");

    return 0;
}
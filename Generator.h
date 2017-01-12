//
// Created by adele on 1/12/17.
//

#ifndef AAL_GENERATOR_H
#define AAL_GENERATOR_H

#include "Point.h"

#define radius_outer 100
#define radius_inner 80

class Generator {
public:
    Generator();
    std::vector<Point> generateDataInCube(int amount);
    void generateDataInBall(int amount);
    void generateDataInSphere(int amount);
};


#endif //AAL_GENERATOR_H

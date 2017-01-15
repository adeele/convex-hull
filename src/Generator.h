//
// Created by adele on 1/12/17.
//

#ifndef AAL_GENERATOR_H
#define AAL_GENERATOR_H

#include "Vector.h"

#define radius_outer 100
#define radius_inner 80

class Generator {
public:
    Generator();
    std::vector<Vector> generateDataInCube(int amount);
    vector<Vector> generateDataInBall(int amount);
    vector<Vector> generateDataInSphere(int amount);
};

#endif //AAL_GENERATOR_H

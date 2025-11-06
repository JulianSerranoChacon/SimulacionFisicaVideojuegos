#pragma once
#include "ForceGenerator.h"

class WindForceGenerator : public ForceGenerator {
public:
    WindForceGenerator(mVector3D windVel, float k = 1.0f);
    virtual ~WindForceGenerator();

    void addForce(ParticleWithMass* p) override;

private:
    float k1;
};

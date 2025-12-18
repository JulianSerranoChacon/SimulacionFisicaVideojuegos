#pragma once
#include "ForceGenerator.h"

class WindForceGenerator : public ForceGenerator {
public:
    WindForceGenerator(mVector3D windVel, float k = 1.0f);
    virtual ~WindForceGenerator();

    virtual mVector3D addForce(ParticleWithMass* p) override;
    virtual mVector3D addForce(SolidDynamic* s) override;

private:
    float k1;
};

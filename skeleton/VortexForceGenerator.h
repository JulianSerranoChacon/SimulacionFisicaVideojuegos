#pragma once
#include "ForceGenerator.h"
class VortexForceGenerator : public ForceGenerator
{
public:
    VortexForceGenerator(mVector3D center, float k, float strength, double radius);

    void addForce(ParticleWithMass* p) override;

private:
    mVector3D center;
    float K;
    float strenght;
    double radius;
};


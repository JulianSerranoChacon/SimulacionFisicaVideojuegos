#pragma once
#include "ForceGenerator.h"
class VortexForceGenerator : public ForceGenerator
{
public:
    VortexForceGenerator(mVector3D center, float k, float strength, double radius);

    virtual mVector3D addForce(ParticleWithMass* p) override;
    virtual mVector3D addForce(SolidDynamic* s) override;

private:
    mVector3D center;
    float K;
    float strenght;
    double radius;
};


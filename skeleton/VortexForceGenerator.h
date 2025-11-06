#pragma once
#include "ForceGenerator.h"
class VortexForceGenerator : public ForceGenerator
{
public:
    VortexForceGenerator(mVector3D center, float strength);

    void addForce(ParticleWithMass* p) override;

private:
    mVector3D center;
    float K;
};


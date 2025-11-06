#include "WindForceGenerator.h"
#include "ParticleWithMass.h"

WindForceGenerator::WindForceGenerator(mVector3D windVel, float k)
    : ForceGenerator(windVel), k1(k) 
{
}

WindForceGenerator::~WindForceGenerator()
{
}

void WindForceGenerator::addForce(ParticleWithMass* p)
{
    if (!active) return;

    mVector3D relativeVel = forceToAply - p->getVel(); // v_wind - v_particle
    mVector3D accel = relativeVel.scalar(k1); // fuerza proporcional
    p->addAcceleration(accel);
}

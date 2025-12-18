#include "WindForceGenerator.h"
#include "ParticleWithMass.h"
#include "SolidDynamic.h"

WindForceGenerator::WindForceGenerator(mVector3D windVel, float k)
    : ForceGenerator(windVel), k1(k) 
{
}

WindForceGenerator::~WindForceGenerator()
{
}

MVector3 WindForceGenerator::addForce(ParticleWithMass* p)
{
    if (!active) return{ 0,0,0 };

    mVector3D relativeVel = forceToAply - p->getVel(); // v_wind - v_particle
    mVector3D accel = relativeVel.scalar(k1); // fuerza proporcional
    return accel;
}

mVector3D WindForceGenerator::addForce(SolidDynamic* s)
{
    if (!active) return{ 0,0,0 };



    Vector3 relativeVel = forceToAply.toVector3() - s->getObject()->getLinearVelocity(); // v_wind - v_particle
    Vector3 accel = relativeVel * k1; // fuerza proporcional
    return mVector3D(accel.x,accel.y,accel.z);
}

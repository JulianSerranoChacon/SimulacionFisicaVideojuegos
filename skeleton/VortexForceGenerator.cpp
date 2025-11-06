#include "VortexForceGenerator.h"
#include "ParticleWithMass.h"

VortexForceGenerator::VortexForceGenerator(mVector3D center, float strength)
    : ForceGenerator({ 0,0,0 }), center(center), K(strength) 
{
}

void VortexForceGenerator::addForce(ParticleWithMass* p)
{
    if (!active) return;

    Vector3 r = p->getPos() - center.toVector3();
    Vector3 tangential(-r.y, r.x, r.z); // 2D tangencial, z se mantiene
    Vector3 accel = tangential * K;
    p->addAcceleration(MVector3(accel.x,accel.y,accel.z));
}

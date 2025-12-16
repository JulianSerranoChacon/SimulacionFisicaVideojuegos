#include "VortexForceGenerator.h"
#include "ParticleWithMass.h"
#include <algorithm>

VortexForceGenerator::VortexForceGenerator(mVector3D center, float k, float strength, double radius)
    : ForceGenerator({ 0,0,0 }), center(center), K(k), strenght(strenght), radius(radius)
{
}

MVector3 VortexForceGenerator::addForce(ParticleWithMass* p)
{
    if (!active) return{ 0,0,0 };

    Vector3 r = p->getPos() - center.toVector3();
    Vector3 tangential(r.z, 0, -r.x); // 2D tangencial, z se mantiene
    Vector3 accel = tangential * K;
    double forceMag = strenght * (r.magnitude() / radius);
    forceMag = std::clamp(forceMag, 0.0, 50.0);
    Vector3 totalForce = tangential * forceMag;
    
    return MVector3(accel.x,accel.y,accel.z);
}

#include "gravityForceGenerator.h"
#include "ParticleWithMass.h"

gravityForceGenerator::gravityForceGenerator(mVector3D force): ForceGenerator(force)
{
}

gravityForceGenerator::~gravityForceGenerator()
{
}

mVector3D gravityForceGenerator::addForce(ParticleWithMass* p)
{
	if (!active || p->getMass() == 0)
		return { 0,0,0 };

	mVector3D accel = forceToAply * p->getMass();
	return accel;
}

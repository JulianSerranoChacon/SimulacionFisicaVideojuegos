#include "gravityForceGenerator.h"
#include "ParticleWithMass.h"

gravityForceGenerator::gravityForceGenerator(mVector3D force): ForceGenerator(force)
{
}

gravityForceGenerator::~gravityForceGenerator()
{
}

void gravityForceGenerator::addForce(ParticleWithMass* p)
{
	if (!active || p->getMass() == 0)
		return;

	mVector3D accel = {forceToAply.getX()/p->getMass(),forceToAply.getY() / p->getMass() ,forceToAply.getZ()/p->getMass()};
	p->addAcceleration(accel);
}

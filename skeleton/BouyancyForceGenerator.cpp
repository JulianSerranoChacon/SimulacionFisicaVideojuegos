#include "BouyancyForceGenerator.h"
#include "ParticleWithMass.h"
#include "SolidDynamic.h"

BouyancyForceGenerator::BouyancyForceGenerator(float h, float v, float d, ParticleWithMass* liquid): height(h),volume(v),liquidDensity(d),
liquidParticle(liquid)
{
}

mVector3D BouyancyForceGenerator::addForce(ParticleWithMass* p)
{
	float h = p->getPos().y;
	float h0 = liquidParticle->getPos().y;

	float immersed = 0.0;

	if (h - h0 > height * 0.5) {
		immersed = 0.0;
	}
	else if (h0 - h > height * 0.5) {
		immersed = 1.0;
	}
	else {
		immersed = (h0 - h) / height + 0.5;
	}

	float y = liquidDensity * volume * immersed * gravity;

	return mVector3D(0,y,0);
}

mVector3D BouyancyForceGenerator::addForce(SolidDynamic* s)
{
	float h = s->getPos().y;
	float h0 = liquidParticle->getPos().y;

	float immersed = 0.0;

	if (h - h0 > height * 0.5) {
		immersed = 0.0;
	}
	else if (h0 - h > height * 0.5) {
		immersed = 1.0;
	}
	else {
		immersed = (h0 - h) / height + 0.5;
	}

	float y = liquidDensity * volume * immersed * gravity;

	return mVector3D(0, y, 0);
}

BouyancyForceGenerator::~BouyancyForceGenerator()
{
}


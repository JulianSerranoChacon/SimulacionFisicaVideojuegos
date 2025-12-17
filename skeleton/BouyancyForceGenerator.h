#pragma once
#include "ForceGenerator.h"
class BouyancyForceGenerator : public ForceGenerator
{
public:
	BouyancyForceGenerator(float h, float v, float d, ParticleWithMass* liquid);
	virtual mVector3D addForce(ParticleWithMass* p) override;

	virtual ~BouyancyForceGenerator();
protected:
	float height;
	float volume;
	float liquidDensity;
	float gravity = 9.8;

	ParticleWithMass* liquidParticle;
};


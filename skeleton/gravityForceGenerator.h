#pragma once
#include "ForceGenerator.h"
class ParticleWithMass;
class gravityForceGenerator: public ForceGenerator
{
public:
	gravityForceGenerator(mVector3D force);
	virtual ~gravityForceGenerator();
	virtual void addForce(ParticleWithMass* p) override;
private:
};


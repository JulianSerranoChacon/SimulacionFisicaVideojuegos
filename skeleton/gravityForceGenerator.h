#pragma once
#include "ForceGenerator.h"
class ParticleWithMass;
class gravityForceGenerator: public ForceGenerator
{
public:
	gravityForceGenerator(mVector3D force);
	virtual ~gravityForceGenerator();
	virtual mVector3D addForce(ParticleWithMass* p) override;
	virtual mVector3D addForce(SolidDynamic* s) override;
private:
};


#pragma once
#include "ForceGenerator.h"

class ParticleWithMass;
class SpringForceGenerator: public ForceGenerator
{
public:
	SpringForceGenerator(double k, double resting_lenght, ParticleWithMass* other);

	virtual mVector3D addForce(ParticleWithMass* p);

	inline virtual void setK(double nK) { k = nK; };

	virtual ~SpringForceGenerator();

private:
	double k;
	double resting_lenght;
	ParticleWithMass* other;

};


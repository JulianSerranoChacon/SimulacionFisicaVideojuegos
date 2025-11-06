#pragma once
#include "Vector3D.h"
#include <vector>
using mVector3D = Vector3D<float>;
class ParticleWithMass;
class ForceGenerator
{
public:
	ForceGenerator(mVector3D force);
	virtual ~ForceGenerator();
	inline virtual void setActive(bool active) { active = active; }
	inline virtual bool getActive() { return active; }
	virtual void addForce(ParticleWithMass* p) = 0;
protected:
	mVector3D forceToAply;
	bool active;

};


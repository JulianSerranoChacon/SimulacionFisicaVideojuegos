#include "SpringForceGenerator.h"
#include "ParticleWithMass.h"
#include "SolidDynamic.h"

SpringForceGenerator::SpringForceGenerator(double k, double resting_lenght, ParticleWithMass* other):ForceGenerator(), k(k), resting_lenght(resting_lenght),
other(other)
{
}

MVector3 SpringForceGenerator::addForce(ParticleWithMass* p)
{
	//Particle is the particle to apply the force
	Vector3 relPosVec = other->getPos() - p->getPos();
	Vector3 force;

	const float lenght = relPosVec.normalize();
	const float delta_x = lenght - resting_lenght;

	force = relPosVec * delta_x * k;
	return Vector3D(force.x,force.y,force.z);
}

mVector3D SpringForceGenerator::addForce(SolidDynamic* s)
{//Particle is the particle to apply the force
	Vector3 relPosVec = other->getPos() - s->getPos();
	Vector3 force;

	const float lenght = relPosVec.normalize();
	const float delta_x = lenght - resting_lenght;

	force = relPosVec * delta_x * k;
	return Vector3D(force.x, force.y, force.z);
}

SpringForceGenerator::~SpringForceGenerator()
{
}

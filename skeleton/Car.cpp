#include "Car.h"

Car::Car(MVector3 pos, MVector3 moveDir, double speed, float dumping, float mass, float timeLife, float sizeX,float sizeY,float sizeZ, Vector4 sV):
	ParticleWithMass(pos, MVector3(0,0,0), MVector3(0, 0, 0), dumping, mass, timeLife,size, CreateShape(physx::PxBoxGeometry(sizeX, sizeY, sizeZ)), sv), moveDir(0,0,0), speed(speed)
{
}

void Car::shoot()
{
}

void Car::integrate(double t)
{
	vel_ = moveDir.scalar(speed);
	ParticleWithMass::integrate(t);
	if (pS != nullptr)
		pS->moveTo(pose_.p - Vector3(size/2,0, size / 2));
}

void Car::move(Vector3 v)
{
	moveDir = Vector3D(v.x,v.y,v.z);
	if(pS != nullptr)
		pS->moveTo(v);
}

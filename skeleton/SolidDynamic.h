#pragma once

#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"


using namespace physx;
class SolidDynamic
{
public:
	SolidDynamic(PxScene* gScene, PxPhysics* gPhysics, PxShape* shape, PxTransform& transform,double density, Vector4& color = Vector4(1));
	SolidDynamic(PxScene* gScene, PxPhysics* gPhysics, PxShape* shape, PxTransform& transform, double density,float maxtimeLife,
		Vector4& color = Vector4(1));
	~SolidDynamic();
	bool updateTimeLife(double t);
	void integrate(double t);
	inline PxRigidDynamic* getObject() { return obj_; }

private:
	void createObj(PxScene* gScene, PxShape* shape, PxTransform& transform, double density, Vector4& color = Vector4(1));

	PxPhysics* gPhysics_;
	PxRigidDynamic* obj_;
	PxTransform transform_;
	RenderItem* rItem_;
	double timeLife;
	double maxTimeLife;
};


#pragma once

#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include "ForceGenerator.h"
#include <list>


using namespace physx;
class SolidDynamic
{
public:
	SolidDynamic(PxScene* gScene, PxPhysics* gPhysics, PxShape* shape, PxTransform& transform,double density,
		double staticFriction, double dynamicFriction, double restitution, Vector4& color = Vector4(1));
	SolidDynamic(PxScene* gScene, PxPhysics* gPhysics, PxShape* shape, PxTransform& transform, double density,
		double staticFriction, double dynamicFriction, double restitution, float maxtimeLife, Vector4& color = Vector4(1));
	~SolidDynamic();
	bool updateTimeLife(double t);
	void integrate(double t);
	inline PxRigidDynamic* getObject() { return obj; }
	inline Vector3 getPos() { return transform.p; }
	inline virtual void addForceGenerator(ForceGenerator* fg) { fG.push_back(fg); }

private:
	void createObj(PxScene* gScene, PxShape* shape, PxTransform& transform, double density, double staticFriction, double dynamicFriction,
		double restitution, Vector4& color = Vector4(1));

	PxPhysics* gPhysics;
	PxRigidDynamic* obj;
	PxTransform transform;
	RenderItem* rItem;
	double timeLife;
	double maxTimeLife;
	std::list<ForceGenerator*> fG;
};


#include "SolidDynamic.h"

SolidDynamic::SolidDynamic(PxScene* gScene, PxPhysics* gPhysics, PxShape* shape, PxTransform& transform, double density, Vector4& color) :
	gPhysics_(gPhysics), transform_(transform), maxTimeLife(-1)
{
	createObj(gScene,shape, transform, density, color);
}

SolidDynamic::SolidDynamic(PxScene* gScene, PxPhysics* gPhysics, PxShape* shape, PxTransform& transform, double density,
	float maxtimeLife, Vector4& color): gPhysics_(gPhysics), transform_(transform), maxTimeLife(timeLife)
{
	createObj(gScene, shape, transform, density, color);
}

SolidDynamic::~SolidDynamic()
{
	DeregisterRenderItem(rItem_);
	rItem_ = nullptr;
}

bool SolidDynamic::updateTimeLife(double t) {

	timeLife += t;
	return maxTimeLife > 0 && timeLife < maxTimeLife;
}

void SolidDynamic::createObj(PxScene* gScene, PxShape* shape, PxTransform& transform, double density, Vector4& color)
{
	obj_ = gPhysics_->createRigidDynamic(transform_);
	obj_->setLinearVelocity(Vector3(0, 5, 0));
	obj_->setAngularVelocity(Vector3(0, 0, 0));
	if (shape == nullptr)
		shape = CreateShape(PxBoxGeometry(100, 30, 100));

	obj_->attachShape(*shape);
	gScene->addActor(*obj_);

	PxRigidBodyExt::updateMassAndInertia(*obj_, density);
	rItem_ = new RenderItem(shape, obj_, color);
}

void SolidDynamic::integrate(double t) {

}
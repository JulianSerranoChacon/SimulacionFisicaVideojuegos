#include "SolidStatic.h"

SolidStatic::SolidStatic(PxScene* gScene, PxPhysics* gPhysics, PxShape* shape, PxTransform& transform, Vector4& color): gPhysics_(gPhysics),
transform_(transform)
{
	obj_ = gPhysics_->createRigidStatic(transform_);
	if (shape == nullptr)
		shape = CreateShape(PxBoxGeometry(100,30, 100));

	obj_->attachShape(*shape);
	gScene->addActor(*obj_);

	rItem_ = new RenderItem(shape, obj_, color);
}

SolidStatic::SolidStatic(PxScene* gScene, PxPhysics* gPhysics, PxShape* shape, PxTransform& transform, PxFilterData filter,
	Vector4& color) : gPhysics_(gPhysics),
	transform_(transform)
{
	obj_ = gPhysics_->createRigidStatic(transform_);
	if (shape == nullptr)
		shape = CreateShape(PxBoxGeometry(100, 30, 100));

	shape->setSimulationFilterData(filter);
	obj_->attachShape(*shape);
	gScene->addActor(*obj_);

	rItem_ = new RenderItem(shape, obj_, color);
}

SolidStatic::~SolidStatic()
{
	if(rItem_ != nullptr)
		DeregisterRenderItem(rItem_);
	rItem_ = nullptr;
}

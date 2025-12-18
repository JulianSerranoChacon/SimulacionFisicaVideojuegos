#include "SolidDynamic.h"

SolidDynamic::SolidDynamic(PxScene* gScene, PxPhysics* gPhysics, PxShape* shape, PxTransform& transform, double density,
	double staticFriction, double dynamicFriction, double restitution, Vector4& color) :
	gPhysics(gPhysics), transform(transform), maxTimeLife(-1)
{
	createObj(gScene, shape, transform, density, staticFriction, dynamicFriction, restitution, color);
}

SolidDynamic::SolidDynamic(PxScene* gScene, PxPhysics* gPhysics, PxShape* shape, PxTransform& transform, double density,
	double staticFriction, double dynamicFriction, double restitution, PxFilterData filterdata, Vector4& color):
	gPhysics(gPhysics), transform(transform), maxTimeLife(-1)
{
	shape->setSimulationFilterData(filterdata);
	createObj(gScene, shape, transform, density, staticFriction, dynamicFriction, restitution, color);
}

SolidDynamic::SolidDynamic(PxScene* gScene, PxPhysics* gPhysics, PxShape* shape, PxTransform& transform, double density,
	double staticFriction, double dynamicFriction, double restitution, float maxtimeLife, Vector4& color):
	gPhysics(gPhysics), transform(transform), maxTimeLife(maxtimeLife), timeLife(0)
{
	createObj(gScene, shape, transform, density,staticFriction,dynamicFriction,restitution, color);
}

SolidDynamic::~SolidDynamic()
{

	if (rItem != nullptr)
		DeregisterRenderItem(rItem);
	rItem = nullptr;
}

bool SolidDynamic::updateTimeLife(double t) {

	timeLife += t;
	return maxTimeLife > 0 && timeLife < maxTimeLife;
}

void SolidDynamic::createObj(PxScene* gScene, PxShape* shape, PxTransform& transform, double density,
	double staticFriction, double dynamicFriction, double restitution, Vector4& color)
{

	PxMaterial* material = gPhysics->createMaterial(staticFriction, dynamicFriction, restitution);
	obj = gPhysics->createRigidDynamic(transform);
	obj->setLinearVelocity(Vector3(0, 5, 0));
	obj->setAngularVelocity(Vector3(0, 0, 0));
	if (shape == nullptr)
		shape = CreateShape(PxBoxGeometry(100, 30, 100), material);

	shape->setMaterials(&material, 1);
	obj->attachShape(*shape);
	gScene->addActor(*obj);

	PxRigidBodyExt::updateMassAndInertia(*obj, density);
	rItem = new RenderItem(shape, obj, color);
}

void SolidDynamic::integrate(double t) {
	for (ForceGenerator* fg : fG) {
		if (fg != nullptr) {
			obj->addForce(fg->addForce(this).toVector3(), PxForceMode::eIMPULSE, true);
		}
	}

	transform = obj->getGlobalPose();
}
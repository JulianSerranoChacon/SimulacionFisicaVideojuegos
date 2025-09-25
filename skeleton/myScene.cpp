#include "MyScene.h"
#include "Vector3D.h"

using namespace physx;

myScene::myScene()
{
	createAxis();
	PxShape* s = CreateShape(PxSphereGeometry(5));
	PxTransform* str = new PxTransform(Vector3(0, 0, 0));
	Vector4 sv = Vector4(1, 1, 1, 1);
	RenderItem* sphere = new RenderItem(s, str, sv);
	mItems.push_back(sphere);
}

myScene::~myScene()
{
	for (int i = 0; i < mItems.size(); i++) {
		if (mItems[i] != nullptr)
			mItems[i]->release();
	}
}

void myScene::createAxis()
{
	Vector3D<float> vR(20, 0, 0);
	PxShape* sR = CreateShape(PxSphereGeometry(5));
	PxTransform* strR = new PxTransform(vR.toVector3());
	Vector4 svR = Vector4(1, 0, 0, 1);
	RenderItem* sphereR = new RenderItem(sR, strR, svR);
	mItems.push_back(sphereR);

	Vector3D<float> vG(0, 20, 0);
	PxShape* sG = CreateShape(PxSphereGeometry(5));
	PxTransform* strG = new PxTransform(vG.toVector3());
	Vector4 svG = Vector4(0, 1, 0, 1);
	RenderItem* sphereG = new RenderItem(sG, strG, svG);
	mItems.push_back(sphereG);

	Vector3D<float> vB(0, 0, 20);
	PxShape* sB = CreateShape(PxSphereGeometry(5));
	PxTransform* strB = new PxTransform(vB.toVector3());
	Vector4 svB = Vector4(0, 0, 1, 1);
	RenderItem* sphereB = new RenderItem(sB, strB, svB);
	mItems.push_back(sphereB);
}

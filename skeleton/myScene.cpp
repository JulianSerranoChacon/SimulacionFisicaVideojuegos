#include "MyScene.h"
#include "Vector3D.h"
#include "Particle.h"

using namespace physx;

myScene::myScene()
{
	createAxis();
	chooseScene(1);
}

myScene::~myScene()
{
	for (int i = 0; i < mParticles.size(); i++)
	{
		if (mParticles[i] != nullptr)
			delete mParticles[i];
	}
	for (int i = 0; i < mItems.size(); i++) {
		if (mItems[i] != nullptr)
			mItems[i]->release();
	}

}

void myScene::update(float t)
{
	for (int i = 0; i < mParticles.size(); i++)
		if (mParticles[i] != nullptr)
			mParticles[i]->integrate(t);
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

void myScene::chooseScene(int id)
{
	switch (id)
	{
	case 0:
		scene0();
		break;
	case 1:
		scene1();
		break;
	default:
		break;
	}
}

void myScene::scene0()
{
	PxShape* s = CreateShape(PxSphereGeometry(5));
	PxTransform* str = new PxTransform(Vector3(0, 0, 0));
	Vector4 sv = Vector4(1, 1, 1, 1);
	RenderItem* sphere = new RenderItem(s, str, sv);
	mItems.push_back(sphere);
}

void myScene::scene1()
{
	mParticles.push_back(new Particle(Vector3D<float>(0, 0, 0), Vector3D<float>(2, 0, 0), Vector3D<float>(0, 5, 5), 0.2));
}

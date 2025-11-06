#include "MyScene.h"
#include "Vector3D.h"
#include "Particle.h"
#include "Proyectil.h"
#include "ParticleSystem.h"
#include "NormalGenerator.h"
#include "uniformGenerator.h"

using namespace physx;

myScene::myScene()
{
	createAxis();
	chooseScene(3);
}

myScene::~myScene()
{
	for (int i = 0; i < mParticles.size(); i++)
	{
		if (mParticles[i] != nullptr) {
			delete mParticles[i];
			mParticles[i] = nullptr;
		}
	}
	for (int i = 0; i < mItems.size(); i++) {
		if (mItems[i] != nullptr) {
			DeregisterRenderItem(mItems[i]);
			mItems[i] = nullptr;
		}
	}

}

void myScene::update(float t)
{
	for (int i = 0; i < mParticles.size(); i++)
		if (mParticles[i] != nullptr)
			mParticles[i]->integrate(t);

	for (ParticleSystem* pS : mPSystems)
		pS->update(t);
}

void myScene::Shoot(physx::PxVec3 camPos, physx::PxVec3 camDir)
{
	mParticles.push_back(new Proyectil(Vector3D<float>(camPos.x ,camPos.y,camPos.z), Vector3D<float>(0, 0, 250),
		Vector3D<float>(0, 0, 0), 0.2, 20, 9.8, 
		Vector3D<float>(0, 0, 100) * Vector3D<float>(camDir.x / camDir.x, camDir.y / camDir.y, camDir.z / camDir.z)));
}

void myScene::createAxis()
{
	Vector3D<float> vR(20, 0, 0);
	PxTransform* strR = new PxTransform(vR.toVector3());
	Vector4 svR = Vector4(1, 0, 0, 1);
	RenderItem* sphereR = new RenderItem(CreateShape(PxSphereGeometry(5)), strR, svR);
	mItems.push_back(sphereR);

	Vector3D<float> vG(0, 20, 0);
	PxTransform* strG = new PxTransform(vG.toVector3());
	Vector4 svG = Vector4(0, 1, 0, 1);
	RenderItem* sphereG = new RenderItem(CreateShape(PxSphereGeometry(5)), strG, svG);
	mItems.push_back(sphereG);

	Vector3D<float> vB(0, 0, 20);
	PxTransform* strB = new PxTransform(vB.toVector3());
	Vector4 svB = Vector4(0, 0, 1, 1);
	RenderItem* sphereB = new RenderItem(CreateShape(PxSphereGeometry(5)), strB, svB);
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
	case 2:
		scene2();
		break;
	case 3:
		scene3();
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

void myScene::scene2()
{
	mParticles.push_back(new Proyectil(Vector3D<float>(-30, -30, 0), Vector3D<float>(250, 250, 0), Vector3D<float>(0, 0, 0), 0.2, 2, 9.8, Vector3D<float>(100,100, 0)));
}

void myScene::scene3()
{
	ParticleSystem* myPS = new ParticleSystem();
	mPSystems.push_back(myPS);

	//fuego
	ParticleGenerator* pG = new NormalGenerator(50, 0.1, mVector3D(0, 0, 0), mVector3D(0, 10, 0), mVector3D(20, 20, 20), mVector3D(3, 3, 3), MVector3(0, 10, 0), MVector3(0, 0, 0), 0,
		2, 60, true, 0.5, 0.5,Vector4(1,0,0,1));
	myPS->addParticleGen(pG);

	//lluvia
	pG = new uniformGenerator(50,0.3,mVector3D(0,30,0),MVector3(0,0,0),mVector3D(10,0,10),MVector3(0,-10,0), MVector3(0, -10,0), MVector3(0, 12, 0),
		MVector3(0, 0, 0), MVector3(0, 0, 0), MVector3(0, 0, 0),4,5,10,true,Vector4(0,0,1,1));
	myPS->addParticleGen(pG);


	//humo
	pG = new uniformGenerator(150, 0.1, mVector3D(0, 30, 0), MVector3(0, 0, 0), mVector3D(0, 0, 0), MVector3(0,0,0), MVector3(-7, -7, -7), MVector3(7, 7,7),
		MVector3(0, 10, 0), MVector3(-5, -5, -5), MVector3(5, 5, 5), 1, 2, 14, true, Vector4(0.5, 0.5, 0.5, 1));
	myPS->addParticleGen(pG);
}

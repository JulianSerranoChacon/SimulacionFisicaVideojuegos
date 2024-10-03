#include "MyScene.h"

#include "Vector3D.h"

//#include <iostream> // para debug

using namespace physx;

MyScene::MyScene()
{
	createAxis();

	PxShape* s = CreateShape(PxSphereGeometry(5));
	PxTransform* str = new PxTransform(Vector3(0, 0, 0));
	Vector4 sv = Vector4(1, 1, 1, 1);
	RenderItem* sphere = new RenderItem(s, str, sv);
	mItems.push_back(sphere);

	//para debuggear
	//Vector3D<float> v(1,2,1);
	//Vector3D<float> v1(1,1,2);
	//Vector3D<float> v2;
	////v1 = v;
	//v2 = v1 + v;
	//std::cout << v2.getY() << v1.getY() << v.getY() << std::endl;
	//v1 += v;
	//std::cout << v2.getY() << v1.getY() << v.getY() << std::endl;
	//v = v1 * v2;
	//std::cout << v.getX() << v.getY() << v.getZ() << std::endl;
	/////Vector3D<int> v(1, 1, 1);
}

MyScene::~MyScene()
{
	/*for (int i = 0; i < mItems.size(); i++) {
		if (mItems[i] != nullptr)
			mItems[i]->release();
	}*/
}

void MyScene::createAxis()
{
	Vector3D<float> vR(20, 0, 0);
	PxShape* sR = CreateShape(PxSphereGeometry(5));
	PxTransform* strR = new PxTransform(vR.getX(), vR.getY(), vR.getZ());
	Vector4 svR = Vector4(1, 0, 0, 1);
	RenderItem* sphereR = new RenderItem(sR, strR, svR);
	mItems.push_back(sphereR);

	Vector3D<float> vG(0, 20, 0);
	PxShape* sG = CreateShape(PxSphereGeometry(5));
	PxTransform* strG = new PxTransform(vG.getX(), vG.getY(), vG.getZ());
	Vector4 svG = Vector4(0, 1, 0, 1);
	RenderItem* sphereG = new RenderItem(sG, strG, svG);
	mItems.push_back(sphereG);

	Vector3D<float> vB(0, 0, 20);
	PxShape* sB = CreateShape(PxSphereGeometry(5));
	PxTransform* strB = new PxTransform(vB.getX(), vB.getY(), vB.getZ());
	Vector4 svB = Vector4(0, 0, 1, 1);
	RenderItem* sphereB = new RenderItem(sB, strB, svB);
	mItems.push_back(sphereB);
}

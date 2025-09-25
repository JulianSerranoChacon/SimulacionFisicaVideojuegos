#include "MyScene.h"

using namespace physx;

myScene::myScene()
{
	PxShape* s = CreateShape(PxSphereGeometry(20));
	PxTransform* str = new PxTransform(Vector3(0, 0, 0));
	Vector4 sv = Vector4(1, 1, 1, 1);
	RenderItem* sphere = new RenderItem(s, str, sv);
	mItems.push_back(sphere);
}

myScene::~myScene()
{
	/*for (int i = 0; i < mItems.size(); i++) {
		if (mItems[i] != nullptr)
			mItems[i]->release();
	}*/
}
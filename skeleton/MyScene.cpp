#include "MyScene.h"

#include "Vector3D.h"

#include <iostream> // para debug

using namespace physx;

MyScene::MyScene()
{
	PxShape* s = CreateShape(PxSphereGeometry(20));
	PxTransform* str = new PxTransform(Vector3(0, 0, 0));
	Vector4 sv = Vector4(1, 1, 1, 1);
	RenderItem* sphere = new RenderItem(s, str, sv);
	mItems.push_back(sphere);

	//voy a debuggear
	Vector3D<float> v(1,2,1);
	std::cout << v.scalar(Vector3D<float>(1,2,3)).getZ();
	///Vector3D<int> v(1, 1, 1);

}

MyScene::~MyScene()
{
	/*for (int i = 0; i < mItems.size(); i++) {
		if (mItems[i] != nullptr)
			mItems[i]->release();
	}*/
}

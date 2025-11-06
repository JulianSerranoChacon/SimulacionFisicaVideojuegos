#include "MyScene.h"
#include "Vector3D.h"
#include "Particle.h"
#include "Proyectil.h"
#include "ParticleSystem.h"
#include "NormalGenerator.h"
#include "uniformGenerator.h"
#include "NormalGeneratorWithForces.h"
#include "uniformGeneratorWithForces.h"
#include "gravityForceGenerator.h"
#include "WindForceGenerator.h"
#include "VortexForceGenerator.h"

using namespace physx;

myScene::myScene()
{
	createAxis();
	chooseScene(4);
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
	case 4:
		scene4();
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
	ParticleGenerator* pG = new NormalGenerator(
		100, 0.03,                      // numero particulas, velocidad de emision
		mVector3D(0, 0, 0),             // Posicion
		mVector3D(1, 0.5, 1),           // Offset de la posicion
		mVector3D(0, 8, 0),             // velocidad
		mVector3D(2, 3, 2),             // Offset de la velocidad
		MVector3(0, 2, 0),              // aceleracion
		MVector3(0, 1, 0),              // Offset de la aceleracion
		1, 3, 60,                       // vida minia, maxima y distancia
		true,							// Active
		0.0, 0.4,                       // media y desviacion
		Vector4(1, 0.5, 0, 1)           // color
	);
	myPS->addParticleGen(pG);

	// Generador de lluvia
	pG = new uniformGenerator(
		100,                  // Ma ximo de particulas
		0.07,                 // Tiempo entre emisiones
		mVector3D(0, 30, 0),    // Posicion del generador (altura)
		MVector3(0, 0, 0),      // Offset minimo de posicion
		mVector3D(60, 0, 60),   // Offset maximo de posicion (ancho y profundidad del cuadrado)
		MVector3(0, -25, 0),    // Velocidad
		MVector3(0, -2, 0),     // Offset minimo de la velocidad 
		MVector3(0, 0, 0),      // Offset maximo de la velocidad a
		MVector3(0, 0, 0),      // Aceleracion
		MVector3(0, 0, 0),      // Offset minimo de la aceleracion
		MVector3(0, 0, 0),      // Offset maximo de la maxima
		1,                  // Tiempo de vida minimo
		2,                  // Tiempo de vida maximo
		50.0,                 // Distancia maxima
		true,                 // Activo
		Vector4(0.6, 0.7, 1.0, 1) // Color azul
	);
	myPS->addParticleGen(pG);



	//humo
	// Generador de humo
	pG = new uniformGenerator(
		200,                     // Maximo de particulas
		0.05,                    // Tiempo entre emisiones
		mVector3D(30, 30, 30),   // Posicion
		mVector3D(-5, -5, -5),   // Offset minimo de posicion (cubo alrededor del centro)
		mVector3D(5, 5, 5),      // Offset maximo de posicion
		mVector3D(0, 0, 0),      // Velocidad 
		mVector3D(-1, -1, -1),   // Offset minimo de velocidad (hacia todas direcciones)
		mVector3D(1, 1, 1),      // Offset maximo de velocidad
		mVector3D(0, -10, 0),      // Aceleracion
		mVector3D(0, 0, 0),      // Offset minimo de aceleracion
		mVector3D(0, 0, 0),      // Offset maximo de aceleracion
		2,                        // Tiempo de vida minimo
		4,                        // Tiempo de vida maximo
		10,                       // Distancia maxima
		true,                     // Activo
		Vector4(0.5, 0.5, 0.5, 1) // Color gris
	);
	myPS->addParticleGen(pG);
}

void myScene::scene4()
{
	ParticleSystem* myPS = new ParticleSystem();
	mPSystems.push_back(myPS);

	gravityForceGenerator* gG = new gravityForceGenerator(mVector3D(0, -9.8, 0));
	WindForceGenerator* wG = new WindForceGenerator(mVector3D(5,5,0 ), 0.8f);
	VortexForceGenerator* vG = new VortexForceGenerator(mVector3D(30, 30, 30), 0.0002f);

	//fuego
	NormalGeneratorWithForces* pG = new NormalGeneratorWithForces(
		100, 0.03,                      // numero particulas, velocidad de emision
		mVector3D(0, 0, 0),             // Posicion
		mVector3D(1, 0.5, 1),           // Offset de la posicion
		mVector3D(0, 8, 0),             // velocidad
		mVector3D(2, 3, 2),             // Offset de la velocidad
		MVector3(0, 2, 0),              // aceleracion
		MVector3(0, 1, 0),              // Offset de la aceleracion
		1, 3, 60,                       // vida minia, maxima y distancia
		true,							// Active
		0.0, 0.4,                       // media y desviacion
		50,								//masa
		Vector4(1, 0.5, 0, 1)           // color
	);
	//pG->addForceGenerator(gG);
	//pG->addForceGenerator(wG);
	pG->addForceGenerator(vG);
	myPS->addParticleGen(pG);

	// Generador de lluvia
	uniformGeneratorWithForces* pG2 = new uniformGeneratorWithForces(
		100,                  // Ma ximo de particulas
		0.07,                 // Tiempo entre emisiones
		mVector3D(0, 30, 0),    // Posicion del generador (altura)
		MVector3(0, 0, 0),      // Offset minimo de posicion
		mVector3D(60, 0, 60),   // Offset maximo de posicion (ancho y profundidad del cuadrado)
		MVector3(0, -25, 0),    // Velocidad
		MVector3(0, -2, 0),     // Offset minimo de la velocidad 
		MVector3(0, 0, 0),      // Offset maximo de la velocidad a
		MVector3(0, 0, 0),      // Aceleracion
		MVector3(0, 0, 0),      // Offset minimo de la aceleracion
		MVector3(0, 0, 0),      // Offset maximo de la maxima
		1,                  // Tiempo de vida minimo
		2,                  // Tiempo de vida maximo
		50.0,                 // Distancia maxima
		true,                 // Activo
		50,						//masa
		Vector4(0.6, 0.7, 1.0, 1) // Color azul
	);
	pG2->addForceGenerator(gG);
	myPS->addParticleGen(pG2);

	//humo
	// Generador de humo
	pG2 = new uniformGeneratorWithForces(
		200,                     // Maximo de particulas
		0.05,                    // Tiempo entre emisiones
		mVector3D(30, 30, 30),   // Posicion
		mVector3D(-5, -5, -5),   // Offset minimo de posicion (cubo alrededor del centro)
		mVector3D(5, 5, 5),      // Offset maximo de posicion
		mVector3D(0, 0, 0),      // Velocidad 
		mVector3D(-1, -1, -1),   // Offset minimo de velocidad (hacia todas direcciones)
		mVector3D(1, 1, 1),      // Offset maximo de velocidad
		mVector3D(0, -10, 0),      // Aceleracion
		mVector3D(0, 0, 0),      // Offset minimo de aceleracion
		mVector3D(0, 0, 0),      // Offset maximo de aceleracion
		2,                        // Tiempo de vida minimo
		4,                        // Tiempo de vida maximo
		10,                       // Distancia maxima
		true,                     // Activo
		50,							//masa
		Vector4(0.5, 0.5, 0.5, 1) // Color gris
	);
	pG2->addForceGenerator(vG);
	myPS->addParticleGen(pG2);
}

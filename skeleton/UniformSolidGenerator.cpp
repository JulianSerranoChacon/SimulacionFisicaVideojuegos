#include "UniformSolidGenerator.h"

UniformSolidGenerator::UniformSolidGenerator(PxScene* gScene, PxPhysics* gPhysics, int maxParticles, double emisionVel, Vector3 genPos,
	Vector3 genPosOffsetMin, Vector3 genPosOffsetMax, Vector3 genVel, Vector3 genVelOffsetMin, Vector3 genVelOffsetMax,
	Vector3 genAngVel, Vector3 genAngVelOffsetMin, Vector3 genAngVelOffsetMax, double staticFrictionMin, double dynamicFrictionMin,
	double restitutionMin, double staticFrictionMax, double dynamicFrictionMax, double restitutionMax, double timeLifeMin, double timeLifeMax,
	double maxDistance, bool active, float density, PxShape* shape, Vector4 sV) :
	SolidGenerator(gScene, gPhysics, maxParticles, emisionVel, genPos, genPosOffsetMax,
		genVel, genAngVelOffsetMax, genAngVel, genAngVelOffsetMax, staticFrictionMin, dynamicFrictionMin, restitutionMin,
		staticFrictionMax, dynamicFrictionMax, restitutionMax, timeLifeMin,
		timeLifeMax, maxDistance, active,density, shape, sV), genPosOffsetMin(genPosOffsetMin),
	genVelOffsetMin(genVelOffsetMin), genAngVelOffsetMin(genAngVelOffsetMin)
{
	std::random_device randomDevice;
	random = std::mt19937(randomDevice());
}

UniformSolidGenerator::~UniformSolidGenerator()
{
}

void UniformSolidGenerator::generate(double t)
{
	emisionVel -= t;
	if (emisionVel <= 0) {
		emisionVel = iniEmisionVel;
		std::uniform_real_distribution<float> uniformXPos(genPosOffsetMin.x, genPosOffset.x);
		std::uniform_real_distribution<float> uniformYPos(genPosOffsetMin.y, genPosOffset.y);
		std::uniform_real_distribution<float> uniformZPos(genPosOffsetMin.z, genPosOffset.z);

		float auxX = uniformXPos(random);
		float auxY = uniformYPos(random);
		float auxZ = uniformZPos(random);
		Vector3 posVar(auxX, auxY, auxZ);

		std::uniform_real_distribution<float> uniformXVel(genVelOffsetMin.x, genVelOffset.x);
		std::uniform_real_distribution<float> uniformYVel(genVelOffsetMin.y, genVelOffset.y);
		std::uniform_real_distribution<float> uniformZVel(genVelOffsetMin.z, genVelOffset.z);
		auxX = uniformXVel(random);
		auxY = uniformYVel(random);
		auxZ = uniformZVel(random);
		Vector3 velVar(auxX, auxY, auxZ);

		std::uniform_real_distribution<float> uniformXnAngVel(genAngVelOffsetMin.x, genAngVelOffset.x);
		std::uniform_real_distribution<float> uniformYnAngVel(genAngVelOffsetMin.y, genAngVelOffset.y);
		std::uniform_real_distribution<float> uniformZAngVel(genAngVelOffsetMin.z, genAngVelOffset.z);
		auxX = uniformXnAngVel(random);
		auxY = uniformYnAngVel(random);
		auxZ = uniformZAngVel(random);
		Vector3 nAngVelVar(auxX, auxY, auxZ);

		std::uniform_real_distribution<double> time(timeLifeMin, timeLifeMax);
		double timeVar = time(random);

		std::uniform_real_distribution<double> staticFR(staticFrictionMin, staticFrictionMax);
		double staticFVar = staticFR(random);


		std::uniform_real_distribution<double> dynamicFR(dynamicFrictionMin, dynamicFrictionMax);
		double dynamicFVar = dynamicFR(random);

		std::uniform_real_distribution<double> restitutionR(restitutionMin, restitutionMax);
		double restitutionVar = restitutionR(random);

		//ParticleWithMass* p = new ParticleWithMass(genPos + posVar, genVel + velVar, genAccel + accelVar, 0.5, mass, time(random), 0.5, sV);
		SolidDynamic* s = new SolidDynamic(gScene,gPhysics, CreateShape(shape->getGeometry().any()), PxTransform(genPos + posVar), density,
			staticFVar, dynamicFVar, restitutionVar,timeVar, sV);
		s->getObject()->setLinearVelocity(genVel + velVar);
		s->getObject()->setAngularVelocity(genAngVel + nAngVelVar);
		

		for(ForceGenerator* f : fG)
			s->addForceGenerator(f);

		listS.push_front(s);
		nParticles++;
	}
}

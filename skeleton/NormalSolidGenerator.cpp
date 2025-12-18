#include "NormalSolidGenerator.h"
#include "SolidDynamic.h"


NormalSolidGenerator::NormalSolidGenerator(double media, double desviacion,PxScene* gScene, PxPhysics* gPhysics, int maxParticles, double emisionVel, Vector3 genPos,
	Vector3 genPosOffset,Vector3 genVel, Vector3 genVelOffset, Vector3 genAngVel, Vector3 genAngVelOffset, double staticFrictionMin,
	double dynamicFrictionMin,double restitutionMin, double staticFrictionMax, double dynamicFrictionMax, double restitutionMax,
	double timeLifeMin,double timeLifeMax, double maxDistance, bool active, float density,PxShape* shape, Vector4 sV):
	SolidGenerator(gScene,gPhysics,maxParticles,emisionVel,genPos,genPosOffset,genVel,genVelOffset,genAngVel,genAngVelOffset,
		staticFrictionMin,dynamicFrictionMin,restitutionMin, staticFrictionMax, dynamicFrictionMax, restitutionMax,timeLifeMin,
		timeLifeMax,maxDistance,active,density,shape,sV), media(media), desviacion(desviacion)

{
	std::random_device randomDevice;
	random = std::mt19937(randomDevice());
}

NormalSolidGenerator::~NormalSolidGenerator()
{
}

void NormalSolidGenerator::generate(double t) {

	emisionVel -= t;
	if (emisionVel <= 0) {
		emisionVel = iniEmisionVel;


		Vector3 posVar(0);
		Vector3 velVar(0);
		Vector3 nAngVelVar(0);

		if (desviacion > 0) {
			std::normal_distribution<float> normal(media, desviacion);

			posVar = Vector3(
				genPosOffset.x * normal(random),
				genPosOffset.y * normal(random),
				genPosOffset.z * normal(random)
			);

			velVar = Vector3(
				genVelOffset.x * normal(random),
				genVelOffset.y * normal(random),
				genVelOffset.z * normal(random)
			);

			nAngVelVar = Vector3(
				genAngVelOffset.x * normal(random),
				genAngVelOffset.y * normal(random),
				genAngVelOffset.z * normal(random)
			);
		}
		

		std::uniform_real_distribution<double> time(timeLifeMin, timeLifeMax);
		double timeVar = time(random);

		std::uniform_real_distribution<double> staticFR(staticFrictionMin, staticFrictionMax);
		double staticFVar = staticFR(random);


		std::uniform_real_distribution<double> dynamicFR(dynamicFrictionMin, dynamicFrictionMax);
		double dynamicFVar = dynamicFR(random);

		std::uniform_real_distribution<double> restitutionR(restitutionMin, restitutionMax);

		
		double restitutionVar = restitutionR(random);
		SolidDynamic* s = new SolidDynamic(gScene, gPhysics, shape, PxTransform(genPos + posVar), density, staticFVar, dynamicFVar,
			restitutionVar,timeVar, sV);

		s->getObject()->setLinearVelocity(genVel + velVar);
		s->getObject()->setAngularVelocity(genAngVel + nAngVelVar);

		for (ForceGenerator* f : fG)
			s->addForceGenerator(f);

		listS.push_front(s);
		nParticles++;
	}
}

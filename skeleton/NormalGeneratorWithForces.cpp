#include "NormalGeneratorWithForces.h"
#include "ParticleWithMass.h"

NormalGeneratorWithForces::NormalGeneratorWithForces(int maxParticles, double emisionVel, mVector3D genPos, mVector3D genPosOffset, mVector3D genVel,
	mVector3D genVelOffset, mVector3D genAccel, mVector3D genAccelOffset, double timeLifeMin, double timeLifeMax, double maxDistance,
	bool active, double media, double desviacion,float mass, Vector4 sV):
	NormalGenerator(maxParticles,emisionVel,genPos,genPosOffset,genVel,genVelOffset,genAccel,genAccelOffset,timeLifeMin,timeLifeMax,maxDistance,
		active,media,desviacion,sV), mass(mass)
{
}

void NormalGeneratorWithForces::generate(double t)
{
	emisionVel -= t;
	if (emisionVel <= 0) {
		emisionVel = iniEmisionVel;
		std::normal_distribution<float> normal(media, desviacion);

		float auxX = normal(random);
		float auxY = normal(random);
		float auxZ = normal(random);
		mVector3D vAux(auxX, auxY, auxZ);
		mVector3D posVar(genPosOffset.scalar(vAux));

		auxX = normal(random);
		auxY = normal(random);
		auxZ = normal(random);
		vAux = mVector3D(auxX, auxY, auxZ);
		mVector3D velVar(genVelOffset.scalar(vAux));

		auxX = normal(random);
		auxY = normal(random);
		auxZ = normal(random);
		vAux = mVector3D(auxX, auxY, auxZ);
		mVector3D accelVar(genAccelOffset.scalar(vAux));

		int tm = timeLifeMax;
		ParticleWithMass* p = new ParticleWithMass(genPos + posVar, genVel + velVar, genAccel + accelVar, 0.5, mass, (double)(timeLifeMin + rand() % tm),0.5, sV);
		for (ForceGenerator* f : fG)
			p->addForceGenerator(f);
		listP.push_front(p);
		nParticles++;
	}
}

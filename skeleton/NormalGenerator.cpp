#include "NormalGenerator.h"
#include "ParticleGen.h"

NormalGenerator::NormalGenerator(int maxParticles, double emisionVel, mVector3D genPos, mVector3D genPosOffset, mVector3D genVel, mVector3D genVelOffset,
	mVector3D genAccel, mVector3D genAccelOffset, double timeLifeMin, double timeLifeMax, double maxDistance, bool active,double media, double desviacion):
	ParticleGenerator(maxParticles,emisionVel,genPos,genPosOffset,genVel,genVelOffset,genAccel,genAccelOffset,timeLifeMin,timeLifeMax,maxDistance,active), 
	media(media), desviacion(desviacion)
{
	std::random_device randomDevice;
	random = std::mt19937(randomDevice());
}

void NormalGenerator::generate(double t)
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
		listP.push_front(new ParticleGen(genPos+posVar,genVel+velVar,genAccel+accelVar,0.5,(double)(timeLifeMin + rand()%tm)));
		nParticles++;
	}
}

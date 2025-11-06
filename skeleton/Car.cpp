#include "Car.h"
#include "Proyectil.h"

Car::Car(MVector3 pos, MVector3 moveDir, double speed, float dumping, float mass, float timeLife, float sizeX,float sizeY,float sizeZ, Vector4 sV):
	ParticleWithMass(pos, MVector3(0,0,0), MVector3(0, 0, 0), dumping, mass, timeLife,size, CreateShape(physx::PxBoxGeometry(sizeX, sizeY, sizeZ)), sv), moveDir(0,0,0), speed(speed)
{
}

Proyectil* Car::shoot()
{
    return new Proyectil(Vector3D<float>(pose_.p.x, pose_.p.y, pose_.p.z), Vector3D<float>(0, 0, 250),
        Vector3D<float>(0, 0, 0), 0.2, 20, 9.8,
        Vector3D<float>(100, 100, 100) * vel_.normalize() + Vector3D<float>(0, 50,0));
}

void Car::integrate(double t)
{
	vel_ = moveDir.scalar(speed);
	ParticleWithMass::integrate(t);
	if (pS != nullptr)
		pS->moveTo(pose_.p);

}


void Car::move(Vector3 dir)
{
      // Dirección deseada (normalizada)
      mVector3D desiredDir(dir.x, dir.y, dir.z);
     desiredDir.normalize();

     // Velocidad deseada
     mVector3D desiredVel = desiredDir.scalar(speed);

     // Interpolamos suavemente la velocidad actual hacia la deseada
     // (ajusta el factor 0.1f para más o menos suavidad)
    // Interpolación (ajusta el factor 0.1f para más/menos suavidad)
    vel_ = vel_.scalar(0.9f) + desiredVel.scalar(0.4f);

    // Actualiza la dirección del movimiento
    moveDir = desiredDir;
}

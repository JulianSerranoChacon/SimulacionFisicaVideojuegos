#include "Car.h"
#include "Proyectil.h"
#include <cmath>

Car::Car(PxScene* gScene, PxPhysics* gPhysics, PxShape* shape, PxTransform& transform, double density,
    double staticFriction, double dynamicFriction, double restitution, double speed, double maxSpeed, double damping,
    double jumpForce, double highHeight, Vector4& color):
    SolidDynamic(gScene, gPhysics, shape, transform, density, staticFriction, dynamicFriction, restitution, -1, color),
    speed(speed), maxSpeed(maxSpeed), moveDir(0), damping(damping), jumpForce(jumpForce), highHeight(highHeight)
{

    obj->setLinearDamping(damping);
    obj->setAngularDamping(damping);
    obj->setRigidDynamicLockFlags(PxRigidDynamicLockFlag::eLOCK_ANGULAR_X | PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z);

    PxTransform cm = obj->getCMassLocalPose();
    cm.p.y *= 0.5f;
    obj->setCMassLocalPose(cm);
}

Car::~Car()
{
}

Proyectil* Car::shoot()
{
    return new Proyectil(Vector3D<float>(transform.p.x, transform.p.y, transform.p.z), Vector3D<float>(0, 0, 250),
        Vector3D<float>(0, 0, 0), 0.2, 20, 9.8,
        Vector3D<float>(100, 100, 100) * obj->getLinearVelocity().normalize() + Vector3D<float>(0, 50, 0));
}

void Car::integrate(double t)
{
    // Aplicar fuerzas externas (gravedad, etc.)
    for (auto fg : fG)
        fg->addForce(this);

    // Aplicamos movimiento suave basado en inputs acumulados
    applyMove(moveDir, t);

    // Si quieres frenar lentamente al soltar teclas:
    moveDir *= damping;

    transform = obj->getGlobalPose();
}

void Car::applyMove(Vector3& dir, double t)
{
    if (!obj)
        return;

    Vector3 actVel = obj->getLinearVelocity();

    if(abs(actVel.magnitude()) > maxSpeed)
        return;

    Vector3 desVel = moveDir * speed;
    if (abs(desVel.magnitude()) > maxSpeed){
        desVel.normalize();
        desVel *= maxSpeed;
    }

    obj->addForce(desVel * 10000);
}



void Car::move(const Vector3& direction)
{
    moveDir += direction;
}

void Car::jump()
{
    if(transform.p.y < highHeight)
        obj->addForce(Vector3(0,jumpForce,0) * 10000);
}

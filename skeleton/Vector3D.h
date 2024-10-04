#pragma once
#include <type_traits>
#include <PxPhysicsAPI.h>
#include <math.h>

template <typename T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
class Vector3D
{
public:
	Vector3D(): x_(0),y_(0),z_(0) {}
	Vector3D(T x, T y, T z) : x_(x), y_(y), z_(z) {};
	~Vector3D() {}

	T getX() const { return x_; }
	T getY() const { return y_; }
	T getZ() const { return z_; }

	T Module() const {
		return sqrt(pow(x_,2) + pow(y_, 2) + pow(z_, 2));
	}

	Vector3D normalize() const {
		return Vector3D(x_ /Module() ,y_ / Module() ,z_ / Module());
	}

	Vector3D scalar  (const Vector3D v) const {
		return Vector3D(x_ * v.getX(), y_ * v.getY(), z_ * v.getZ());
	}

	Vector3D scalar(T k) const {
		return Vector3D(x_ * k, y_ * k, z_ * k); 
	}

	Vector3D& operator = (const Vector3D& v){
		x_ = v.x_;
		y_ = v.y_;
		z_ = v.z_;
		return *this;
	}

	Vector3D& operator += (const Vector3D& v) {
		x_ += v.x_;
		y_ += v.y_;
		z_ += v.z_;
		return *this;
	}

	friend Vector3D& operator + (const Vector3D& v1, const Vector3D& v2) {
		return *(new Vector3D(v1.x_ + v2.x_, v1.y_ + v2.y_, v1.z_ + v2.z_));
	}


	friend Vector3D& operator - (const Vector3D& v1, const Vector3D& v2) {
		return *(new Vector3D(v1.x_ - v2.x_, v1.y_ - v2.y_, v1.z_ - v2.z_));
	}

	friend Vector3D& operator * (const Vector3D& v1, const Vector3D& v2) {
		return *(new Vector3D(v1.y_ * v2.z_ - v1.z_ * v2.y_, v1.z_ * v2.x_ - v1.x_ * v2.z_, v1.x_ * v2.y_ - v1.y_ * v2.x_));
	}

	physx::PxVec3 toVector3() {
		return physx::PxVec3(x_, y_, z_);
	}

protected:
	T x_;
	T y_;
	T z_;
};


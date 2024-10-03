#pragma once
#include <type_traits>
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

protected:
	T x_;
	T y_;
	T z_;
};


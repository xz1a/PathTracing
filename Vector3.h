#ifndef _VECTOR_3_H_
#define _VECTOR_3_H_
#include "Math.h"
#include <math.h>
#include <iostream>

class Vector3 {
public:
	Vector3();
	Vector3(double p_x, double p_y, double p_z);
	~Vector3();

	double x() const;
	double y() const;
	double z() const;

	Vector3 operator-() const;
	double operator[](int index) const;
	double& operator[](int index);
	Vector3& operator+=(const Vector3 &other);
	Vector3& operator*=(const double scalar);
	Vector3& operator*=(const Vector3 &other);
	Vector3& operator/=(const double scalar);
	double length_squared();
	double length();
	Vector3 normalize();
	bool IsZero();
	static Vector3 random();
	static Vector3 random(double min, double max);
	static Vector3 random_in_unit_sphere();
	static Vector3 random_unit_vector();
protected:
private:
	double data[3];
};

inline Vector3 operator+(const Vector3 &v1, const Vector3 &v2) {
	return Vector3(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
}

inline Vector3 operator-(const Vector3 &v1, const Vector3 &v2) {
	return Vector3(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]);
}

inline Vector3 operator*(const Vector3& v1, const Vector3& v2) {
	return Vector3(v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]);
}


inline Vector3 operator*(const double scalar, const Vector3 &v) {
	return Vector3(scalar * v[0], scalar * v[1], scalar * v[2]);
}

inline Vector3 operator*(const Vector3& v, const double scalar) {
	return scalar*v;
}

inline Vector3 operator/(const Vector3 &v, const double scalar) {
	return Vector3(v[0] / scalar, v[1] / scalar, v[2] / scalar);
}

inline double dot(const Vector3 &v1, const Vector3 &v2) {
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

inline Vector3 cross(const Vector3 &v1, const Vector3 &v2) {
	return Vector3(v1[1] * v2[2] - v1[2] * v2[1],
					v1[2] * v2[0] - v1[0] * v2[2],
					v1[0] * v2[1] - v1[1] * v2[0]);
}

inline Vector3 reflect(const Vector3 &v1, const Vector3 &v2) {
	return v1 - 2 * dot(v1, v2) * v2;
}

typedef Vector3 Vec3;
typedef Vector3 Color3;
typedef Vector3 Point;
#endif
#include "Vector3.h"

Vector3::Vector3() : data{ 0.0, 0.0, 0.0 } {

}

Vector3::Vector3(double p_x, double p_y, double p_z) : data{ p_x, p_y, p_z } {

}

Vector3::~Vector3() {

}

double Vector3::x() const {
	return data[0];
}

double Vector3::y() const {
	return data[1];
}

double Vector3::z() const {
	return data[2];
}

Vector3 Vector3::operator-() const {
	return Vector3(-data[0], -data[1], -data[2]);
}

double Vector3::operator[](int index) const {
	return data[index];
}

double& Vector3::operator[](int index) {
	return data[index];
}

Vector3& Vector3::operator+=(const Vector3& other) {
	data[0] += other[0];
	data[1] += other[1];
	data[2] += other[2];
	return *this;
}

Vector3& Vector3::operator*=(const double scalar) {
	data[0] *= scalar;
	data[1] *= scalar;
	data[2] *= scalar;
	return *this;
}

Vector3& Vector3::operator*=(const Vector3& other) {
	data[0] *= other[0];
	data[1] *= other[1];
	data[2] *= other[2];
	return *this;
}

Vector3& Vector3::operator/=(const double scalar) {
	return *this *= 1 / scalar;
}

double Vector3::length_squared() {
	return data[0] * data[0] + data[1] * data[1] + data[2] * data[2];
}

double Vector3::length() {
	return sqrt(length_squared());
}

Vector3 Vector3::normalize() {
	double magnitude = length();
	return *this/magnitude;
}

Vector3 Vector3::random() {
	return Vector3(random_double(), random_double(), random_double());
}

Vector3 Vector3::random(double min, double max) {
	return Vector3(random_double(min, max), random_double(min, max), random_double(min, max));
}

Vector3 Vector3::random_in_unit_sphere() {
	while (true) {
		Vector3 point = Vector3::random(-1.0, 1.0);
		if (point.length_squared() >= 1.0) {
			continue;
		}
		return point;
	}
}

Vector3 Vector3::random_unit_vector() {
	return random_in_unit_sphere().normalize();
}

bool Vector3::IsZero() {
	double zero = 1e-8;
	return (fabs(data[0]) < zero) && (fabs(data[1]) < zero) && (fabs(data[2]) < zero);
}
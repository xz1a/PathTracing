#include "Vector2.h"

Vector2::Vector2() : data{ 0.0, 0.0 } {

}

Vector2::Vector2(double p_x, double p_y) : data{ p_x, p_y } {

}

Vector2::~Vector2() {

}

double Vector2::x() const {
	return data[0];
}

double Vector2::y() const {
	return data[1];
}

Vector2 Vector2::operator-() const {
	return Vector2(-data[0], -data[1]);
}

double Vector2::operator[](int index) const {
	return data[index];
}

double& Vector2::operator[](int index) {
	return data[index];
}

Vector2& Vector2::operator+=(const Vector2& other) {
	data[0] += other[0];
	data[1] += other[1];
	return *this;
}

Vector2& Vector2::operator*=(const double scalar) {
	data[0] *= scalar;
	data[1] *= scalar;
	return *this;
}

Vector2& Vector2::operator/=(const double scalar) {
	return *this *= 1 / scalar;
}

double Vector2::length_squared() {
	return data[0] * data[0] + data[1] * data[1];
}

double Vector2::length() {
	return sqrt(length_squared());
}

Vector2 Vector2::normalize() {
	double magnitude = length();
	return Vector2(data[0] / magnitude, data[1] / magnitude);
}
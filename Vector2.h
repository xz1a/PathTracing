#ifndef _VECTOR_2_H_
#define _VECTOR_2_H_
#include <math.h>

class Vector2 {
public:
	Vector2();
	Vector2(double p_x, double p_y);
	~Vector2();

	double x() const;
	double y() const;

	Vector2 operator-() const;
	double operator[](int index) const;
	double& operator[](int index);
	Vector2& operator+=(const Vector2& other);
	Vector2& operator*=(const double scalar);
	Vector2& operator/=(const double scalar);
	double length_squared();
	double length();
	Vector2 normalize();
protected:
private:
	double data[2];
};

typedef Vector2 Vec2;
#endif
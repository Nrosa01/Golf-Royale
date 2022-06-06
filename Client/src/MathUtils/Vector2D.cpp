#include "Vector2D.h"
#include <math.h>

using namespace std;

Vector2D Vector2D::operator+(const Vector2D& vector) const { return { x + vector.x, y + vector.y }; }

Vector2D Vector2D::operator-(const Vector2D& vector) const { return { x - vector.x, y - vector.y }; }

Vector2D Vector2D::operator+=(const Vector2D vector) { return {x += vector.x, y += vector.y}; }

float Vector2D::operator*(const Vector2D& vector) const { return vector.x * x + vector.y * y; }

Vector2D Vector2D::operator*(float number) const { return { x * number , y * number }; }

void Vector2D::operator*=(float number) { x *= number; y *= number; }

bool Vector2D::operator==(const Vector2D& vector) const { return (x == vector.x && y == vector.y); }

bool Vector2D::operator!=(const Vector2D& vector) const { return (x != vector.x || y != vector.y); }

void Vector2D::operator=(const Vector2D& vector) { x = vector.x; y = vector.y; }

Vector2D Vector2D::inverted() const { return *this * -1; }

Vector2D Vector2D::normalized() const
{
	if (this->x == 0 && this->y == 0) return { 0,0 };
	float module = magnitude();
	return {(this->x / module), (this->y/module)};
}

float Vector2D::magnitude() const
{
	return sqrt(pow(this->x, 2) + pow(this->y, 2));
}

istream& operator>>(istream& in, Vector2D& vector)
{
	in >> vector.x >> vector.y;
	return in;
}

ostream& operator<<(ostream& out, const Vector2D& vector)
{
	out << vector.x << " " << vector.y;
	return out;
}

float Vector2D::angle() const
{
	return atan2(y, x) * 180 / M_PI;
}
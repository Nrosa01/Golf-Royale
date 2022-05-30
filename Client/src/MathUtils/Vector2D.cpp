#include "Vector2D.h"
#include <math.h>

using namespace std;

Vector2D Vector2D::operator+(const Vector2D& vector) const { return { x + vector.x, y + vector.y }; }

Vector2D Vector2D::operator-(const Vector2D& vector) const { return { x - vector.x, y - vector.y }; }

Vector2D Vector2D::operator+=(const Vector2D vector) { return {x += vector.x, y += vector.y}; }

int Vector2D::operator*(const Vector2D& vector) const { return vector.x * x + vector.y * y; }

Vector2D Vector2D::operator*(int number) const { return { x * number , y * number }; }

Vector2D Vector2D::operator*=(int number) { x *= number; y *= number; }

bool Vector2D::operator==(const Vector2D& vector) const { return (x == vector.x && y == vector.y); }

bool Vector2D::operator!=(const Vector2D& vector) const { return (x != vector.x || y != vector.y); }

void Vector2D::operator=(const Vector2D& vector) { x = vector.x; y = vector.y; }

Vector2D Vector2D::Invert() const { return *this * -1; }

Vector2D Vector2D::Normalized() const
{
	if (this->x == 0 && this->y == 0) return { 0,0 };
	float module = Magnitude();
	return {(int)(this->x / module), (int)(this->y/module)};
}

float Vector2D::Magnitude() const
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

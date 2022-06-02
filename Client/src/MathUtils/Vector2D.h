#ifndef Vector2DH
#define Vector2DH
#include <fstream>
using namespace std;

class Vector2D
{
public:
	float x;
	float y;

	Vector2D() : x(), y() {};
	Vector2D(float x, float y) : x(x), y(y) {};

	float getX() const { return x; }; // obtener x
	void setX(float xValue) { x = xValue; }; // establecer x
	float getY() const { return y; }; // obtener y
	void setY(float yValue) { y = yValue; }; // establecer y
	float angle() const;

	Vector2D operator+  (const Vector2D& vector) const; // suma
	Vector2D operator-  (const Vector2D& vector) const; // resta
	Vector2D operator+= (const Vector2D vector);        // suma
	float operator*       (const Vector2D& vector) const; // producto escalar
	Vector2D operator*  (float number) const;             // producto de vector por escalar
	void operator*=  (float number);             // producto de vector por escalar
	bool operator==     (const Vector2D& vector) const; // igualdad
	bool operator!=     (const Vector2D& vector) const; // desigualdad
	void operator=      (const Vector2D& vector);       // asignación
	Vector2D Inverted     () const;						// devuelve el vector multiplicado por -1
	Vector2D Normalized () const;						// devuelve el vector normalizado
	float Magnitude  ()const;						// devuelve el módulo del vector
	friend istream& operator>>(istream& in, Vector2D& vector);
	friend ostream& operator<<(ostream& out, const Vector2D& vector);
};

#endif
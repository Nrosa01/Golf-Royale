#ifndef Vector2DH
#define Vector2DH
#include <fstream>
using namespace std;

class Vector2D
{
private:
	int x;
	int y;

public:
	Vector2D() : x(), y() {};
	Vector2D(int x, int y) : x(x), y(y) {};

	int getX() const { return x; }; // obtener x
	void setX(int xValue) { x = xValue; }; // establecer x
	int getY() const { return y; }; // obtener y
	void setY(int yValue) { y = yValue; }; // establecer y

	Vector2D operator+  (const Vector2D& vector) const; // suma
	Vector2D operator-  (const Vector2D& vector) const; // resta
	Vector2D operator+= (const Vector2D vector);        // suma
	int operator*       (const Vector2D& vector) const; // producto escalar
	Vector2D operator*  (int number) const;             // producto de vector por escalar
	bool operator==     (const Vector2D& vector) const; // igualdad
	bool operator!=     (const Vector2D& vector) const; // desigualdad
	void operator=      (const Vector2D& vector);       // asignación
	Vector2D Invert     () const;						// devuelve el vector multiplicado por -1
	Vector2D Normalized () const;						// devuelve el vector normalizado
	float Magnitude  ()const;						// devuelve el módulo del vector
	friend istream& operator>>(istream& in, Vector2D& vector);
	friend ostream& operator<<(ostream& out, const Vector2D& vector);
};

#endif
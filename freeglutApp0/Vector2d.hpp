#include <math.h>

#include "Draw.hpp"

typedef double COORDINATE;
class Vector2d {
public:
	Vector2d() : x(0), y(0) {}
	Vector2d(COORDINATE new_x, COORDINATE new_y) : x(new_x), y(new_y) {}

	COORDINATE get_x() {
		return x;
	}
	COORDINATE get_y() {
		return y;
	}

	Vector2d operator+(Vector2d other) {
		return Vector2d(x + other.get_x(), y + other.get_y());
	}
	Vector2d operator-(Vector2d other) {
		return Vector2d(x - other.get_x(), y - other.get_y());
	}
	COORDINATE operator*(Vector2d other) {
		return x * other.get_x() + y * other.get_y();
	}
	Vector2d operator*(COORDINATE number) {
		return Vector2d(x * number, y * number);
	}
	Vector2d operator/(COORDINATE number) {
		return Vector2d(x / number, y / number);
	}
	COORDINATE length() {
		return sqrt(x * x + y * y);
	}
	Vector2d normalize() {
		return Vector2d(x, y) / length();
	}

	void draw() {
		int rounded_x = lround(x),
			rounded_y = lround(y);
		Draw::putPixel(rounded_x, rounded_y, White);
	}

protected:
	COORDINATE x, y;
};
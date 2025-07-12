#include "Draw.hpp"
#include "Vector2d.hpp"

class Primitive {
public:
	void draw() {}
};

class Point2d : Primitive {
public:
	Point2d() : position(Vector2d()) {}
	Point2d(int new_x, int new_y) : position(Vector2d(new_x, new_y)) {}
	Point2d(Vector2d pos) : position(pos) {}

	void draw() {
		position.draw();
	}
	COORDINATE get_x() {
		return position.get_x();
	}
	COORDINATE get_y() {
		return position.get_y();
	}
	Vector2d get_position() {
		return position;
	}
protected:
	Vector2d position;
};

class ColoredPoint2d : Point2d {
public:
	ColoredPoint2d() : position(Vector2d()), color(Color(White)) {}
	ColoredPoint2d(int new_r, int new_g, int new_b, int new_x, int new_y) : color(Color(new_r, new_g, new_b)), position(new_x, new_y) {}

	void draw() {
		Draw::putPixel(lround(position.get_x()), lround(position.get_y()), color);
	}
	int get_x() {
		return position.get_x();
	}
	int get_y() {
		return position.get_y();
	}

protected:
	Color color;
	Vector2d position;
};

class Line2d : Primitive {
public:
	Line2d() : point1(Point2d()), point2(Point2d()) {}
	Line2d(Point2d new_point1, Point2d new_point2) : point1(new_point1), point2(new_point2) {}

	void draw() {
		Vector2d position1 = point1.get_position(),
			position2 = point2.get_position(),
			direction = (position2 - position1).normalize(),
			current = position1;
		COORDINATE length = (position2 - position1).length();
		for (int i = 0; i < length && current.get_x() < WIDTH - 1 && current.get_y() < HEIGHT - 1 && current.get_x() > 0 && current.get_y() > 0; i++) {
			current.draw();
			current = current + direction;
		}
	}
protected:
	Point2d point1, point2;
};
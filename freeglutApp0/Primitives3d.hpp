#include "Primitives2d.hpp"
#include "Vector3d.hpp"

class Point3d : Primitive {
public:
	Point3d() : position(Vector3d()) {}
	Point3d(COORDINATE x, COORDINATE y, COORDINATE z) : position(Vector3d(x, y, z)) {}
	Point3d(Vector3d pos) : position(pos) {}

	void drawFishEye(Camera camera) {
		Vector3d relative = position - camera.position;
		int y = (relative.angle(camera.axis) / atan(1) / 4 * HEIGHT * 2) - HEIGHT / 4;
		int x = WIDTH / 2 - atan2((relative - camera.axis * (relative * camera.axis)) * camera.side, (relative - camera.axis * (relative * camera.axis)) * camera.direction) / atan(1) / 4 * HEIGHT * 2;
		Draw::putPixel(x, y, White);
	}
	void drawPerspective(Camera camera) {
		Vector3d relative = position - camera.position;
		if (relative * camera.direction < 0) {
			return;
		}
		int x = -relative.projectToAxis(camera.side) / relative.projectToAxis(camera.direction) * HEIGHT + WIDTH / 2;
		int y = -relative.projectToAxis(camera.axis) / relative.projectToAxis(camera.direction) * HEIGHT+ HEIGHT / 2;
		Draw::putPixel(x, y, White);
	}
	void draw(Camera camera) {
		drawPerspective(camera);
	}
	Point2d get2dPos(Camera camera) {
		Vector3d relative = position - camera.position;
		int y = HEIGHT / 2 - (relative.angle(camera.axis) / atan(1) / 4 * HEIGHT * 2);
		int x = WIDTH / 2 - atan2((relative - camera.axis * (relative * camera.axis)) * camera.side, (relative - camera.axis * (relative * camera.axis)) * camera.direction) / atan(1) / 4 * HEIGHT * 4;
		return Point2d(x, y);
	}
	COORDINATE get_x() {
		return position.get_x();
	}
	COORDINATE get_y() {
		return position.get_y();
	}
	COORDINATE get_z() {
		return position.get_z();
	}
	Vector3d get_position() {
		return position;
	}
protected:
	Vector3d position;
};

class Line3d : Primitive {
public:
	Line3d(Point3d point1, Point3d point2) : a(point1), b(point2) {}
	void draw(Camera camera) {
		Vector3d begin = a.get_position(),
			end = b.get_position(),
			current = begin,
			direction = (begin - end).normalize();
		
		COORDINATE lenght = (begin - end).length();
		for (int i = 0; i < lenght; i++) {
			Point3d(current).draw(camera);
			current = current - direction;
		}
	}
private:
	Point3d a, b;
};
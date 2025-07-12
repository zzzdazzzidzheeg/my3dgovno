#include <math.h>
#include <numbers>
#include <cstdio>

#include "Draw.hpp"

typedef double ANGLE;

typedef double COORDINATE;
class Vector3d {
public:
	Vector3d() : x(0), y(0), z(0) {}
	Vector3d(COORDINATE new_x, COORDINATE new_y, COORDINATE new_z) : x(new_x), y(new_y), z(new_z) {}

	COORDINATE get_x() {
		return x;
	}
	COORDINATE get_y() {
		return y;
	}
	COORDINATE get_z() {
		return z;
	}

	static Vector3d sum(Vector3d a, Vector3d b) {
		return Vector3d(a.get_x() + b.get_x(),
			a.get_y() + b.get_y(),
			a.get_z() + b.get_z());
	}
	static Vector3d diff(Vector3d a, Vector3d b) {
		return Vector3d(a.get_x() - b.get_x(),
			a.get_y() - b.get_y(),
			a.get_z() - b.get_z());
	}

	Vector3d operator+(Vector3d other) {
		return Vector3d(x + other.get_x(),
			y + other.get_y(),
			z + other.get_z());
	}
	Vector3d operator-(Vector3d other) {
		return Vector3d(x - other.get_x(),
			y - other.get_y(),
			z - other.get_z());
	}
	COORDINATE operator*(Vector3d other) {
		return x * other.get_x() +
			y * other.get_y() +
			z * other.get_z();
	}
	Vector3d operator^(Vector3d other) {
		return Vector3d(y * other.get_z() - z * other.get_y(),
			z * other.get_x() - x * other.get_z(),
			x * other.get_y() - y * other.get_x());
	}
	Vector3d operator*(COORDINATE number) {
		return Vector3d(x * number, y * number, z * number);
	}
	Vector3d operator/(COORDINATE number) {
		return Vector3d(x / number, y / number, z / number);
	}
	COORDINATE length() {
		return sqrt(x * x + y * y + z * z);
	}
	Vector3d normalize() {
		return Vector3d(x, y, z) / length();
	}
	
	static ANGLE angle(Vector3d a, Vector3d b) {
		return acos(a * b / a.length() / b.length());
	}

	ANGLE angle(Vector3d other) {
		Vector3d temp = Vector3d(x, y, z);
		return acos(temp * other / temp.length() / other.length());
	}

	COORDINATE projectToAxis(Vector3d axis) {
		Vector3d temp = Vector3d(x, y, z);
		return (temp * axis);
	}

	Vector3d rotate(ANGLE angle) {
		return Vector3d();
	}

protected:
	COORDINATE x, y, z;
};

class Matrix3d {
public:
	Matrix3d(COORDINATE new_xx, COORDINATE new_xy, COORDINATE new_xz,
		COORDINATE new_yx, COORDINATE new_yy, COORDINATE new_yz,
		COORDINATE new_zx, COORDINATE new_zy, COORDINATE new_zz) :
		xx(new_xx), xy(new_xy), xz(new_xz),
		yx(new_yx), yy(new_yy), yz(new_yz),
		zx(new_zx), zy(new_zy), zz(new_zz) {}
	Matrix3d(Vector3d x, Vector3d y, Vector3d z) : 
		xx(x.get_x()), xy(x.get_y()), xz(x.get_z()), 
		yx(y.get_x()), yy(y.get_y()), yz(y.get_z()),
		zx(z.get_x()), zy(z.get_y()), zz(z.get_z()) {}

	COORDINATE get_xx() {
		return xx;
	}
	COORDINATE get_xy() {
		return xy;
	}
	COORDINATE get_xz() {
		return xz;
	}

	COORDINATE get_yx() {
		return yx;
	}
	COORDINATE get_yy() {
		return yy;
	}
	COORDINATE get_yz() {
		return yz;
	}

	COORDINATE get_zx() {
		return zx;
	}
	COORDINATE get_zy() {
		return zy;
	}
	COORDINATE get_zz() {
		return zz;
	}

	Vector3d get_x() {
		return Vector3d(xx, xy, xz);
	}
	Vector3d get_y() {
		return Vector3d(yx, yy, yz);
	}
	Vector3d get_z() {
		return Vector3d(zx, zy, zz);
	}

	Vector3d transform(Vector3d vec) {
		COORDINATE x = vec.get_x(), y = vec.get_y(), z = vec.get_z();
		return Vector3d(x * xx + y * xy + z * xz,
			x * yx + y * yy + z * yz,
			x * zx + y * zy + z * zz);
	}

	Matrix3d operator*(Matrix3d other) {
		return Matrix3d(
			Vector3d(xx * other.get_xx() + xy * other.get_yx() + xz * other.get_zx(),
				xx * other.get_xy() + xy * other.get_yy() + xz * other.get_zy(),
				xx * other.get_xz() + xy * other.get_yz() + xz * other.get_zz()),

			Vector3d(yx * other.get_xx() + yy * other.get_yx() + yz * other.get_zx(),
				yx * other.get_xy() + yy * other.get_yy() + yz * other.get_zy(),
				yx * other.get_xz() + yy * other.get_yz() + yz * other.get_zz()),

			Vector3d(zx * other.get_xx() + zy * other.get_yx() + zz * other.get_zx(),
				zx * other.get_xy() + zy * other.get_yy() + zz * other.get_zy(),
				zx * other.get_xz() + zy * other.get_yz() + zz * other.get_zz())
		);
	}
	Matrix3d operator*(COORDINATE number) {
		return Matrix3d(
			Vector3d(xx * number,
				xy * number,
				xz * number),  

			Vector3d(yx * number,
				yy * number,
				yz * number),

			Vector3d(zx * number,
				zy * number,
				zz * number)
		);
	}

	COORDINATE determinant() {
		return xx * (yy * zz - yz * zy) 
			- xy * (yx * zz - yz * zx) 
			+ xz * (yx * zy - zx * yy);
	}
	Matrix3d inverse() {
		COORDINATE invdet = 1 / determinant();
		return Matrix3d(
			Vector3d(yy * zz - yz * zy,
				xz * zy - xy * zz,
				xy * yx - xz * yy),
			Vector3d(yz * zx - yx * zz, 
				xx * zz - xz * zx,
				xz * yx - xx * yz),
			Vector3d(yx * zy - yy * zx,
				xy * zx - xx * zy,
				xx * yy - xy * yx)) * invdet;
	}
	Matrix3d unitInverse() {
		return Matrix3d(
			Vector3d(yy * zz - yz * zy,
				xz * zy - xy * zz,
				xy * yx - xz * yy),
			Vector3d(yz * zx - yx * zz,
				xx * zz - xz * zx,
				xz * yx - xx * yz),
			Vector3d(yx * zy - yy * zx,
				xy * zx - xx * zy,
				xx * yy - xy * yx));
	}
protected:
	COORDINATE xx, xy, xz,
		yx, yy, yz,
		zx, zy, zz;
};

class Camera {
public:
	Vector3d position;
	Vector3d direction;
	Vector3d axis;
	Vector3d side;
	void initCamera() {
		position = Vector3d();
		direction = Vector3d(1, 0, 0);
		axis = Vector3d(0, 0, 1);
		side = axis ^ direction;
	}

	Camera() : position(Vector3d()), direction(Vector3d(1, 0, 0)), axis(Vector3d(0, 0, 1)), side(Vector3d(0, 1, 0)) {}

	void goToward() {
		position = position + direction;
	}
	void goBackward() {
		position = position - direction;
	}
	void goLeft() {
		position = position + side;
	}
	void goRight() {
		position = position - side;
	}
	void goUp() {
		position = position + axis;
	}
	void goDown() {
		position = position - axis;
	}
	void rotateXY(ANGLE angle) {
		Matrix3d coord = Matrix3d(direction, side, axis),
			rot = Matrix3d(Vector3d(cos(angle), sin(angle), 0),
				Vector3d(-sin(angle), cos(angle), 0),
				Vector3d(0, 0, 1));
		rot = rot;
		direction = rot.transform(direction);
		side = rot.transform(side);
		axis = rot.transform(axis);
	}
private:
};
#pragma once

#include <gl/GL.h>

#include "Color.hpp"

#define WIDTH 800
#define HEIGHT 600

static GLubyte* frame;

class Draw {
public:
	static void putPixel(int x, int y, GLubyte r, GLubyte g, GLubyte b) {
		if (isCorrectPixel(x, y, r, g, b)) {
			frame[y * WIDTH * 3 + x * 3] = b;
			frame[y * WIDTH * 3 + x * 3 + 1] = g;
			frame[y * WIDTH * 3 + x * 3 + 2] = r;
		}
	}
	
	static void putPixel(int x, int y, stdColor color) {
		if (isCorrectPixel(x, y)) {
			Color rgb = Color(color);
			frame[y * WIDTH * 3 + x * 3] = rgb.get_b();
			frame[y * WIDTH * 3 + x * 3 + 1] = rgb.get_g();
			frame[y * WIDTH * 3 + x * 3 + 2] = rgb.get_r();
		}
	}
	static void putPixel(int x, int y, Color color) {
		if (isCorrectPixel(x, y)) {
			frame[y * WIDTH * 3 + x * 3] = color.get_b();
			frame[y * WIDTH * 3 + x * 3 + 1] = color.get_g();
			frame[y * WIDTH * 3 + x * 3 + 2] = color.get_r();
		}
	}
private:
	static bool isCorrectPixel(int x, int y, GLubyte r, GLubyte g, GLubyte b) {
		return x <= WIDTH && x >= 0 && y < HEIGHT && y >= 0 && r >= 0 && g >= 0 && b >= 0 && r < 256 && g < 256 && b < 256;
	}
	static bool isCorrectPixel(int x, int y) {
		return x <= WIDTH && x >= 0 && y < HEIGHT && y >= 0;
	}
};
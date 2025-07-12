enum stdColor {
	White, Red, Blue, Green, Yellow, Cyan, Magenta, Black, Brown
};

class Color {
public:
	Color(int new_r, int new_g, int new_b) : r(new_r), g(new_g), b(new_b) {}
	Color(stdColor color) {
		switch (color) {
		case White:
			r = 255;
			g = 255;
			b = 255;
			break;
		case Red:
			r = 255;
			g = 0;
			b = 0;
			break;
		case Green:
			r = 0;
			g = 255;
			b = 0;
			break;
		case Blue: 
			r = 0;
			g = 0;
			b = 255;
			break;
		case Yellow:
			r = 255;
			g = 255;
			b = 0;
			break;
		case Cyan:
			r = 0;
			g = 255;
			b = 255;
			break;
		case Magenta:
			r = 255;
			g = 0;
			b = 255;
			break;
		case Black:
			r = 0;
			b = 0;
			g = 0;
			break;
		case Brown:
			r = 50;
			g = 50;
			b = 0;
			break;
		}
	}
	int get_r() {
		return r;
	}
	int get_g() {
		return g;
	}
	int get_b() {
		return b;
	}
private:
	int r = 0, g = 0, b = 0;
};
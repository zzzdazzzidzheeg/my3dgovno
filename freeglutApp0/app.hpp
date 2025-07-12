#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <iostream>
#include <freeglut.h>

#include "Draw.hpp"
#include "Primitives3d.hpp"


Camera camera;

class App {
public:
	void run(int *argc, char **argv) {
		init(argc, argv);
		createWindow("Lol");
		initFrame();
		camera = Camera();

		glutDisplayFunc(App::display);
		glutKeyboardFunc(App::keyboard);

		glutMainLoop();
		close();
	}
	int width() {
		return w;
	}
	int height() {
		return h;
	}
private:
	static const int w = 800;
	static const int h = 600;

	void init(int* argc, char **argv) {
		glutInit(argc, argv);
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
		glutInitWindowSize(w, h);
		glutInitWindowPosition(0, 0);
	}
	void createWindow(const char* windowName) {
		glutCreateWindow(windowName);
	}
	void initFrame() {
		frame = new GLubyte[w * h * 3 + 3];
		for (int i = 0; i < w * h * 3; i++) {
			frame[i] = 0;
		}
	}
	static void clearFrame() {
		for (int i = 0; i < w * h * 3; i++) {
			frame[i] = 0;
		}
	}
	static void display(void)
	{
		Line3d ab = Line3d(Point3d(100, -50, 100), Point3d(100, 50, 100)),
			bc = Line3d(Point3d(100, 50, 100), Point3d(100, 50, 200)),
			cd = Line3d(Point3d(100, 50, 200), Point3d(100, -50, 200)),
			da = Line3d(Point3d(100, -50, 200), Point3d(100, -50, 100)),
			a1a = Line3d(Point3d(100, -50, 100), Point3d(200, -50, 100)),
			b1b = Line3d(Point3d(100, 50, 100), Point3d(200, 50, 100)),
			c1c = Line3d(Point3d(100, 50, 200), Point3d(200, 50, 200)),
			d1d = Line3d(Point3d(100, -50, 200), Point3d(200, -50, 200)),
			a1b1 = Line3d(Point3d(200, -50, 100), Point3d(200, 50, 100)),
			b1c1 = Line3d(Point3d(200, 50, 100), Point3d(200, 50, 200)),
			c1d1 = Line3d(Point3d(200, 50, 200), Point3d(200, -50, 200)),
			d1a1 = Line3d(Point3d(200, -50, 200), Point3d(200, -50, 100));
		//Line3d line = Line3d(Point3d(100, 0, -50), Point3d(100, 0, 50));
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
		glRasterPos2d(-1, 1);
		glPixelZoom(1, -1);
		clearFrame();
		ab.draw(camera);
		bc.draw(camera);
		cd.draw(camera);
		da.draw(camera);
		a1a.draw(camera);
		b1b.draw(camera);
		c1c.draw(camera);
		d1d.draw(camera);
		a1b1.draw(camera);
		b1c1.draw(camera);
		c1d1.draw(camera);
		d1a1.draw(camera);
		//line.draw(camera);
		glDrawPixels(w, h, GL_BGR_EXT, GL_UNSIGNED_BYTE, frame);
		glFinish();
		glutSwapBuffers();
		glutPostRedisplay();
	}

	static void keyboard(unsigned char key, int x, int y) {
		switch (key) {
		case 27:
			exit(0);
			break;
		case 'w':
			camera.goToward();
			break;
		case 's':
			camera.goBackward();
			break;
		case 'a':
			camera.goLeft();
			break;
		case 'd':
			camera.goRight();
			break;
		case ' ':
			camera.goUp();
			break;
		case 'z':
			camera.goDown();
			break;
		case 'j' :
			camera.rotateXY(-1.0/100);
			break;
		case 'l':
			camera.rotateXY(1.0 / 100);
			break;
		}
	}

	void close() {
		delete[] frame;
	}
};
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <iostream>
#include <freeglut.h>

#include "app.hpp"
int main(int argc, char** argv)
{
    App app;
    app.run(&argc, argv);
    return 0;
}
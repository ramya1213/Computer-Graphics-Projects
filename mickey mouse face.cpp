#include <iostream>
#include <cmath>
#include <glut.h>

using namespace std;

void init()
{
glOrtho(-10, 10, -10, 10, -10, 10);
}

void func1()
{
//glClearColor(0.76, 0.34, 1, 0);

glClearColor(0.6, 0.4, 0.5, 0);
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(0.2, 0.3, .42);
glPointSize(5);
glLineWidth(5);

float PI = 2*acos(0);
//first ear
for (float x = 0; x <= PI*2; x += 0.001) {
glBegin(GL_LINES);
glVertex2f(-2+1.5*sin(x), 1.5*cos(x));
glVertex2f(-2+1.5*sin(x+0.03), 1.5*cos(x+0.03));
glEnd();
}

//second ear
for ( x = 0; x <= PI*2; x += 0.001) {
glBegin(GL_LINES);
glVertex2f(2+1.5*sin(x), 1.5*cos(x));
glVertex2f(2+1.5*sin(x+0.001), 1.5*cos(x+0.001));
glEnd();
}

//face structure
for ( x = 0; x <= PI*2; x += 0.001) {
glBegin(GL_POINTS);
glVertex2f(3.5*sin(x), -5+3.5*cos(x));
glEnd();
}

//nose
for ( x = 0; x <= PI*2; x += 0.001) {
glBegin(GL_LINES);
glVertex2f(1.2*sin(x), -5.7+0.7*cos(x));
glVertex2f(1.2*sin(x+0.001), -5.7+0.7*cos(x+0.001));
glEnd();
}

//hair on nose
for (x = -1.2; x <= 1.2; x += 0.001) {
glBegin(GL_LINES);
glVertex2f(1.5*sin(x), -5.5+1*cos(x));
glVertex2f(1.5*sin(x+0.001), -5.5+1*cos(x+0.001));
glEnd();
}

//first eye
for ( x = 0; x <= PI*2; x += 0.001) {
glBegin(GL_LINES);
glVertex2f(-0.7+0.5*sin(x), -3.5+1*cos(x));
glVertex2f(-0.7+0.5*sin(x+0.001), -3.5+1*cos(x+0.001));
glEnd();
}

//second eye
for (x = 0; x <= PI*2; x += 0.001) {
glBegin(GL_LINES);
glVertex2f(0.7+0.5*sin(x), -3.5+1*cos(x));
glVertex2f(0.7+0.5*sin(x+0.001), -3.5+1*cos(x+0.001));
glEnd();
}

//second eyelid
for ( x = 0; x <= PI*2; x += 0.001) {
glBegin(GL_LINES);
glVertex2f(0.7+0.3*sin(x), -3.9+0.7*cos(x));
glVertex2f(0.7+0.3*sin(x+0.001), -3.9+0.7*cos(x+0.001));
glEnd();
}

//first eyelid
for ( x = 0; x <= PI*2; x += 0.001) {
glBegin(GL_LINES);
glVertex2f(-0.7+0.3*sin(x), -3.9+0.7*cos(x));
glVertex2f(-0.7+0.3*sin(x+0.001), -3.9+0.7*cos(x+0.001));
glEnd();
}

//face upper
for ( x = PI/2+0.3; x <= 3*PI/2-0.3; x += 0.001) {
glBegin(GL_LINES);
glVertex2f(2.5*sin(x), -5.1+2*cos(x));
glVertex2f(2.5*sin(x+0.001), -5.1+2*cos(x+0.001));
glEnd();
}

//face lower
for ( x = PI/2; x <= 3*PI/2; x += 0.001) {
glBegin(GL_LINES);
glVertex2f(1.3*sin(x), -6.9+0.9*cos(x));
glVertex2f(1.3*sin(x+0.001), -6.9+0.9*cos(x+0.001));
glEnd();
}

//face lower second
for ( x = PI/2+0.3; x <= 3*PI/2-0.3; x += 0.001) {
glBegin(GL_LINES);
glVertex2f(2.5*sin(x), -5.1+2*cos(x));
glVertex2f(2.5*sin(x+0.001), -5.1+2*cos(x+0.001));
glEnd();
}

glEnd();
glFlush();
}

int main(int argc, char **argv)
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE);
glutInitWindowSize(600, 600);
glutInitWindowPosition(100, 100);
glutCreateWindow("Mickey Mouse");
init();
glutDisplayFunc(func1);
glutMainLoop();

return 0;
}



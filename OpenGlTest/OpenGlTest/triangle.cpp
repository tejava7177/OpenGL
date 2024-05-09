//
//  triangle.cpp
//  OpenGlTest
//
//  Created by 심주흔 on 5/8/24.
//

#define GL_SILENCE_DEPRECATION      //버전 오류 해결
#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>

#include <cstdlib> // 랜덤 색상을 생성하기 위해 필요

static int leftFirst = GL_TRUE;
float alpha = 1.0;

static void init(void) {
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA);
glShadeModel(GL_FLAT);
glClearColor(0.0, 0.0, 0.0, 0.0);


}

static void drawLeftTriangle(void) {
glBegin(GL_TRIANGLES);
glColor4f(0.0, 1.0, 0.0, alpha);
glVertex3f(0.1, 0.9, 0.0);
glVertex3f(0.1, 0.1, 0.0);
glVertex3f(0.7, 0.5, 0.0);
glEnd();
}

static void drawRighTriangle(void) {
glBegin(GL_TRIANGLES);
glColor4f(1.0, 0.0, 0.0, alpha);
glVertex3f(0.9, 0.9, 0.0);
glVertex3f(0.3, 0.5, 0.0);
glVertex3f(0.9, 0.1, 0.0);
glEnd();
}

void display(void) {
glClear(GL_COLOR_BUFFER_BIT);

if (leftFirst) {
drawLeftTriangle();
drawRighTriangle();
}

else {
drawRighTriangle();
drawLeftTriangle();
}

glFlush();
}

void reshape(int w, int h) {
glViewport(0, 0, (GLsizei)w, (GLsizei)h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();

if (w <= h)
gluOrtho2D(0.0, 1.0, 0.0, 1.0 * (GLfloat)h / (GLfloat)w);
else
gluOrtho2D(0.0, 1.0 * (GLfloat)w / (GLfloat)h, 0.0, 1.0);
}

void keyboard(unsigned char key, int x, int y) {
switch (key)
{
case 't':
case 'T':
leftFirst = !leftFirst;
glutPostRedisplay();
break;

case 'a':
if (alpha > 0) alpha -= 0.05;
glutPostRedisplay();
break;

case 27:
exit(0);
break;

default:
break;
}
}


int main(int argc, char** argv) {
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize(500, 500);
glutCreateWindow(argv[0]);
init();

glutReshapeFunc(reshape);
glutKeyboardFunc(keyboard);
glutDisplayFunc(display);
glutMainLoop();

return 0;
}

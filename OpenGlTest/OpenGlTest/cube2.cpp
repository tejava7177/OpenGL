////
////  cube2.cpp
////  OpenGlTest
////
////  Created by 심주흔 on 5/1/24.
////
//
//#define GL_SILENCE_DEPRECATION      //버전 오류 해결
//#include <iostream>
//#include <OpenGL/gl.h>
//#include <OpenGl/glu.h>
//#include <GLUT/glut.h>
//#include <vector>
//#include <cstdlib> // 랜덤 색상을 생성하기 위해 필요
//
//
//GLint winWidth = 600, winHeight = 600;
//GLfloat eyeX = 0.0, eyeY = 0.0, eyeZ = 2.0;
//GLfloat theta = 270.0, phi = 180.0;
//GLfloat upX = 0.0, upY = 1.0, upZ = 0.0;
//GLfloat r = 2.0;
//
//void draw_cube() {
////앞쪽
//glBegin(GL_POLYGON);
//glColor3f(1.0, 1.0, 1.0);
//glVertex3f(0.5, 0.5, 0.5);
//
//glColor3f(1.0, 0.0, 1.0);
//glVertex3f(-0.5, 0.5, 0.5);
//
//glColor3f(1.0, 0.0, 0.0);
//glVertex3f(-0.5, -0.5, 0.5);
//
//glColor3f(1.0, 1.0, 0.0);
//glVertex3f(0.5, -0.5, 0.5);
//glEnd();
//
//
////오른쪽
//glBegin(GL_POLYGON);
//glColor3f(1.0, 1.0, 1.0);
//glVertex3f(0.5, 0.5, 0.5);
//
//glColor3f(1.0, 1.0, 0.0);
//glVertex3f(0.5, -0.5, 0.5);
//
//glColor3f(0.0, 1.0, 0.0);
//glVertex3f(0.5, -0.5, -0.5);
//
//glColor3f(0.0, 1.0, 1.0);
//glVertex3f(0.5, 0.5, -0.5);
//glEnd();
//
//
//
////위쪽
//glBegin(GL_POLYGON);
//glColor3f(1.0, 0.0, 1.0);
//glVertex3f(-0.5, 0.5, 0.5);
//
//glColor3f(1.0, 1.0, 1.0);
//glVertex3f(0.5, 0.5, 0.5);
//
//glColor3f(0.0, 1.0, 1.0);
//glVertex3f(0.5, 0.5, -0.5);
//
//glColor3f(0.0, 0.0, 1.0);
//glVertex3f(-0.5, 0.5, -0.5);
//glEnd();
//
//
//
////왼쪽
//glBegin(GL_POLYGON);
//glColor3f(1.0, 0.0, 1.0);
//glVertex3f(-0.5, 0.5, 0.5);
//
//glColor3f(0.0, 0.0, 1.0);
//glVertex3f(-0.5, 0.5, -0.5);
//
//glColor3f(0.0, 0.0, 1.0);
//glVertex3f(-0.5, -0.5, -0.5);
//
//glColor3f(1.0, 0.0, 0.0);
//glVertex3f(-0.5, -0.5, -0.5);
//glEnd();
//
////아래쪽
//glBegin(GL_POLYGON);
//glColor3f(1.0, 0.0, 0.0);
//glVertex3f(-0.5, -0.5, 0.5);
//
//glColor3f(0.0, 0.0, 1.0);
//glVertex3f(-0.5, -0.5, -0.5);
//
//glColor3f(0.0, 1.0, 0.0);
//glVertex3f(0.5, -0.5, -0.5);
//
//glColor3f(1.0, 1.0, 0.0);
//glVertex3f(0.5, -0.5, 0.5);
//glEnd();
//
//
////뒤쪽
//glBegin(GL_POLYGON);
//glColor3f(0.0, 0.0, 1.0);
//glVertex3f(-0.5, 0.5, -0.5);
//
//glColor3f(0.0, 1.0, 1.0);
//glVertex3f(0.5, 0.5, -0.5);
//
//glColor3f(0.0, 1.0, 0.0);
//glVertex3f(0.5, -0.5, -0.5);
//
//glColor3f(0.0, 0.0, 1.0);
//glVertex3f(-0.5, -0.5, -0.5);
//glEnd();
//}
//
//void init() {
//glClearColor(0.0, 0.0, 0.0, 0.0);
//glEnable(GL_DEPTH_TEST);
//glMatrixMode(GL_PROJECTION);
//glLoadIdentity();
//glFrustum(-1, 1, -1, 1, 0.6, 300);
//}
//
//void displayFcn() {
//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//glMatrixMode(GL_MODELVIEW);
//glLoadIdentity();
//gluLookAt(eyeX, eyeY, eyeZ, 0, 0, 0, upX, upY, upZ);
//
//glPolygonMode(GL_FRONT, GL_FILL);
//draw_cube();
//
//glutSwapBuffers();
//
//}
//
//void reshapeFunc(GLint newWidth, GLint newHeight) {
//glViewport(0, 0, newWidth, newHeight);
//winWidth = newWidth;
//winHeight = newHeight;
//
//
//}
//
//void eyePosition(void) {
//GLfloat dt = 1.0;
//
//GLfloat eyeXtemp = r * sin(theta * 0.0174531 - dt) * sin(phi * 0.0174532);
//GLfloat eyeYtemp = r * cos(theta * 0.0174532 - dt);
//GLfloat eyeZtemp = r * sin(theta * 0.0174532 - dt) * cos(phi * 0.0174532);
//
//
//eyeX = r * sin(theta * 0.0174531) * sin(phi * 0.0174532);
//eyeY = r * cos(theta * 0.0174532);
//eyeZ = r * sin(theta * 0.0174532) * cos(phi * 0.0174532);
//
//
//upX = eyeXtemp - eyeX;
//upY = eyeYtemp - eyeY;
//upZ = eyeZtemp - eyeZ;
//
//glutPostRedisplay();
//}
//
//void onMouseMove(int x, int y) {
//theta = (360.0 / (double)winHeight) * (double)y * 3.0;
//phi = (360.0 / (double)winWidth)* (double)x * 3.0;
//
//if (theta > 360) theta = fmod((double)theta, 360.0);
//if (phi > 360) phi = fmod((double)phi, 360.0);
//
//eyePosition();
//}
//
//void SpecialKeys(int key, int x, int y) {
//if (key == GLUT_KEY_UP) r -= 0.1;
//if (key == GLUT_KEY_DOWN) r += 0.1;
//
//eyePosition();
//}
//
//int main(int argc, char** argv) {
//glutInit(&argc, argv);
//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//glutInitWindowPosition(50, 50);
//glutInitWindowSize(winWidth, winHeight);
//glutCreateWindow("Camera & RGB Color Cube");
//
//init();
//
//glutDisplayFunc(displayFcn);
//glutReshapeFunc(reshapeFunc);
//glutPassiveMotionFunc(onMouseMove);
//glutSpecialFunc(SpecialKeys);
//glutMainLoop();
//    
//    return 0;
//}
//

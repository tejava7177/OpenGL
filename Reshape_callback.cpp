////
////  Reshape_callback.cpp
////  OpenGlTest
////
////  Created by 심주흔 on 2024/03/19.
////
//
////#include <stdio.h>
//
//
////#include <glut.h>
////#include <stdlib.h>
////#include <GL/glut.h>
//
//#define GL_SILENCE_DEPRECATION      //버전 오류 해결
//
//#include <iostream>
//#include <OpenGL/gl.h>
//#include <OpenGl/glu.h>
//#include <GLUT/glut.h>
//
//void init(void) {
//    glClearColor(0.0, 0.0, 0.0, 0.0);
//    glShadeModel(GL_SMOOTH); //flat 보다 시간이 많이 걸림.
//
//}
//
//void triangle(void) {
//    glBegin(GL_TRIANGLES);
//    glColor3f(1.0, 0.0, 0.0);
//    glVertex2f(-0.5, -0.5);
//    glColor3f(0.0, 1.0, 0.0);
//    glVertex2f(0.5, -0.5);
//    glColor3f(0.0, 0.0, 1.0);
//    glVertex2f(-0.5, 0.5);
//    glEnd();
//}
//
///*
//void display() {
//    glColor3f(1.0, 1.0, 1.0);
//
//    glBegin(GL_POLYGON);
//    glVertex3f(-0.75, -0.75, 0.0);
//    glVertex3f(0.75, -0.75, 0.0);
//    glVertex3f(-0.75, -0.75, 0.0);
//    glVertex3f(-0.75, 0.75, 0.0);
//    glEnd();
//
//    glFlush();
//}
//
//void init() {
//    glClearColor(0.0, 0.0, 0.0, 0.0);
//    glClear(GL_COLOR_BUFFER_BIT);
//}
//*/
//
//void display(void) {
//    glClear(GL_COLOR_BUFFER_BIT);
//    triangle();
//    glFlush();
//}
//
//
//void reshape(int new_w, int new_h) {
//    glViewport(0, 0, new_w, new_h);
//    float WidthFactor = (float) new_w / 300.0;
//    float HeightFactor = (float)new_h / 300.0;
//
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//
//    gluOrtho2D(-1.0 * WidthFactor, 1.0 * WidthFactor, -1.0 * HeightFactor, 1.0 * HeightFactor);
//}
//
//
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//    glutInitWindowSize(300, 300);
//    glutInitWindowPosition(100, 100);
//    glutCreateWindow(argv[0]);
//    init();
//    glutDisplayFunc(display);
//    glutReshapeFunc(reshape);
//    glutMainLoop();
//    return 0;
//}

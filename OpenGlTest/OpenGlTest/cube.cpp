////
////  cube.cpp
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
//
//GLfloat MyVertices[8][3] = {
//{-0.25,-0.25,0.25},
//{-0.25,0.25,0.25},
//{0.25,0.25,0.25},
//{0.25,-0.25,0.25},
//{-0.25,-0.25,-0.25},
//{-0.25,0.25,-0.25},
//{0.25,0.25,-0.25},
//{0.25,-0.25,-0.25}
//
//};
//
//GLfloat MyColors[8][3] = {
//{0.2,0.2,0.2},
//{1.0,0.0,0.0},
//{1.0,1.0,0.0},
//{0.0,1.0,0.0},
//{0.0,0.0,1.0},
//{1.0,0.0,1.0},
//{1.0,1.0,0.0},
//{0.0,1.0,1.0}
//
//};
//
//GLubyte MyVertexList[24] = {
//0,3,2,1,2,3,7,6,0,4,7,3,1,2,6,5,4,5,6,7,0,1,5,4
//};
//
//void MyDisplay() {
//glClear(GL_COLOR_BUFFER_BIT);
//glFrontFace(GL_CCW);
//glEnable(GL_CULL_FACE);
//glEnableClientState(GL_COLOR_ARRAY);
//glEnableClientState(GL_VERTEX_ARRAY);
//glColorPointer(3, GL_FLOAT, 0, MyColors);
//glVertexPointer(3, GL_FLOAT, 0, MyVertices);
//glMatrixMode(GL_MODELVIEW);
//glLoadIdentity();
//glRotatef(30.0, 1.0, 1.0, 1.0);
//for (GLint i = 0; i < 6; i++)
//glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4 * i]);
//glFlush();
//}
//
//int main(int argc, char** argv) {
//
//glutInit(&argc, argv);
//
//glutInitDisplayMode(GLUT_RGB);
//glutCreateWindow("OpenGL Vertex Array Example");
//glutInitWindowSize(300, 300);
//glutInitWindowPosition(0, 0);
//
//glClearColor(1.0, 1.0, 1.0, 1.0);
//glMatrixMode(GL_PROJECTION);
//
//glLoadIdentity();
//glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
//glutDisplayFunc(MyDisplay);
//
//
//glutMainLoop();
//return 0;
//
//
//}

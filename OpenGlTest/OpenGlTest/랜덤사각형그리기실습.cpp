////
////  랜덤사각형그리기실습.cpp
////  OpenGlTest
////
////  Created by 심주흔 on 2024/03/18.
////
//
////#include <stdio.h>
////#include <stdlib.h>
////#include <time.h>
////#include <GL/glut.h>
//
//#define GL_SILENCE_DEPRECATION      //버전 오류 해결
//
//#include <iostream>
//#include <OpenGL/gl.h>
//#include <OpenGl/glu.h>
//#include <GLUT/glut.h>
//
//
//static int delay = 10;
//
//void init() {
//    //srand(time(0));           //작은 데이터타입으로 변환을 하면데이터를 잃어버릴 수 있는 가능성이 있는 코드이므로 밑처럼 수정
//    unsigned int current_time = (unsigned int)time(0); // 현재 시간을 unsigned int로 변환
//    srand(current_time); // 변환된 현재 시간을 시드로 사용하여 무작위 수 생성기 초기화
//
//    glClearColor(1.0, 1.0, 1.0, 1.0);
//    glColor3f(1.0, 0.0, 0.0);
//    //평면으로 만들겠다
//    gluOrtho2D(0.0, 50.0, 0.0, 50.0);
//    glClear(GL_COLOR_BUFFER_BIT);
//
//}
//
//void display() {
//    int x1, y1, x2, y2, r, g, b;
//
//    x1 = rand() % 50; y1 = rand() % 50; x2 = rand() % 50; y2 = rand() % 50; //좌표
//    r = rand() % 256; g = rand() % 256; b = rand() % 256;                   //색상
//    
//    //색상값
//    glColor3f((GLfloat)r / 255, (GLfloat)g / 255, (GLfloat)b / 255);
//
//    //사각형 위치 랜덤 생성
//    glBegin(GL_POLYGON);
//    glVertex2f(x1, y1); glVertex2f(x1, y2);
//    glVertex2f(x2, y2); glVertex2f(x2, y1);
//
//    glEnd();
//
//    glFlush();
//
//
//}
//
//void timer(int t) {
//    glutPostRedisplay();
//    glutTimerFunc(delay, timer, t);
//}
//
//int main(int argc, char* argv[]) {
//    glutInit(&argc, (char**)argv);
//    glutInitWindowSize(500, 500);
//    glutCreateWindow("Prog02: Random boxes");
//    glutDisplayFunc(display);
//    glutTimerFunc(delay, timer, 0);
//
//    init();
//    glutMainLoop();
//
//    return 0;
//}

////
////  popupMenu.cpp
////  OpenGlTest
////
////  Created by 심주흔 on 4/29/24.
////
//
//#define GL_SILENCE_DEPRECATION      //버전 오류 해결
//
//#include <OpenGL/gl.h>
//#include <OpenGl/glu.h>
//#include <GLUT/glut.h>
//#include <stdio.h>
//#include <stdlib.h>
//
//void display(void) {
//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//glMatrixMode(GL_MODELVIEW);
//glColor3f(0.0f, 0.0f, 0.0f);
//glFlush();
//}
//
//void main_menu_select(int value) {
//switch (value)
//{
//case 1:
//glutSetWindowTitle("First mod..");
//printf("첫번째 메뉴를 선택했습니다.\n");
//break;
//
//case 2:
//glutSetWindowTitle("Second mod..");
//printf("두번째 메뉴를 선택했습니다.\n");
//break;
//
//case 3:
//glutSetWindowTitle("Third mod..");
//printf("세번째 메뉴를 선택했습니다.\n");
//break;
//
//case 666:
//
//printf("프로그램 종료\n");
//exit(0);
//
//}
//}
//
//int main(int argc, char** argv) {
//    glutInitWindowSize(400, 400);
//    glutInit(&argc, argv);
//    
//    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//    glutCreateWindow("Menu example by juheun");
//    glutDisplayFunc(display);
//    
//    glutCreateMenu(main_menu_select);
//    glutAddMenuEntry("First", 1);
//    glutAddMenuEntry("Second", 2);
//    glutAddMenuEntry("Third", 3);
//    glutAddMenuEntry("Quit", 666);
//    
//    glutAttachMenu(GLUT_RIGHT_BUTTON);
//    
//    glutMainLoop();
//    return 0;
//    
//    
//}

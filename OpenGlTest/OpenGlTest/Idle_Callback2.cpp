////
////  Idle_Callback2.cpp
////  OpenGlTest
////
////  Created by 심주흔 on 2024/03/26.
////
//
//
//#define GL_SILENCE_DEPRECATION      //버전 오류 해결
//
//#include <iostream>
//#include <OpenGL/gl.h>
//#include <OpenGl/glu.h>
//#include <GLUT/glut.h>
//
//#define size 50.0
//
//float w_height = 800;
//float w_width = 800;
//float square_x = 0, square_y = 400;
//float square_dx = 0.5;        //0.5씩 증가시키겠다
//
//void idleCallBack() {
//    square_x += square_dx; //계속 더한다.
//    if (square_x + size > w_width || square_x <= 0) square_dx *= -1.0;        //벽에 다으면 방향 변경
//    glutPostRedisplay();                                                    //콜백함수 호출를 통해서 다시 그림 그림
//}
//
//void displaycallBack(void) {
//    glClearColor(0.0, 0.0, 0.0, 1.0);
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glOrtho(0.0, w_width, 0.0, w_height, -1.0, 1.0);
//
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    glTranslatef(square_x, square_y, 0.0);
//
//
//    //사각형 그리기
//    glColor3ub(255, 255, 0);
//    glBegin(GL_POLYGON);
//    glVertex2f(0, 0);
//    glVertex2f(size, 0);
//    glVertex2f(size, size);
//    glVertex2f(0, size);
//    glEnd();
//
//    //더블 버퍼를 사용했기에
//    glutSwapBuffers();
//
//}
//
//int main(int argc, char** argv) {
//
//    glutInit(&argc, argv);
//
//    glutInitWindowPosition(10, 10);
//    glutInitWindowSize(w_width, w_height);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//    glutCreateWindow("Idle Callback");
//    
//    //init();
//    glutDisplayFunc(displaycallBack);
//    glutIdleFunc(idleCallBack);
//
//
//    glutMainLoop();
//    return 0;
//}

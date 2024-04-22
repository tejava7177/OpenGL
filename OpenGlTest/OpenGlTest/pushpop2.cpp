//
////  pushpop.cpp
////  OpenGlTest
////
////  Created by 심주흔 on 4/19/24.
//
//
////
////  pushpop.cpp
////  OpenGlTest
////
////  Created by 심주흔 on 4/12/24.
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
//
//void draw_square(){
//    glBegin(GL_POLYGON);
//    glVertex2f(-0.2, 0.2);
//    glVertex2f(-0.2, -0.2);
//    glVertex2f(0.2, -0.2);
//    glVertex2f(0.2, 0.2);
//    glEnd();
//
//}
//
//void display(){
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    glColor3f(1.0, 0.0, 0.0);
//    draw_square();
//
//    glPushMatrix();
//
//    glColor3f(0.0, 1.0, 0.0);
//    glTranslatef(-0.6, 0.6, 0.0);
//    draw_square();
//
//    glPopMatrix();
//    
// 
//    
//    glPushMatrix();
//    glColor3f(0.0, 0.0, 1.0);
//    glTranslatef(0.6, 0.6, 0.0);
//    glRotatef(45, 0.0, 0.0, 1.0);
//    draw_square();
//    
//
//    glColor3f(1.0, 0.0, 1.0);
//    glScalef(1.2, 1.2, 1.0);
//    glTranslatef(-0.7, -0.7, 0.0);
//    
//    draw_square();
//   
//    
//    
//    glPopMatrix();
//    
//
////
////    glColor3f(1.0, 1.0, 0.0);
////    glTranslatef(-0.6, -0.6, 0.0);
////    glScalef(1.2, 1.2, 1.0);
////    draw_square();
//
//
//    glFlush();
//}
//
//void init(){
//    glClearColor(1.0, 1.0, 1.0, 0.0);
//    glColor3f(1.0, 1.0, 1.0);
//
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
//
//    glViewport(0, 0, 400, 400);
//
//}
//
//int main(int argc, char ** argv){
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
//    glutInitWindowPosition(100, 100);
//    glutInitWindowSize(400, 400);
//    glutCreateWindow("Push pop Matrix");
//    glutDisplayFunc(display);
//    init();
//    glutMainLoop();
//}

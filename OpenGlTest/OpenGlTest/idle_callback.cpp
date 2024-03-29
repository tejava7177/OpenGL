////
////  idle_callback.cpp
////  OpenGlTest
////
////  Created by 심주흔 on 2024/03/25.
////
//
//#define GL_SILENCE_DEPRECATION      //버전 오류 해결
//
//#include <iostream>
//#include <OpenGL/gl.h>
//#include <OpenGl/glu.h>
//#include <GLUT/glut.h>
//
//
//void idleProcess(){
//    angle += 0.0001;
//    if(angle > 360.0) angle = 0.0f;
//    
//    glutPostRedisplay();
//}
//
//void display(){
//    glClear(GL_COLOR_BUFFER_BIT);
//    
//    glRotatef(anlge, 0, 0, 1);
//    glColor3f(1.0f, 1.0f, 1.0f);
//    
//    glBegin(GL_POLYGON);
//    glVertex3f(-0.75, -0.75, 0.0);
//    
//    
//    glEnd();
//    
//    glutSwapBuffers();
//}
//
//int main(int argc, char** argv){
//    glutInit(&argc, argv);
//    
//    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
//    
//    glutInitWindowSize(250, 250);
//    glutInitWindowPosition(100, 100);
//    
//    glutCreateWindow("02_5 Idle Callback");
//    init();
//    
//    glutDisplayFunc(display);
//    glutReshapeFunc(reshape);
//    glutIdleFunc(idleProcess);
//    glutMainLoop();
//    
//    return 0;
//}

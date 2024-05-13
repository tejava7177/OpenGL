//
//  shik.cpp
//  OpenGlTest
//
//  Created by 심주흔 on 5/13/24.
//

#define GL_SILENCE_DEPRECATION      //버전 오류 해결

#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
#include <stdio.h>
#include <stdlib.h>


void init(void){
    GLfloat light_positon[] = {1.0, 2.0, 3.0, 1.0};
    GLfloat light_ambient[] = {0.0, 1.0, 0.0, 1.0};
    GLfloat light_diffuse[] = {1.0, 0.0, 0.0, 1.0};
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
    
    
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    
    glLightfv(GL_LIGHT0, GL_POSITION, light_positon);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}


void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSolidTeapot(0.5);
    glFlush();
}

void reshape(int w, int h){
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if(w <= h)
        glOrtho(-1.5, 1.5, -1.5*(GLfloat)h / (GLfloat)w,  -1.5*(GLfloat)h / (GLfloat)w, -10.0, 10.0);
    else
        glOrtho(-1.5*(GLfloat)w / (GLfloat)h, -1.5*(GLfloat)w / (GLfloat)h, -1.5,  1.5, -10.0, 10.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char ** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB| GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Lighting Example");
    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    
    
    return 0;
}

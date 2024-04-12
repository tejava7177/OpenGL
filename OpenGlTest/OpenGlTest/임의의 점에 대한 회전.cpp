//
//  임의의 점에 대한 회전.cpp
//  OpenGlTest
//
//  Created by 심주흔 on 4/12/24.
//

#define GL_SILENCE_DEPRECATION      //버전 오류 해결

#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>


void draw_rectangle(){
    glBegin(GL_POLYGON);
    glVertex2f(0.2, 0.4);
    glVertex2f(0.8, 0.4);
    glVertex2f(0.8, 0.6);
    glVertex2f(0.2, 0.6);
    glEnd();
}

void draw_point(){
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glVertex2f(0.5, 0.5);
    glEnd();
}


void draw_lines(){
    glBegin(GL_LINES);
    glVertex2f(-1.0, 0.0);
    glVertex2f(1.0, 0.0);
    glVertex2f(0.0, -1.0);
    glVertex2f(0.0, 1.0);
    glEnd();
}


void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    
    glColor3f(1.0, 0.0, 0.0);
    draw_rectangle();
    
    glColor3f(0.0, 0.0, 0.0);
    draw_point();
    
    glLoadIdentity();
    glColor3f(0.0, 0.0, 0.0);
    draw_lines();
    
    glFlush();
}

void init(){
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glViewport(0, 0, 800, 800);
}

int main(int argc, char ** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    
    glutCreateWindow("임의의 점에 대한 회전");
    glutDisplayFunc(display);
    init();
    
    glutMainLoop();
}

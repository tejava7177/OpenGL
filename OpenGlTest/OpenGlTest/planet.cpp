//
//  planet.cpp
//  OpenGlTest
//
//  Created by 심주흔 on 4/23/24.
//


#define GL_SILENCE_DEPRECATION // 버전 오류 해결(무시)

#include <OpenGL/gl.h>          //mac Xcode에서 OpenGL을 사용하기 위한 헤더파일
#include <OpenGL/glu.h>         //mac Xcode에서 OpenGL을 사용하기 위한 헤더파일
#include <GLUT/glut.h>          //mac Xcode에서 OpenGL을 사용하기 위한 헤더파일
#include <math.h>

static float year = 0, day = 0, moon = 5;

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}


void drawOrbit(float radius, int segments) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; i++) {
        float angle = 2.0f * M_PI * i / segments;
        glVertex2f(cos(angle) * radius, sin(angle) * radius);
    }
    glEnd();
}

void display(void) {
  
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    
    glPushMatrix();
    // Draw the Sun
    glutWireSphere(1.0, 20, 16);

    // Draw First Planet's Orbit
    glColor3f(0.5, 0.5, 0.5); // Grey color for orbit
    drawOrbit(2.0, 100);

    // First Planet
    glColor3f(1.0, 1.0, 1.0); // Reset color to white for the planet
    glRotatef(year, 0.0, 1.0, 0.0);
    glTranslatef(2.0, 0.0, 0.0);
    glPushMatrix();
    glutWireSphere(0.2, 10, 8);
    
    // Moon of the First Planet
    glRotatef(moon, 1.0, 1.0, 0.0);
    glTranslatef(0.5, 0.0, 0.0);
    glutWireSphere(0.1, 10, 8);
    glPopMatrix();
    
    // Draw Second Planet's Orbit
    glColor3f(0.5, 0.5, 0.5);
    drawOrbit(6.0, 100);

    // Second Planet
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(4.0, 0.0, 0.0); // Additional translation to place the second planet
    glutWireSphere(0.7, 10, 8);

    glPopMatrix();
    
    glutSwapBuffers();

}

void idleProcess() {
    year += 1.0;
    if (year >= 360.0) year -= 360.0;
    
    
    moon += 3.5;
    if (moon >= 360.0) moon -= 360.0;
    
    glutPostRedisplay();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0.0, 8.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Planet");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idleProcess);
    glutMainLoop();
    return 0;
}

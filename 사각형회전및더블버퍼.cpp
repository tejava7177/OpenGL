//
//  사각형회전및더블버퍼.cpp
//  OpenGlTest
//
//  Created by 심주흔 on 2024/03/25.
//

// 사각형 회전 및 더블 버퍼 실스

#define GL_SILENCE_DEPRECATION      //버전 오류 해결

#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>

static GLfloat spin = 0.0;

void display(void) {
    int r, g, b;
    r = rand() % 256;
    g = rand() % 256;
    b = rand() % 256;

    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glRotatef(spin, 0.0, 0.0, 1.0);
    glColor3f((GLfloat)r / 255, (GLfloat)g / 255, (GLfloat)b / 255);
    glRectf(-25.0, -25.0, 25.0, 25.0);
    glPopMatrix();

    glutSwapBuffers();
}

void spinDisplay(void) {
    //스핀 회전 속도 조절
    spin = spin + 0.05;
    if (spin > 360.0) spin = spin - 360;
    glutPostRedisplay();
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void mouse(int button, int state, int x, int y) {
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN) glutIdleFunc(spinDisplay);
        break;
    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN) glutIdleFunc(NULL);
        break;
    default:
        break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(250, 250);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("02_4 사각형 회전");
    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}

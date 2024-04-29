
#define GL_SILENCE_DEPRECATION      //버전 오류 해결

#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
#include <stdio.h>
#include <stdlib.h>

GLboolean IsSphere = GL_TRUE;
GLboolean IsSmall = GL_TRUE;

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.5, 0.0, 0.5);
    if (IsSphere && IsSmall)
        glutWireSphere(0.2, 15, 15);
    else if (IsSphere && !IsSmall)
        glutWireSphere(0.4, 15, 15);
    else if (!IsSphere && !IsSmall)
        glutWireTorus(0.1, 0.3, 40, 20);
    else
        glutWireTorus(0.2, 0.5, 40, 20);
    glFlush();
}

void MyMainMenu(int entryID) {
    switch (entryID) {
        case 1:
            IsSphere = GL_TRUE;
            break;
        case 2:
            IsSphere = GL_FALSE;
            break;
        case 3:
            exit(0);
            break;
    }
    glutPostRedisplay();
}

void MySubMenu(int entryID) {
    IsSmall = (entryID == 1) ? GL_TRUE : GL_FALSE;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL sub Menu example");

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    GLint MySubMenuID = glutCreateMenu(MySubMenu);
    glutAddMenuEntry("Small Object", 1);
    glutAddMenuEntry("Big Object", 2);

    GLint MyMainMenuId = glutCreateMenu(MyMainMenu);
    glutAddMenuEntry("Draw Sphere", 1);
    glutAddMenuEntry("Draw Torus", 2);
    glutAddSubMenu("Change size", MySubMenuID);
    glutAddMenuEntry("Exit", 3);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutDisplayFunc(MyDisplay);
    glutMainLoop();

    return 0;
}


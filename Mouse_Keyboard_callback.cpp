//
//  Mouse_Keyboard_callback.cpp
//  OpenGlTest
//
//  Created by 심주흔 on 2024/03/19.
//

//#include <stdio.h>
#define GL_SILENCE_DEPRECATION      //버전 오류 해결

#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>


void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);

}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glFlush();
}

void mouseProcess(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        printf("Left mouse button is pressed.. \n\n");
    }

    else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
        printf("Middle mouse button is pressed..\n\n");
    }

    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        printf("Right mouse button is pressed..\n\n");
    }

    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        printf("Left mouse button is released..\n\n");
    }

    else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) {
        printf("Middle mouse button is released..\n\n");
    }

    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
        printf("Right mouse button is released..\n\n");
    }
}

    void mousePassiveMotion(int x, int y){
        printf("Current mouse position: %d, %d\n", x, y);
    }

    void mouseActiveMotion(int x, int y) {
        printf("Pressed mouse position: %d, %d\n", x, y);
    }

    void mouseEntry(int state) {
        if (state == GLUT_LEFT) {
            printf("Mouse is outside of window..\n\n");
        }
        else if (state == GLUT_ENTERED) {
            printf("Mouse is inside of window..\n\n");
        }
    }

    void keyboard(unsigned char key, int x, int y) {
        switch (key) {
        case 'a':
            printf("a is pressed .. %d, %d\a\n", x, y);
            break;
        case 'b':
            printf("b is pressed .. %d, %d\a\n", x, y);
            break;
        case 27:
            exit(0);
            break;
        }
    }

    int main(int argc, char** argv) {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowSize(500, 500);
        glutInitWindowPosition(100, 100);
        glutCreateWindow("Mouse and keyboard");
        init();
        glutDisplayFunc(display);
        glutKeyboardFunc(keyboard);
        glutMouseFunc(mouseProcess);
        glutPassiveMotionFunc(mousePassiveMotion);
        glutMotionFunc(mouseActiveMotion);
        glutEntryFunc(mouseEntry);


        glutMainLoop();
        return 0;
    }

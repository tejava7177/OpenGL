//
//  별만들기.cpp
//  OpenGlTest
//
//  Created by 심주흔 on 2024/03/27.
//

#define GL_SILENCE_DEPRECATION      //버전 오류 해결

#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
#include <math.h>

void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 배경색을 흰색으로 설정
    glClear(GL_COLOR_BUFFER_BIT); // 현재 버퍼를 지우고 설정된 배경색으로 새로 그림
    
    // 첫 번째 삼각형 (빨간색)
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-0.1f, 0.4f);
    glVertex2f(0.1f, 0.4f);
    glVertex2f(0.0f, 0.6f);
    glEnd();
    
    // 두 번째 삼각형 (초록색)
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-0.1f, 0.55f);
    glVertex2f(0.1f, 0.55f);
    glVertex2f(0.0f, 0.35f);
    glEnd();
    
    glFlush();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height); // 화면의 전체 영역을 사용
    glMatrixMode(GL_PROJECTION); // 투영 행렬 모드 설정
    glLoadIdentity(); // 현재 투영 행렬을 초기화

    if (width <= height) {
        gluOrtho2D(-1.0, 1.0, -1.0 * (GLfloat)height / (GLfloat)width, 1.0 * (GLfloat)height / (GLfloat)width); // 화면 비율에 맞게 투영
    } else {
        gluOrtho2D(-1.0 * (GLfloat)width / (GLfloat)height, 1.0 * (GLfloat)width / (GLfloat)height, -1.0, 1.0); // 화면 비율에 맞게 투영
    }
    glMatrixMode(GL_MODELVIEW); // 모델뷰 행렬 모드로 다시 설정
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL 별 모양 그리기");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}

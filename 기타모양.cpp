//
//  기타모양.cpp
//  OpenGlTest
//
//  Created by 심주흔 on 2024/03/13.
//

//#include <stdio.h>
//
//#include <GL/glut.h>


#define GL_SILENCE_DEPRECATION

#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>


void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0); // 흰색 배경 설정
    glMatrixMode(GL_PROJECTION); // 투영 행렬 모드 설정
    gluOrtho2D(0.0, 500.0, 0.0, 500.0); // 2D 직교 투영 설정
}

void drawGuitar(void) {
    glClear(GL_COLOR_BUFFER_BIT); // 화면 지우기

    glColor3f(0.0, 0.0, 0.0); // 검은색으로 선 색상 설정
    glLineWidth(2.0); // 선의 너비 설정

    // 기타 몸통 그리기
    glBegin(GL_POLYGON);
    glVertex2i(100, 100);
    glVertex2i(400, 100);
    glVertex2i(400, 400);
    glVertex2i(100, 400);
    glEnd();

    // 기타 몸통과 목을 이어주는 부분 그리기
    glBegin(GL_LINES);
    glVertex2i(250, 400);
    glVertex2i(250, 450);
    glEnd();

    // 기타 목 그리기
    glBegin(GL_POLYGON);
    glVertex2i(250, 450);
    glVertex2i(275, 500);
    glVertex2i(225, 500);
    glEnd();

    glFlush(); // 그리기 명령 실행
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // GLUT 초기화
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // 디스플레이 모드 설정
    glutInitWindowSize(500, 500); // 윈도우 크기 설정
    glutInitWindowPosition(100, 100); // 윈도우 위치 설정
    glutCreateWindow("Guitar Drawing"); // 윈도우 생성 및 제목 설정
    init(); // OpenGL 초기화 함수 호출
    glutDisplayFunc(drawGuitar); // 디스플레이 콜백 함수 등록
    glutMainLoop(); // 이벤트 루프 시작

    return 0;
}

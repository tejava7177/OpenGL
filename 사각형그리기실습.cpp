//
//  사각형그리기실습.cpp
//  OpenGlTest
//
//  Created by 심주흔 on 2024/03/18.
//

// #include <stdio.h>
#define GL_SILENCE_DEPRECATION      //버전 오류 해결

#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>

void display(void){
    glClear(GL_COLOR_BUFFER_BIT); //색상 버퍼를 지움.
    glColor3f(1.0, 1.0, 1.0);       //흰색으로 설정
    
    //사각형의 좌표 입력
    glBegin(GL_POLYGON);
    
    // z 좌표는 0 => 원근감이 없기 때문 (평면 사각형)
    glVertex3f(0.25, 0.25, 0.0);
    glVertex3f(0.75, 0.25, 0.0);
    glVertex3f(0.75, 0.75, 0.0);
    glVertex3f(0.25, 0.75, 0.0);
    
    glEnd();
    
    glFlush();  //사각형을 화면에 그림
}

void init(void){
    glClearColor(0.0, 0.0, 0.0, 0.0);       //윈도우 배경을 검은색으로 설정
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();                       //단위 행렬
    
    //직교 투영 : left, right, bottom, top, near, far
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

}

int main(int argc, char** argv){
    glutInit(&argc, argv);          //GLUT 사용을 초기화
    
    //디스플레이모드 형식 선택: single buffer & RGBA color 모드 선택
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    
    // 창의 크기와 위치 설정
    glutInitWindowSize(250, 250);
    glutInitWindowPosition(100, 100);
    
    //필요한 콜백함수 등록
    glutCreateWindow("01 사각형 그리기");     //윈도우 생성
    init();
    
    //필요한 콜백함수 등록
    glutDisplayFunc(display);
    glutMainLoop();         //이벤트 처리엔진 시작
    
    return 0;
}

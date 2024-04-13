//
//  원그리기.cpp
//  OpenGlTest
//
//  Created by 심주흔 on 4/13/24.
//

#define GL_SILENCE_DEPRECATION      //버전 오류 해결


#include <stdlib.h>
#include <stdio.h>
#include <OpenGL/gl.h>              //mac Xcode에서 OpenGL을 사용하기 위한 헤더파일
#include <OpenGl/glu.h>             //mac Xcode에서 OpenGL을 사용하기 위한 헤더파일
#include <GLUT/glut.h>              //mac Xcode에서 OpenGL을 사용하기 위한 헤더파일
#include <math.h>                   //수학 개념을 사용하기 위한 헤더파일


void init(void){
    glClearColor(1.0, 1.0, 1.0, 1.0);       //배경을 흰색으로 설정
}



void draw_circle(){
    
    glColor3f(1.0, 1.0, 0.0);               //노란색 원을 그리기 위함.
    
    glBegin(GL_TRIANGLE_FAN);
    float radius = 0.36f;                      //반지름
    int segment = 100;                          //100개의 삼각형을 만들겠다.
    
    //삼각형 생성
    for (int i = 0; i <= segment; i++) {
        float angle = 2.0f * 3.141592 * i / segment;
        float x = 0.0f + radius * cosf(angle);          //x 좌표
        float y = 0.0f + radius * sinf(angle);          //y 좌표
        
        glVertex2f(x, y);                               //생성
    }
    
    glEnd();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);                       //현재 버퍼를 지우고 설정된 배경색으로 새로 그림
    
    draw_circle();                                      //원 생성함수
    
    glFlush();
}




int main(int argc, char** argv){
    
    glutInit(&argc, argv);
    
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("원 그리기");
    
    init();
    glutDisplayFunc(display);
    
    glutMainLoop();

    return 0;
}

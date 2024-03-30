///*
// 작성일 : 2024.03.27
// 작성자 : 심주흔
// 프로그램명 : 윈도우 상에 튀르키예 국가를 그리고 키보드 입력에 맞는 동작 실행
// */
//
//
//#define GL_SILENCE_DEPRECATION      //버전 오류 해결
//
////#include <iostream>
//#include <stdlib.h>
//#include <stdio.h>
//#include <OpenGL/gl.h>              //mac Xcode에서 OpenGL을 사용하기 위한 헤더파일
//#include <OpenGl/glu.h>             //mac Xcode에서 OpenGL을 사용하기 위한 헤더파일
//#include <GLUT/glut.h>              //mac Xcode에서 OpenGL을 사용하기 위한 헤더파일
//#include <math.h>                   //수학 개념을 사용하기 위한 헤더파일
//
//// 국기에 들어갈 모양 색을 흰색으로 초기화 => 변경하기 위해 변수 생성
//GLfloat triangleColor1 = 1.0f;
//GLfloat triangleColor2 = 1.0f;
//GLfloat triangleColor3 = 1.0f;
//GLfloat circleColor1 = 1.0f;
//GLfloat circleColor2 = 1.0f;
//GLfloat circleColor3 = 1.0f;
//
//void display() {
//    glClearColor(1.0f, 0.0f, 0.0f, 0.0f); // 배경색을 빨간색으로 설정
//    glClear(GL_COLOR_BUFFER_BIT); // 현재 버퍼를 지우고 설정된 배경색으로 새로 그림
//
//    // 삼각형으로 된 별 그리기
//    glColor3f(triangleColor1, triangleColor2, triangleColor3); // 흰색으로 삼각형 그리기
//    glBegin(GL_TRIANGLES);          //3개의 점을 이어 삼각형을 만든다.
//    glVertex2f(0.0f, 0.0f);         //첫번째 삼각형 좌표
//    glVertex2f(0.28f, 0.12f);       //첫번째 삼각형 좌표
//    glVertex2f(0.17f, -0.07f);      //첫번째 삼각형 좌표
//    glVertex2f(0.23f, 0.0f);        //두번째 삼각형 좌표
//    glVertex2f(0.10f, 0.16f);       //두번째 삼각형 좌표
//    glVertex2f(0.10f, -0.16f);      //두번째 삼가형 좌표
//    glVertex2f(0.0f, 0.0f);         //세번째 삼각형 좌표
//    glVertex2f(0.2f, 0.07f);        //세번쨰 삼각형 좌표
//    glVertex2f(0.3f, -0.1f);        //세번째 삼각형 좌표
//    glEnd();
//
//    // 원 그리기
//    glColor3f(circleColor1,circleColor2,circleColor3); // 흰색으로 큰 원 그리기
//    glBegin(GL_TRIANGLE_FAN);       //한 점을 중심으로 여러개의 삼각형을 그리면 => 원이 됨.
//    float radius = 0.45f;           // 원의 반지름 설정
//    int segment = 100;              // 원을 구성할 세그먼트(삼각형) 수 설정
//    
//    // 원의 중심은 (-0.48, 0.0)으로 잡고 그 중심을 기준으로 100개의 삼각형으로 둘러쌈.
//    for (int i = 0; i <= segment; i++) {
//        float angle = 2.0f * 3.141592 * i / segment; // 세타각 = 원의 둘레 / 세그먼트
//        float x = -0.48f + radius * cosf(angle); // 삼각형의 x 좌표 계산
//        float y = 0.0f + radius * sinf(angle); // 삼각형의 y 좌표 계산
//        
//        glVertex2f(x, y);                       //정점 설정
//    }
//    glEnd();
//
//    // 달 모양을 만들기 위해 겹치는 빨간색 원 그리기
//    glColor3f(1.0f, 0.0f, 0.0f); // 빨간색으로 설정 / 바뀔 필요 없음.
//    glBegin(GL_TRIANGLE_FAN);
//    float radius_small = 0.36f;
//    for (int i = 0; i <= segment; i++) {
//        float angle = 2.0f * 3.141592 * i / segment;
//        float x = -0.38f + radius_small * cosf(angle);
//        float y = 0.0f + radius_small * sinf(angle);
//        glVertex2f(x, y);
//    }
//
//    glEnd();
//
//    glFlush();  //싱글버퍼로 동작하기 때문에 glFlush();
//}
//
////유동적인 윈도우를 만들기 위한 콜백함수
//void reshape(int width, int height) {
//    glViewport(0, 0, width, height); // 화면의 전체 영역을 사용
//    glMatrixMode(GL_PROJECTION); // 투영 행렬 모드 설정
//    glLoadIdentity(); // 현재 투영 행렬을 초기화
//
//    if (width <= height) {
//        gluOrtho2D(-1.0, 1.0, -1.0 * (GLfloat)height / (GLfloat)width, 1.0 * (GLfloat)height / (GLfloat)width); // 화면 비율에 맞게 투영
//    } 
//    else {
//        gluOrtho2D(-1.0 * (GLfloat)width / (GLfloat)height, 1.0 * (GLfloat)width / (GLfloat)height, -1.0, 1.0); // 화면 비율에 맞게 투영
//    }
//}
//
//// 키보드 콜백 함수
//void keyboard(unsigned char key, int x, int y) {
//    switch(key) {
//        case '1':
//            // 삼각형 색을 빨간색으로 변경 => 달만 보이게
//            triangleColor1 = 1.0f;
//            triangleColor2 = 0.0f;
//            triangleColor3 = 0.0f;
//            circleColor1 = 1.0f;
//            circleColor2 = 1.0f;
//            circleColor3 = 1.0f;
//            break;
//
//        case '2':
//            // 원 색을 빨간색으로 변경    => 별만 보이도록
//            triangleColor1 = 1.0f;
//            triangleColor2 = 1.0f;
//            triangleColor3 = 1.0f;
//            circleColor1 = 1.0f;
//            circleColor2 = 0.0f;
//            circleColor3 = 0.0f;
//            break;
//
//        case 13: // 13은 'Enter' 키의 ASCII 코드
//                    // 원과, 별 모두 흰색으로 변경
//                    triangleColor1 = 1.0f;
//                    triangleColor2 = 1.0f;
//                    triangleColor3 = 1.0f;
//                    circleColor1 = 1.0f;
//                    circleColor2 = 1.0f;
//                    circleColor3 = 1.0f;
//                    break;
//    }
//    glutPostRedisplay(); // 화면을 다시 그리도록 요청
//}
//
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitWindowSize(600, 400); // 초기 윈도우 창 크기 설정
//    glutInitWindowPosition(100, 100);   //화면 기준 창이 나타나는 공간을 설정한다. 좌상단 원점 기준
//    glutCreateWindow("OpenGL 원 그리기"); // 윈도우 생성 및 제목 설정
//    glutDisplayFunc(display); // display 함수를 화면에 표시하기 위해 콜백 함수 호출
//    glutReshapeFunc(reshape); // reshape 함수를 창의 크기가 변경될 때마다 콜백함수 호출
//    glutKeyboardFunc(keyboard); // 키보드 입력을 처리하기 위한 콜백함수 호출
//
//    glutMainLoop(); // 이벤트 루프 시작
//
//    return 0;
//}
//

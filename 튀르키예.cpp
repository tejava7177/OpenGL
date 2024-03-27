//#define GL_SILENCE_DEPRECATION      //버전 오류 해결
//
//#include <iostream>
//#include <OpenGL/gl.h>
//#include <OpenGl/glu.h>
//#include <GLUT/glut.h>
//#include <math.h>
//
//void display_circle() {
//    glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // 배경색을 빨간색으로 설정
//    glClear(GL_COLOR_BUFFER_BIT); // 현재 버퍼를 지우고 설정된 배경색으로 새로 그림
//    
//    // 빨간색 원 그리기
//    glColor3f(1.0f, 1.0f, 1.0f); // 흰색으로 설정
//    glBegin(GL_TRIANGLE_FAN);
//    float radius = 0.45f; // 원의 반지름 설정
//    int numSegments = 100; // 원을 구성할 세그먼트 수 설정
//    for (int i = 0; i <= numSegments; i++) {
//        float theta = 2.0f * M_PI * i / numSegments; // 세그먼트 간격 계산
//        float x = -0.48f + radius * cosf(theta); // x 좌표 계산 (원이 왼쪽에 위치하도록 함)
//        float y = 0.0f + radius * sinf(theta); // y 좌표 계산 (y 중심에 위치하도록 함)
//        glVertex2f(x, y); // 정점 추가
//    }
//    glEnd();
//    
//    // 빨간색 원 그리기
//    glColor3f(1.0f, 0.0f, 0.0f); // 빨간색으로 설정ㅁ
//    glBegin(GL_TRIANGLE_FAN);
//    float radius_small = 0.36f;
//    for (int i = 0; i <= numSegments; i++) {
//        float theta = 2.0f * M_PI * i / numSegments; // 세그먼트 간격 계산
//        float x = -0.38f + radius_small * cosf(theta); // x 좌표 계산 (원이 오른쪽에 위치하도록 함)
//        float y = 0.0f + radius_small * sinf(theta); // y 좌표 계산 (y 중심에 위치하도록 함)
//        glVertex2f(x, y); // 정점 추가
//    }
//    
//    glEnd();
//  
//    
//    glBegin(GL_TRIANGLES);
//
//    // 첫 번째 삼각형 (빨간색)
//    glColor3f(1.0f, 1.0f, 1.0f);
//    glVertex2f(0.0f, 0.0f);
//    glVertex2f(0.28f, 0.12f);
//    glVertex2f(0.17f, -0.07f);
//    
//
//    // 두 번째 삼각형 (초록색)
//    glColor3f(1.0f, 1.0f, 1.0f);
//    glVertex2f(0.23f, 0.0f);
//    glVertex2f(0.10f, 0.16f);
//    glVertex2f(0.10f, -0.16f);
//    
//    glColor3f(1.0f, 1.0f, 1.0f);
//    glVertex2f(0.0f, 0.0f);
//    glVertex2f(0.2f, 0.07f);
//    glVertex2f(0.3f, -0.1f);
//    glEnd();
//    
//    glFlush();
//
//}
//
//
//
//void reshape(int width, int height) {
//    glViewport(0, 0, width, height); // 화면의 전체 영역을 사용
//    glMatrixMode(GL_PROJECTION); // 투영 행렬 모드 설정
//    glLoadIdentity(); // 현재 투영 행렬을 초기화
//
//    if (width <= height) {
//        gluOrtho2D(-1.0, 1.0, -1.0 * (GLfloat)height / (GLfloat)width, 1.0 * (GLfloat)height / (GLfloat)width); // 화면 비율에 맞게 투영
//    } else {
//        gluOrtho2D(-1.0 * (GLfloat)width / (GLfloat)height, 1.0 * (GLfloat)width / (GLfloat)height, -1.0, 1.0); // 화면 비율에 맞게 투영
//    }
//    glMatrixMode(GL_MODELVIEW); // 모델뷰 행렬 모드로 다시 설정
//}
//
//
//
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitWindowSize(800, 600); // 윈도우 크기 설정 (가로, 세로)
//    glutCreateWindow("OpenGL 원 그리기"); // 윈도우 생성 및 제목 설정
//    glutDisplayFunc(display_circle); // display 함수를 화면에 표시하기 위해 호출
//    //glutDisplayFunc(display_tri);
//    glutReshapeFunc(reshape); // reshape 함수를 창의 크기가 변경될 때마다 호출
//
//    glutMainLoop(); // 이벤트 루프 시작
//
//    return 0;
//}
//

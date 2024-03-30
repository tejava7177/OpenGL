//
//#define GL_SILENCE_DEPRECATION      //버전 오류 해결
//#include <iostream>
//#include <OpenGL/gl.h>
//#include <OpenGl/glu.h>
//#include <GLUT/glut.h>
//#include <vector>
//#include <cstdlib> // 랜덤 색상을 생성하기 위해 필요
//
//// 전역 변수로 별의 크기 설정
//float starSize = 0.1f;
//
//// 별의 좌표와 색상을 저장할 구조체 정의
//struct Star {
//    float x;
//    float y;
//    float color[3]; // RGB 값
//};
//
//// 전역 변수로 별들을 저장할 벡터 정의
//std::vector<Star> stars;
//
//// 랜덤 색상을 생성하는 함수
//void generateRandomColor(float color[3]) {
//    color[0] = static_cast<float>(rand()) / RAND_MAX; // 빨간색 성분
//    color[1] = static_cast<float>(rand()) / RAND_MAX; // 초록색 성분
//    color[2] = static_cast<float>(rand()) / RAND_MAX; // 파란색 성분
//}
//
//// 별을 그리는 함수
//void drawStar(float x, float y, float color[3]) {
//    glBegin(GL_TRIANGLES);
//    glColor3fv(color); // 색상 설정
//    // 위쪽 삼각형
//    glVertex2f(x, y + starSize);
//    glVertex2f(x - starSize / 2, y - starSize / 2);
//    glVertex2f(x + starSize / 2, y - starSize / 2);
//    // 아래쪽 삼각형
//    glVertex2f(x, y - starSize);
//    glVertex2f(x - starSize / 2, y + starSize / 2);
//    glVertex2f(x + starSize / 2, y + starSize / 2);
//    glEnd();
//}
//
//// 직선을 그리는 함수
//void drawLine(float startX, float startY, float endX, float endY) {
//    glBegin(GL_LINES);
//    glColor3f(0.0f, 0.0f, 0.0f); // 검은색으로 설정
//    glVertex2f(startX, startY);
//    glVertex2f(endX, endY);
//    glEnd();
//}
//
//// 디스플레이 콜백 함수
//void display() {
//    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 배경색을 흰색으로 설정
//    glClear(GL_COLOR_BUFFER_BIT); // 현재 버퍼를 지우고 설정된 배경색으로 새로 그림
//    
//    // 저장된 별들을 순회하면서 별과 직선을 그립니다.
//    for (size_t i = 0; i < stars.size(); ++i) {
//        drawStar(stars[i].x, stars[i].y, stars[i].color);
//        if (i > 0) {
//            drawLine(stars[i-1].x, stars[i-1].y, stars[i].x, stars[i].y);
//        }
//    }
//    
//    glFlush();
//}
//
//// 리셰이프 콜백 함수
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
//// 마우스 클릭 콜백 함수
//void mouse(int button, int state, int x, int y) {
//    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
//        // 클릭된 위치로 새로운 별 생성 및 추가
//        Star newStar;
//        newStar.x = (2.0f * x / glutGet(GLUT_WINDOW_WIDTH)) - 1.0f;
//        newStar.y = ((2.0f * (glutGet(GLUT_WINDOW_HEIGHT) - y)) / glutGet(GLUT_WINDOW_HEIGHT)) - 1.0f;
//        generateRandomColor(newStar.color); // 랜덤 색상 생성
//        stars.push_back(newStar);
//        glutPostRedisplay(); // 화면을 다시 그리도록 요청
//    } else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
//        // 클릭될 때마다 모든 별의 색상을 랜덤으로 변경
//        for (size_t i = 0; i < stars.size(); ++i) {
//            generateRandomColor(stars[i].color);
//        }
//        glutPostRedisplay(); // 화면을 다시 그리도록 요청
//    }
//}
//
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitWindowSize(800, 600);
//    glutCreateWindow("OpenGL 별 모양 그리기");
//    glutDisplayFunc(display);
//    glutReshapeFunc(reshape);
//    glutMouseFunc(mouse); // 마우스 이벤트 콜백 함수 등록
//
//    glutMainLoop();
//
//    return 0;
//}

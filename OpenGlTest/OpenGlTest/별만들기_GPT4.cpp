//#define GL_SILENCE_DEPRECATION // OpenGL 관련 오류를 방지하기 위한 매크로
//
//#include <iostream>
//#include <OpenGL/gl.h> // OpenGL 함수를 사용하기 위한 헤더 파일
//#include <OpenGL/glu.h> // OpenGL 유틸리티 라이브러리
//#include <GLUT/glut.h> // GLUT 라이브러리
//#include <vector> // 벡터 컨테이너 사용을 위한 헤더 파일
//
//static int delay = 10;
//
//// 별을 나타내는 구조체
//struct Star {
//    float x, y; // 별의 위치
//};
//
//std::vector<Star> stars; // 화면에 그려질 별들을 저장할 벡터
//float rotateAngle = 0.0f; // 별의 회전 각도
//bool rotateDirection = false; // 별의 회전 방향
//float currentColor[3] = {1.0f, 1.0f, 1.0f}; // 현재 별의 색상 (RGB)
//
//// 별을 그리는 함수
//void drawStar(float x, float y) {
//    glPushMatrix(); // 현재 행렬 상태를 저장
//    glTranslatef(x, y, 0); // 별의 위치로 변환
//    glRotatef(rotateAngle, 0, 0, 1); // 별을 Z축을 중심으로 회전
//    glBegin(GL_TRIANGLES); // 삼각형 그리기 시작
//    
//    glColor3fv(currentColor); // 설정된 색상으로 별 색칠
//    
//    // 첫 번째 삼각형 (아래)
//    glVertex2f(-0.1f, -0.1f);
//    glVertex2f(0.1f, -0.1f);
//    glVertex2f(0.0f, 0.2f);
//    // 두 번째 삼각형 (위)
//    glVertex2f(-0.1f, 0.1f);
//    glVertex2f(0.1f, 0.1f);
//    glVertex2f(0.0f, -0.2f);
//    
//    
//    
//    
//    
//    glEnd(); // 삼각형 그리기 종료
//    glPopMatrix(); // 행렬 상태 복원
//}
//
//// 화면을 새로 그릴 때 호출되는 함수
//void display() {
//    glClear(GL_COLOR_BUFFER_BIT); // 화면을 클리어
//    for (const auto& star : stars) { // 저장된 모든 별을 그림
//        drawStar(star.x, star.y);
//    }
//    // 별들 사이에 선 그리기
//    if (stars.size() > 1) {
//        glColor3f(1.0, 1.0, 1.0); // 선의 색상 설정 (흰색)
//        glBegin(GL_LINES);
//        for (size_t i = 0; i < stars.size() - 1; ++i) {
//            glVertex2f(stars[i].x, stars[i].y);
//            glVertex2f(stars[i + 1].x, stars[i + 1].y);
//        }
//        glEnd();
//    }
//    glutSwapBuffers(); // 더블 버퍼링을 사용하여 화면에 출력
//}
//
//bool rotating = false; // 추가: 별의 회전 상태를 저장
//
//void mouse(int button, int state, int x, int y) {
//    
//    if (state == GLUT_DOWN) {
//        float newX = (float)x / (glutGet(GLUT_WINDOW_WIDTH) / 2) - 1.0f;
//        float newY = -((float)y / (glutGet(GLUT_WINDOW_HEIGHT) / 2) - 1.0f);
//        if (button == GLUT_LEFT_BUTTON) {
//            stars.push_back({newX, newY}); // 별 추가
//        } else if (button == GLUT_RIGHT_BUTTON) {
//            if (!rotating) {
//                rotating = true; // 회전 시작
//            } else {
//                rotateDirection = !rotateDirection; // 회전 방향 토글
//            }
//        } else if (button == GLUT_MIDDLE_BUTTON) {
//            // 가운데 버튼으로 별의 색상 변경
//            currentColor[0] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
//            currentColor[1] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
//            currentColor[2] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
//
//        }
//    }
//    glutPostRedisplay();
//}
//void update(int value) {
//    if (rotating) { // 회전 상태가 활성화된 경우에만 각도 업데이트
//        rotateAngle += rotateDirection ? 2.0f : -2.0f;
//    }
//    glutPostRedisplay();
//    glutTimerFunc(delay, update, 0); // 약 30fps로 업데이트
//}
//
//
//// 메인 함수
//int main(int argc, char** argv) {
//    glutInit(&argc, argv); // GLUT 초기화
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // 더블 버퍼링과 RGB 색상 모드 설정
//    glutInitWindowSize(640, 480); // 윈도우 크기 설정
//    glutCreateWindow("OpenGL Stars"); // 윈도우 생성
//    glClearColor(0.0, 0.0, 0.0, 1.0); // 배경색을 검은색으로 설정
//    glutDisplayFunc(display); // 디스플레이 콜백 함수 설정
//    glutMouseFunc(mouse); // 마우스 이벤트 콜백 함수 설정
//    glutTimerFunc(delay, update, 0); // 타이머 콜백 함수 추가로 회전 업데이트
//    glutMainLoop(); // 이벤트 처리 루프 진입
//    return 0;
//}
//

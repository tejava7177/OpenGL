// OpenGL을 사용하기 위한 표준 헤더 파일들을 포함합니다.
#include <stdio.h>
#include <stdlib.h>
#include <OpenGL/gl.h> // OpenGL의 기본 그래픽 함수에 접근합니다.
#include <OpenGL/glu.h> // OpenGL의 유틸리티 함수에 접근합니다.
#include <GLUT/glut.h> // GLUT 라이브러리를 사용해 간편한 윈도우 관리 및 이벤트 처리를 합니다.

#include <math.h> // 수학 함수를 사용하기 위한 헤더 파일입니다. 예: sin(), cos() 함수

#define MAX_STARS 100 // 화면에 표시될 수 있는 최대 별의 수를 정의합니다.

#define GL_SILENCE_DEPRECATION // macOS에서 OpenGL 사용시 나타나는 경고 메시지를 숨깁니다.

// 별을 나타내는 구조체입니다. 각 별은 x, y 좌표를 가집니다.
struct Star {
    float x, y; // 별의 위치
};

// 별들을 저장할 전역 배열과 현재 별의 수를 저장할 변수를 선언합니다.
struct Star stars[MAX_STARS];
int starsCount = 0;

// 별을 회전시킬 때 사용할 각도와 방향을 저장할 변수입니다.
float rotateAngle = 0.0f;
int rotateDirection = 0; // 0: 반시계 방향, 1: 시계 방향

// 현재 별의 색상을 저장할 배열입니다. RGB 형식을 사용합니다.
float currentColor[3] = {1.0f, 1.0f, 1.0f};

// 별을 그리는 함수입니다. 각 별의 위치에 따라 삼각형을 이용해 별 모양을 그립니다.
void drawStar(float x, float y) {
    glPushMatrix(); // 현재 행렬 상태를 저장합니다.
    glTranslatef(x, y, 0); // 별의 위치로 변환합니다.
    glRotatef(rotateAngle, 0, 0, 1); // 설정된 각도로 별을 회전시킵니다.
    glBegin(GL_TRIANGLES); // 삼각형 그리기를 시작합니다.
    glColor3fv(currentColor); // 설정된 색상으로 삼각형을 채웁니다.
    // 별을 구성하는 두 개의 삼각형을 그립니다.
    glVertex2f(-0.1f, -0.1f);
    glVertex2f(0.1f, -0.1f);
    glVertex2f(0.0f, 0.2f);
    glVertex2f(-0.1f, 0.1f);
    glVertex2f(0.1f, 0.1f);
    glVertex2f(0.0f, -0.2f);
    glEnd(); // 삼각형 그리기를 종료합니다.
    glPopMatrix(); // 행렬 상태를 복원합니다.
}

// 화면을 새로 그릴 때마다 호출되는 함수입니다.
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // 화면을 클리어합니다.
    for (int i = 0; i < starsCount; i++) { // 저장된 모든 별을 그립니다.
        drawStar(stars[i].x, stars[i].y);
    }
    // 별들 사이에 선을 그려서 연결합니다.
    if (starsCount > 1) {
        glColor3f(1.0, 1.0, 1.0); // 선의 색상을 설정합니다 (흰색).
        glBegin(GL_LINES);
        for (int i = 0; i < starsCount - 1; i++) {
            glVertex2f(stars[i].x, stars[i].y);
            glVertex2f(stars[i + 1].x, stars[i + 1].y);
        }
        glEnd();
    }
    glutSwapBuffers(); // 화면에 그려진 내용을 표시합니다.
}

// 마우스 클릭 이벤트를 처리하는 함수입니다.
int rotating = 0; // 별의 회전 상태를 저장합니다 (0: 정지, 1: 회전).
void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) { // 마우스 버튼이 눌렸을 때
        float newX = (float)x / (glutGet(GLUT_WINDOW_WIDTH) / 2) - 1.0f;
        float newY = -((float)y / (glutGet(GLUT_WINDOW_HEIGHT) / 2) - 1.0f);
        if (button == GLUT_LEFT_BUTTON && starsCount < MAX_STARS) { // 왼쪽 버튼으로 별 추가
            stars[starsCount++] = (struct Star){newX, newY};
        } else if (button == GLUT_RIGHT_BUTTON) { // 오른쪽 버튼으로 별 회전 상태 토글
            rotating = !rotating;
            if (rotating) {
                rotateDirection = !rotateDirection; // 회전 방향 토글
            }
        } else if (button == GLUT_MIDDLE_BUTTON) { // 가운데 버튼으로 별 색상 변경
            currentColor[0] = (float)rand() / (float)RAND_MAX;
            currentColor[1] = (float)rand() / (float)RAND_MAX;
            currentColor[2] = (float)rand() / (float)RAND_MAX;
        }
    }
    glutPostRedisplay(); // 화면을 다시 그립니다.
}

// 주기적으로 화면을 업데이트하는 함수입니다.
void update(int value) {
    if (rotating) { // 회전 상태일 때 회전 각도를 업데이트합니다.
        rotateAngle += rotateDirection ? 2.0f : -2.0f;
    }
    glutPostRedisplay(); // 화면을 다시 그립니다.
    glutTimerFunc(33, update, 0); // 일정 시간 후에 update 함수를 다시 호출합니다.
}

// 메인 함수
int main(int argc, char** argv) {
    glutInit(&argc, argv); // GLUT 라이브러리를 초기화합니다.
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // 더블 버퍼링과 RGB 색상 모드를 설정합니다.
    glutInitWindowSize(800, 600); // 윈도우의 크기를 설정합니다.
    glutCreateWindow("OpenGL Stars"); // 윈도우를 생성하고 제목을 설정합니다.
    glClearColor(0.0, 0.0, 0.0, 1.0); // 배경색을 검은색으로 설정합니다.
    glutDisplayFunc(display); // 디스플레이 콜백 함수를 지정합니다.
    glutMouseFunc(mouse); // 마우스 이벤트 콜백 함수를 지정합니다.
    glutTimerFunc(33, update, 0); // 타이머 콜백 함수를 설정하여 화면을 주기적으로 업데이트합니다.
    glutMainLoop(); // 이벤트 처리 루프를 시작합니다.
    return 0;
}


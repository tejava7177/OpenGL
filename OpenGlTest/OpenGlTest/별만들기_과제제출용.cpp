
/*
 작성일 : 2024.03.29
 작성자 : 심주흔
 프로그램명 : 윈도우 상에 별을 추가하여 그리고 중점을 연결하며, 회전까지 시키기
 */

//Window 상황
//#include <stdlib.h>
//#include <GL/glut.h>


#define GL_SILENCE_DEPRECATION // 버전 오류 해결(무시)


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>            //회전 여부를 판단하기 위해 bool 사용을 위한 헤더파일
#include <OpenGL/gl.h>          //mac Xcode에서 OpenGL을 사용하기 위한 헤더파일
#include <OpenGL/glu.h>         //mac Xcode에서 OpenGL을 사용하기 위한 헤더파일
#include <GLUT/glut.h>          //mac Xcode에서 OpenGL을 사용하기 위한 헤더파일


#define MAX_STARS 20 // 화면에 표시될 수 있는 최대 별의 수 20개로 정의


// 별을 좌표를 나타내는 구조체
struct Star {
    float x, y; // 별의 좌표
};

// 별들을 저장할 전역 배열과 현재 별의 수를 저장할 변수를 선언
struct Star stars[MAX_STARS];

int starsCount = 1;  //main 함수에 기본적으로 하나 생성 > 이후 1씩 증가

// 별을 회전시킬 때 사용할 각도 변수.
static GLfloat spin = 0.0f;
bool rotating = false;      //회전 여부
bool rotateDirection = false;    // false = 왼쪽, true = 오른쪽

// 별의 색을 정할 RGB 값을 담을 배열 생성
float currentColor[3] = {0.0f, 0.0f, 0.0f};


static int delay = 10;


// 삼각형 두개를 이용해 별을 그리는 함수
void drawStar(float x, float y) {
    glPushMatrix(); // 현재 행렬 상태를 저장합니다.
    glTranslatef(x, y, 0); // 별의 위치로 변환합니다.


    glRotatef(spin, 0, 0, 1); // spin 각도만큼 별 회전시키기


    glBegin(GL_TRIANGLES); // 세 점을 이용해서 삼각형 그리기

    glColor3f(currentColor[0], currentColor[1], currentColor[2]);
    // 별을 구성하는 두 개의 삼각형을 그립니다.
    glVertex2f(-0.1f, -0.1f);           //첫번째 삼각형 좌표
    glVertex2f(0.1f, -0.1f);            //첫번째 삼각형 좌표
    glVertex2f(0.0f, 0.2f);             //첫번째 삼각형 좌표
    glVertex2f(-0.1f, 0.1f);            //두번째 삼각형 좌표
    glVertex2f(0.1f, 0.1f);             //두번째 삼각형 좌표
    glVertex2f(0.0f, -0.2f);            //두번째 삼각형 좌표

    glEnd();

    glPopMatrix(); // 행렬 상태를 복원
}

// 화면을 새로 그릴 때마다 호출
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // 화면을 클리어합니다.
    for (int i = 0; i < starsCount; i++) { // 저장된 모든 별을 그립니다.
        drawStar(stars[i].x, stars[i].y);   //구조체 안에 있는 별의 좌표 출력
    }
    
    // 별들 사이에 선을 그려서 연결합니다.
    if (starsCount > 1) {
        glColor3f(1.0, 0.0, 0.0); // 선의 색상을 설정합니다 (빨간색).
        glBegin(GL_LINES);
        for (int i = 0; i < starsCount - 1; i++) {
            glVertex2f(stars[i].x, stars[i].y);
            glVertex2f(stars[i + 1].x, stars[i + 1].y);
        }
        glEnd();
    }
    glutSwapBuffers(); // 더블 버퍼로 동작하기 때문에 glutSwapBuffers()
}


// 마우스 클릭 이벤트를 처리하는 함수입니다.
void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) { // 마우스 버튼이 눌렸을 때
        

        // 왼쪽 버튼 클릭 & 구조체에 자리가 있다면
        if (button == GLUT_LEFT_BUTTON && starsCount < MAX_STARS) {
            float newX = (float)x / (glutGet(GLUT_WINDOW_WIDTH) / 2) - 1.0f;
            float newY = -((float)y / (glutGet(GLUT_WINDOW_HEIGHT) / 2) - 1.0f);
            
            stars[starsCount++] = (struct Star){newX, newY};    //구조체제 좌표 저장
        }

        
        // 가운데 버튼으로 별 색상 변경
        else if (button == GLUT_MIDDLE_BUTTON) {
            int r, g, b;
                r = rand() % 256;
                g = rand() % 256;
                b = rand() % 256;

                // OpenGL에서 사용하기 위해 [0, 1] 범위의 float 값으로 변환합니다.
                currentColor[0] = (float)r / 255.0f;
                currentColor[1] = (float)g / 255.0f;
                currentColor[2] = (float)b / 255.0f;

        }
        
        // 오른쪽 버튼으로 별 회전 상태 토글
        else if (button == GLUT_RIGHT_BUTTON) {
            rotating = true;  // => 오른쪽 버튼을 누르면 계속 true 상태
            if (rotating) {
                rotateDirection = !rotateDirection; // 오른쪽 클릭시 반대로 회전 방향
            }
        }
    }
    glutPostRedisplay(); // 화면을 다시 그립니다.
}

// 화면을 업데이트하는 함수 실질적으로 별이 돌아가는 애니메이션 역할
void update(int value) {
    if (rotating) { // 회전 상태일 때 회전 각도를 업데이트
        if (rotateDirection) {
            spin += 3.5;        //회전 각도 = 속도
        } else {
            spin -= 3.5;
        }

        // spin 값이 0 미만이거나 360 초과인 경우 값을 조정
        if (spin > 360.0) {
            spin -= 360.0;
        } else if (spin < 0.0) {
            spin += 360.0;
        }
    }
    glutPostRedisplay(); // 화면 재출력
    glutTimerFunc(delay, update, 0); // delay 간격으로 update 함수를 다시 호출합니다.
}

// 메인 함수
int main(int argc, char** argv) {
    glutInit(&argc, argv); // GLUT 라이브러리를 초기화
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // 더블 버퍼링과 RGB 색상 모드를 설정
    glutInitWindowSize(600, 400); // 윈도우의 크기를 설정
    glutInitWindowPosition(100, 100);
    glutCreateWindow("별자리 그리기"); // 제목 설정
    glClearColor(1.0, 1.0, 1.0, 1.0); // 배경색을 흰색으로 설정

    //윈도우를 시작하면 0,0에 고정적으로 별하나는 생김.
    stars[0].x = 0.0f;
    stars[0].y = 0.0f;

    glutDisplayFunc(display); // 디스플레이 콜백 함수를 지정
    glutMouseFunc(mouse); // 마우스 이벤트 콜백 함수를 지정
    glutTimerFunc(delay, update, 0); // 타이머 콜백 함수를 사용하여 화면을 delay 간격으로 업데이트
    glutMainLoop(); // 이벤트 시작
    return 0;
}


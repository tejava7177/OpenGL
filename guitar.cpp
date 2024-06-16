/*
    컴퓨터소프트웨어공학과 20204020 심주흔
    컴퓨터그래픽스 기말 프로젝트 : 모델링 구현 및 요구사항 구현
    제출일 : 20204. 06 . 16
*/

#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>                 
#include <iostream>                 //textureMapping 오류 출력을 위한 라이브러리
#include <gl/glut.h>                //openGL 함수 라이브러리
#include <vector>                   // 동적배열, texture 이미지 저장,처리를 위한 라이브러리
#include "lodepng.h"                //png 파일을 디코딩, 인코딩 하기 위한 헤더파일

// 모델 데이터를 저장하는 구조체 정의
typedef struct {
    double** vPoint;   // 정점 좌표
    double** vnPoint;  // 법선 벡터
    double** vtPoint;  // 텍스처 좌표
    int** fPoint;      // 면 정의
    int vNum;          // 정점 수
    int vnNum;         // 법선 벡터 수
    int vtNum;         // 텍스처 좌표 수
    int fNum;          // 면 수
    int ModelType;     // 모델 타입
} Model;

Model global_model1; // 전역 모델 객체

// 조명 관련 설정 (백색광으로 설정)
GLfloat lightPosition[4] = { 0.0, 1.0, -2.0, 1.0 };     //조명의 위치
GLfloat ambientLight[4] = { 1.0, 1.0, 1.0, 1.0 };       //주변광 색상
GLfloat diffuseLight[4] = { 1.0, 1.0, 1.0, 1.0 };       //난반사광
GLfloat specular[4] = { 1.0, 1.0, 1.0, 1.0 };           //반사광

// 추가 조명 색상 설정
GLfloat lightAmbient[4] = { 1.0, 1.0, 1.0, 1.0 };       //주변 반사광
GLfloat lightDiffuse[4] = { 1.0, 1.0, 1.0, 1.0 };       //확산반사 입사광
GLfloat lightSpecular[4] = { 1.0, 1.0, 1.0, 1.0 };      //경면 반사 입사광

// 평면 및 모델 색상 설정
GLfloat planeColor[3] = { 0.0f, 0.0f, 0.0f };           //plane 컬러 저장배열
GLfloat guitarColor[3] = { 0.5f, 0.5f, 0.5f };          //기타 컬러 저장배열




// 뷰포트 설정
int selectedViewport = 0;  // 선택된 뷰포트 (1: 위, 2: 오른쪽, 3: 앞, 4: 랜덤)

// 카메라 위치 
float cameraPositions[4][3] = {
    {0.0, 107.0, 0.0},    // 위 뷰포트
    {107.0, 0.0, 105.0},  // 오른쪽 뷰포트
    {-105.0, 0.0, 107.0}, // 앞 뷰포트
    {-30.0, 100.0, 20.0}  // 랜덤 뷰포트
};

float cameraDirections[4][3] = {
    {0.0, 0.0, -1.0},  // 위 뷰포트 방향
    {0.0, 1.0, 0.0},   // 오른쪽 뷰포트 방향
    {0.0, 1.0, 0.0},   // 앞 뷰포트 방향
    {0.0, 0.0, -1.0}   // 랜덤 뷰포트 방향
};

float scale = 0.5; // 모델 스케일

GLuint textureID; // 텍스처 ID
bool textureEnabled = true; // 텍스처 사용 여부 (toggle)
std::vector<unsigned char> image2; // 이미지 데이터 저장 벡터

// 텍스처 로드 함수
void loadTexture(const char* path) {
    std::cout << "Loading texture from: " << path << std::endl;         //경로 출력
    std::vector<unsigned char> image;
    unsigned width, height;
    unsigned error = lodepng::decode(image, width, height, path);
    if (error) {
        // 오류 발생시 출력
        std::cout << "error " << error << ": " << lodepng_error_text(error) << std::endl;
        return;
    }

    glGenTextures(1, &textureID);                   //객체생성
    glBindTexture(GL_TEXTURE_2D, textureID);        //객체 바인딩
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());         //객체 저장
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);   // 텍스처의 축소 필터링 방법 설정, 파라미터 저장, 선형 필터링 방법 등
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   // 텍스처의 확대 필터링 방법 설정.
}



// 바닥 평면 설정 함수
void setupPlane(Model& model) {
    double planeY = -0.01;          // Plane의 높이 위치, 모델링 결과 보다 낮은 위치
    double halfSize = 150.0;        //사이즈 조정

    glMaterialfv(GL_FRONT, GL_AMBIENT, planeColor);  // Plane 색상 설정
    glMaterialfv(GL_FRONT, GL_DIFFUSE, planeColor);     
    glColor3f(planeColor[0], planeColor[1], planeColor[2]);  // Plane 색상 설정

    glBegin(GL_QUADS);
    glVertex3f(-halfSize, planeY, -halfSize);  // 왼쪽 아래
    glVertex3f(-halfSize, planeY, halfSize);   // 왼쪽 위
    glVertex3f(halfSize, planeY, halfSize);    // 오른쪽 위
    glVertex3f(halfSize, planeY, -halfSize);   // 오른쪽 아래
    glEnd();
}


// 모델 렌더링 함수
void rendering(Model model) {

    // 조명 설정
    GLfloat mat_ambient[] = { 0.2, 0.2, 0.2, 1.0 };             // 주변광
    GLfloat mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };             //확산광
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };            //반사광
    GLfloat mat_shininess[] = { 50.0 };                         //광택도

  
    glPushMatrix();  // 현재 모델뷰 행렬을 저장

    glMaterialfv(GL_FRONT, GL_AMBIENT, guitarColor);            //기타 색으로 주변광 설정     
    glMaterialfv(GL_FRONT, GL_DIFFUSE, guitarColor);            //기타 색으로 확산광 설정
    glTranslatef(-15.0f, 0.0f, 0.0f);                           // 모델을 왼쪽으로 이동(조정)

    glColor3f(guitarColor[0], guitarColor[1], guitarColor[2]);  // 모델 색상 설정

    //모델링 시작 삼각형을 순회하면서 구현
    for (int i = 0; i < model.fNum; i++) {
        switch (model.ModelType) {
            
        case 0:         // 법선 백터로만 구성된 경우
            glBegin(GL_TRIANGLES);
            glVertex3f(model.vPoint[model.fPoint[i][0]][0] / scale, model.vPoint[model.fPoint[i][0]][1] / scale, model.vPoint[model.fPoint[i][0]][2] / scale);
            glVertex3f(model.vPoint[model.fPoint[i][1]][0] / scale, model.vPoint[model.fPoint[i][1]][1] / scale, model.vPoint[model.fPoint[i][1]][2] / scale);
            glVertex3f(model.vPoint[model.fPoint[i][2]][0] / scale, model.vPoint[model.fPoint[i][2]][1] / scale, model.vPoint[model.fPoint[i][2]][2] / scale);
            glEnd();
            break;
        case 1:         //텍스처를 사용하는 경우
            if (textureEnabled) {
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, textureID);
            }
            else {
                glDisable(GL_TEXTURE_2D);
            }
            glBegin(GL_TRIANGLES);
            glTexCoord2f(model.vtPoint[model.fPoint[i][1]][0], model.vtPoint[model.fPoint[i][1]][1]);
            glVertex3f(model.vPoint[model.fPoint[i][0]][0] / scale, model.vPoint[model.fPoint[i][0]][1] / scale, model.vPoint[model.fPoint[i][0]][2] / scale);
            glTexCoord2f(model.vtPoint[model.fPoint[i][3]][0], model.vtPoint[model.fPoint[i][3]][1]);
            glVertex3f(model.vPoint[model.fPoint[i][2]][0] / scale, model.vPoint[model.fPoint[i][2]][1] / scale, model.vPoint[model.fPoint[i][2]][2] / scale);
            glTexCoord2f(model.vtPoint[model.fPoint[i][5]][0], model.vtPoint[model.fPoint[i][5]][1]);
            glVertex3f(model.vPoint[model.fPoint[i][4]][0] / scale, model.vPoint[model.fPoint[i][4]][1] / scale, model.vPoint[model.fPoint[i][4]][2] / scale);
            glEnd();
            if (textureEnabled) {
                glDisable(GL_TEXTURE_2D);
            }
            break;
        case 2:     //법선 벡터를 사용하는 경우
            glBegin(GL_TRIANGLES);
            glNormal3f(model.vnPoint[model.fPoint[i][1]][0], model.vnPoint[model.fPoint[i][1]][1], model.vnPoint[model.fPoint[i][1]][2]);
            glVertex3f(model.vPoint[model.fPoint[i][0]][0] / scale, model.vPoint[model.fPoint[i][0]][1] / scale, model.vPoint[model.fPoint[i][0]][2] / scale);
            glNormal3f(model.vnPoint[model.fPoint[i][3]][0], model.vnPoint[model.fPoint[i][3]][1], model.vnPoint[model.fPoint[i][3]][2]);
            glVertex3f(model.vPoint[model.fPoint[i][2]][0] / scale, model.vPoint[model.fPoint[i][2]][1] / scale, model.vPoint[model.fPoint[i][2]][2] / scale);
            glNormal3f(model.vnPoint[model.fPoint[i][5]][0], model.vnPoint[model.fPoint[i][5]][1], model.vnPoint[model.fPoint[i][5]][2]);
            glVertex3f(model.vPoint[model.fPoint[i][4]][0] / scale, model.vPoint[model.fPoint[i][4]][1] / scale, model.vPoint[model.fPoint[i][4]][2] / scale);
            glEnd();
            break;
            
        case 3:     //텍스처와 법선 벡터 모두를 사용하는 경우 (프로젝트의 경우에 해당)
            if (textureEnabled) {
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, textureID);
            }
            else {
                glDisable(GL_TEXTURE_2D);
            }
            glBegin(GL_TRIANGLES);
            glNormal3f(model.vnPoint[model.fPoint[i][2]][0], model.vnPoint[model.fPoint[i][2]][1], model.vnPoint[model.fPoint[i][2]][2]);
            glTexCoord2f(model.vtPoint[model.fPoint[i][1]][0], model.vtPoint[model.fPoint[i][1]][1]);
            glVertex3f(model.vPoint[model.fPoint[i][0]][0] / scale, model.vPoint[model.fPoint[i][0]][1] / scale, model.vPoint[model.fPoint[i][0]][2] / scale);
            glNormal3f(model.vnPoint[model.fPoint[i][5]][0], model.vnPoint[model.fPoint[i][5]][1], model.vnPoint[model.fPoint[i][5]][2]);
            glTexCoord2f(model.vtPoint[model.fPoint[i][4]][0], model.vtPoint[model.fPoint[i][4]][1]);
            glVertex3f(model.vPoint[model.fPoint[i][3]][0] / scale, model.vPoint[model.fPoint[i][3]][1] / scale, model.vPoint[model.fPoint[i][3]][2] / scale);
            glNormal3f(model.vnPoint[model.fPoint[i][5]][0], model.vnPoint[model.fPoint[i][5]][1], model.vnPoint[model.fPoint[i][8]][2]);
            glTexCoord2f(model.vtPoint[model.fPoint[i][7]][0], model.vtPoint[model.fPoint[i][7]][1]);
            glVertex3f(model.vPoint[model.fPoint[i][6]][0] / scale, model.vPoint[model.fPoint[i][6]][1] / scale, model.vPoint[model.fPoint[i][6]][2] / scale);
            glEnd();
            // 텍스처 토글을 위한 조건문
            if (textureEnabled) {
                glDisable(GL_TEXTURE_2D);       //텍스처 매핑 비활성화
            }
            break;
        }
    }
    glDisable(GL_TEXTURE_2D);                      //텍스처 매핑 비활성화
}


// 카메라 설정 함수
void setCamera(int viewport) {
    // 카메라의 위치와 방향을 설정하기 위해 배열에서 값을 가져옴.
    float* pos = cameraPositions[viewport - 1];           
    float* dir = cameraDirections[viewport - 1];

    glMatrixMode(GL_MODELVIEW);                     //모델 뷰 활성화
    glLoadIdentity();                               //기본 상태
    gluLookAt(pos[0], pos[1], pos[2], 0.0, 0.0, 0.0, dir[0], dir[1], dir[2]);    //dir은 카메라의 상향 벡터를 나타냄.
}

// 씬 그리기 함수
void drawScene() {
    setupPlane(global_model1);              //plane 설정 함수 호출 후 렌더링
    rendering(global_model1);               //모델링 렌더링
}

// 뷰포트 테두리 그리기 함수 (추가로 구현)
void drawViewportBorder(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(5.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0, height);
    glVertex2f(0, 0);
    glVertex2f(width, 0);
    glVertex2f(width, height);
    glEnd();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

// 디스플레이 함수
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int width = glutGet(GLUT_WINDOW_WIDTH);                 //너비 설정
    int height = glutGet(GLUT_WINDOW_HEIGHT);               //높이 설정

    // 뷰포트 1: 위에서 바라보기
    glViewport(0, height / 2, width / 2, height / 2);
    setCamera(1);           //카메라 설정
    drawScene();            //모델링 시작
    // 사용자가 1을 눌렀다면 1번 viewport 윤곽을 보이게 함
    if (selectedViewport == 1) {
        drawViewportBorder(width / 2, height / 2);
    }

    // 뷰포트 2: 오른쪽에서 바라보기
    glViewport(width / 2, height / 2, width / 2, height / 2);
    setCamera(2);           //카메라 설정
    drawScene();            //모델링 시작
    // 2를 눌렀다면 2번째 viewport에 윤곽
    if (selectedViewport == 2) {
        drawViewportBorder(width / 2, height / 2);
    }

    // 뷰포트 3: 앞에서 바라보기
    glViewport(0, 0, width / 2, height / 2);
    setCamera(3);       //카메라 설정
    drawScene();        //모델링 시작
    // 3를 눌렀다면 3번째 viewport에 윤곽
    if (selectedViewport == 3) {
        drawViewportBorder(width / 2, height / 2);
    }

    // 뷰포트 4: 랜덤 바라보기
    glViewport(width / 2, 0, width / 2, height / 2);
    setCamera(4);       //카메라 설정
    drawScene();        //모델링 시작
    // 4를 눌렀다면 4번째 viewport에 윤곽
    if (selectedViewport == 4) {
        drawViewportBorder(width / 2, height / 2);
    }
    glutSwapBuffers();
}

// OBJ 파일 로드 함수
Model ObjLoad(const char* name) {
    Model model;

    model.vNum = 0;
    model.vnNum = 0;
    model.vtNum = 0;
    model.fNum = 0;
    char temp;
    char c[20];
    int vCount = 0;
    int fCount = 0;
    int vnCount = 0;
    int vtCount = 0;

    model.ModelType = 0;

    FILE* fp = fopen(name, "r");

    // 파일을 읽어 정점, 법선, 텍스처 좌표, 면의 수를 카운트
    while (!feof(fp)) {
        fscanf(fp, "%s", c);
        if (strcmp(c, "v") == 0)
            model.vNum++;
        else if (strcmp(c, "f") == 0)
            model.fNum++;
        else if (strcmp(c, "vn") == 0)
            model.vnNum++;
        else if (strcmp(c, "vt") == 0)
            model.vtNum++;
    }
    rewind(fp);

    // 동적 메모리 할당
    model.vPoint = (double**)malloc(sizeof(double*) * model.vNum);
    for (int i = 0; i < model.vNum; i++)
        model.vPoint[i] = (double*)malloc(sizeof(double) * 3);

    model.vnPoint = (double**)malloc(sizeof(double*) * model.vnNum);
    for (int i = 0; i < model.vnNum; i++)
        model.vnPoint[i] = (double*)malloc(sizeof(double) * 3);

    model.vtPoint = (double**)malloc(sizeof(double*) * model.vtNum);
    for (int i = 0; i < model.vtNum; i++)
        model.vtPoint[i] = (double*)malloc(sizeof(double) * 2);

    model.fPoint = (int**)malloc(sizeof(int*) * model.fNum);

    // 모델 타입에 따라 메모리 할당
    if (model.vnNum == 0 && model.vtNum == 0) {
        for (int i = 0; i < model.fNum; i++)
            model.fPoint[i] = (int*)malloc(sizeof(double) * 3);

        model.ModelType = 0;
    }
    else if (model.vnNum == 0 && model.vtNum != 0) {
        for (int i = 0; i < model.fNum; i++)
            model.fPoint[i] = (int*)malloc(sizeof(double) * 6);

        model.ModelType = 1;
    }
    else if (model.vnNum != 0 && model.vtNum == 0) {
        for (int i = 0; i < model.fNum; i++)
            model.fPoint[i] = (int*)malloc(sizeof(double) * 6);

        model.ModelType = 2;
    }
    else if (model.vnNum != 0 && model.vtNum != 0) {
        for (int i = 0; i < model.fNum; i++)
            model.fPoint[i] = (int*)malloc(sizeof(double) * 9);

        model.ModelType = 3;
    }

    // 모델 데이터 읽기
    while (!feof(fp)) {
        fscanf(fp, "%s", c);

        if (strcmp(c, "v") == 0) {
            fscanf(fp, "%lf %lf %lf", &model.vPoint[vCount][0], &model.vPoint[vCount][1], &model.vPoint[vCount][2]);
            vCount++;
        }
        else if (strcmp(c, "f") == 0) {
            if (fCount >= model.fNum) break;
            if (model.ModelType == 0) {
                fscanf(fp, "%d %d %d", &model.fPoint[fCount][0], &model.fPoint[fCount][1], &model.fPoint[fCount][2]);
                model.fPoint[fCount][0]--;
                model.fPoint[fCount][1]--;
                model.fPoint[fCount][2]--;
                fCount++;
            }
            else if (model.ModelType == 1) {
                for (int i = 0; i < 3; i++) {
                    fscanf(fp, "%d %c %d", &model.fPoint[fCount][i * 2], &temp, &model.fPoint[fCount][i * 2 + 1]);
                    model.fPoint[fCount][i * 2]--;
                    model.fPoint[fCount][i * 2 + 1]--;
                }
                fCount++;
            }
            else if (model.ModelType == 2) {
                for (int i = 0; i < 3; i++) {
                    fscanf(fp, "%d %c %c %d", &model.fPoint[fCount][i * 2], &temp, &temp, &model.fPoint[fCount][i * 2 + 1]);
                    model.fPoint[fCount][i * 2]--;
                    model.fPoint[fCount][i * 2 + 1]--;
                }
                fCount++;
            }
            else if (model.ModelType == 3) {
                for (int i = 0; i < 3; i++) {
                    fscanf(fp, "%d %c %d %c %d", &model.fPoint[fCount][i * 3], &temp, &model.fPoint[fCount][i * 3 + 1], &temp, &model.fPoint[fCount][i * 3 + 2]);
                    model.fPoint[fCount][i * 3]--;
                    model.fPoint[fCount][i * 3 + 1]--;
                    model.fPoint[fCount][i * 3 + 2]--;
                }
                fCount++;
            }
        }
        else if (strcmp(c, "vn") == 0) {
            fscanf(fp, "%lf %lf %lf", &model.vnPoint[vnCount][0], &model.vnPoint[vnCount][1], &model.vnPoint[vnCount][2]);
            vnCount++;
        }
        else if (strcmp(c, "vt") == 0) {
            fscanf(fp, "%lf %lf", &model.vtPoint[vtCount][0], &model.vtPoint[vtCount][1]);
            vtCount++;
        }
    }
    printf("MODEL 로드 성공 : %d %d\n", model.vNum, model.fNum);
    fclose(fp);
    return model;
}

// 초기화 함수
void init() {
    global_model1 = ObjLoad("guitar2.obj");

    glClearColor(1.0, 1.0, 1.0, 0);             //배경 색상을 흰색으로 설정
    glMatrixMode(GL_PROJECTION);                //프로젝션 행렬 설정
    glLoadIdentity();                           
    gluPerspective(45.0, 1.0, 0.1, 1000.0);     //원근 투영 설정 

    //깊이 테스트 활성화
    glEnable(GL_DEPTH_TEST);

    //조명 설정
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    //조명 활성화
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    //텍스처 로드 및 초기화
    loadTexture("wood3.png");
}

// 뷰포트 사이즈 변경시 호출
void reshape(int new_w, int new_h) {
    glViewport(0, 0, new_w, new_h);         //새로운 윈도우 크기로 설정
    glMatrixMode(GL_PROJECTION);            
    glLoadIdentity();
    // 새로운 윈도우 비율에 맞춘 원근 투영 설정
    gluPerspective(120.0, (float)new_w / (float)new_h, 0.1, 1000.0);

    //모델뷰 행렬 설정
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// 모델 데이터 해제 함수
void freeModel(Model model) {
    for (int i = 0; i < model.vNum; i++)        //정점에 대한 메모리 해제
        free(model.vPoint[i]);
    free(model.vPoint);

    for (int i = 0; i < model.vnNum; i++)       //법선 벡터에 대한 메모리 해제
        free(model.vnPoint[i]);
    free(model.vnPoint);

    for (int i = 0; i < model.vtNum; i++)       // 텍스처 좌표에 대한 메모리 해제
        free(model.vtPoint[i]);
    free(model.vtPoint);

    for (int i = 0; i < model.fNum; i++)        // 면에 대한 메모리 해제
        free(model.fPoint[i]);
    free(model.fPoint);
}

// 평면 색상 변경 함수
void changePlaneColor() {
    // 랜덤 색상 설정
    planeColor[0] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    planeColor[1] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    planeColor[2] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

// 모델 색상 변경 함수
void changeModelColor() {
    // 랜덤 색상 설정
    guitarColor[0] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    guitarColor[1] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    guitarColor[2] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

// 조명 색상 변경 함수
void changeLightColor() {
    // 랜덤 색상 설정
    lightAmbient[0] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    lightAmbient[1] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    lightAmbient[2] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

    lightDiffuse[0] = lightAmbient[0];
    lightDiffuse[1] = lightAmbient[1];
    lightDiffuse[2] = lightAmbient[2];

    lightSpecular[0] = lightAmbient[0];
    lightSpecular[1] = lightAmbient[1];
    lightSpecular[2] = lightAmbient[2];

    // OpenGL 조명 설정 업데이트
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
}

// 조명 토글 함수
void toggleLight() {
    static bool lightOn = true;
    lightOn = !lightOn;
    if (lightOn) {
        glEnable(GL_LIGHTING);
    }
    else {
        glDisable(GL_LIGHTING);
    }
}

// 텍스처 토글 함수
void toggleTexture() {
    textureEnabled = !textureEnabled;  // 텍스처 사용 여부를 토글
    glutPostRedisplay();  // 화면을 새로 그릴 것을 요청
}

// 메뉴 항목 선택 함수
void menu(int item) {
    switch (item) {
    case 1:
        // Plane 색 변경
        changePlaneColor();
        break;
    case 2:
        // 모델 색 변경
        changeModelColor();
        break;
    case 3:
        // 조명 on/off
        toggleLight();
        break;
    case 4:
        changeLightColor();
        break;
    case 5:
        toggleTexture();
        break;
    }
    glutPostRedisplay();  // 화면을 새로 그릴 것을 요청
}

// 팝업메뉴 생성 함수
void createMenu() {
    glutCreateMenu(menu);
    glutAddMenuEntry("Plane 색상 랜덤 변경", 1);
    glutAddMenuEntry("모델링 색상 랜덤 변경", 2);
    glutAddMenuEntry("조명 on/off", 3);
    glutAddMenuEntry("조명 색상 변경", 4);
    glutAddMenuEntry("Texture on/off", 5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);  // 마우스 오른쪽 버튼으로 실행
}

// 키보드 입력 처리 함수 뷰포트 선택
void keyboardFunc(unsigned char key, int x, int y) {
    switch (key) {
    case '1':
        selectedViewport = 1;
        break;
    case '2':
        selectedViewport = 2;
        break;
    case '3':
        selectedViewport = 3;
        break;
    case '4':
        selectedViewport = 4;
        break;
    }
    glutPostRedisplay();
}

// 방향키 입력 처리 함수
void specialKeys(int key, int x, int y) {
    if (selectedViewport == 0) return;

    //카메라 위치 설정
    float* pos = cameraPositions[selectedViewport - 1];

    switch (key) {
    case GLUT_KEY_UP:
        pos[1] += 10.0;
        break;
    case GLUT_KEY_DOWN:
        pos[1] -= 10.0;
        break;
    case GLUT_KEY_LEFT:
        pos[0] -= 10.0;
        break;
    case GLUT_KEY_RIGHT:
        pos[0] += 10.0;
        break;
    }

    glutPostRedisplay();    //적용
}


// 메인 함수
int main(int argc, char** argv) {
    glutInit(&argc, argv);                      //glut 라이브러리 초기화 및 명령줄 인수 처리
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   //더블 버퍼링, RGB 색상, 깊이버퍼
    glutInitWindowPosition(100, 100);               //윈도우 초기 위치 설정
    glutInitWindowSize(800, 800);                   //윈도우 크기 설정
    glutCreateWindow("Final Project_20204020_심주흔");     //타이틀 설정

    init();         //초기화 함수 호출
    createMenu();  // 메뉴 생성 호출

    glutDisplayFunc(display);           //디스플레이 콜백함수
    glutReshapeFunc(reshape);           //reshpae 함수 호출
    glutKeyboardFunc(keyboardFunc);     // 키보드 입력 처리 함수
    glutSpecialFunc(specialKeys);       // 방향키 입력 처리 함수

    glutMainLoop();                     //메인루프 진입 (종료까지 계속)

    freeModel(global_model1);           // 모델 메모리 해제
    return 0;
}

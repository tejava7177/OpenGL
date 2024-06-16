#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <gl/glut.h>
#include <vector>
#include "lodepng.h"

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

// 조명 관련 설정
GLfloat lightPosition[4] = { 0.0, 1.0, -2.0, 1.0 };
GLfloat ambientLight[4] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat diffuseLight[4] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat specular[4] = { 1.0, 1.0, 1.0, 1.0 };

// 평면 및 모델 색상 설정
GLfloat planeColor[3] = { 0.0f, 0.0f, 0.0f };
GLfloat guitarColor[3] = { 0.5f, 0.5f, 0.5f };

// 추가 조명 색상 설정
GLfloat lightAmbient[4] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat lightDiffuse[4] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat lightSpecular[4] = { 1.0, 1.0, 1.0, 1.0 };

float lightMovementSpeed = 0.5f;

// 뷰포트 설정
int selectedViewport = 0;  // 선택된 뷰포트 (0: 없음, 1: 위, 2: 오른쪽, 3: 앞, 4: 랜덤)
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
bool textureEnabled = true; // 텍스처 사용 여부
std::vector<unsigned char> image2; // 이미지 데이터 저장 벡터

// 텍스처 로드 함수
void loadTexture(const char* path) {
    std::cout << "Loading texture from: " << path << std::endl;
    std::vector<unsigned char> image;
    unsigned width, height;
    unsigned error = lodepng::decode(image, width, height, path);
    if (error) {
        std::cout << "error " << error << ": " << lodepng_error_text(error) << std::endl;
        return;
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

// 텍스처 초기화 함수
void textureinitialize() {
    loadTexture("wood3.png"); 
}

// 바닥 평면 설정 함수
void setupPlane(Model& model) {
    double planeY = -0.01;  // Plane의 높이 위치
    double halfSize = 150.0;  // Plane의 절반 크기

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
    GLfloat mat_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glPushMatrix();  // 현재 모델뷰 행렬을 저장

    glMaterialfv(GL_FRONT, GL_AMBIENT, guitarColor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, guitarColor);
    glTranslatef(-15.0f, 0.0f, 0.0f);  // 모델을 왼쪽으로 이동

    glColor3f(guitarColor[0], guitarColor[1], guitarColor[2]);  // 모델 색상 설정

    for (int i = 0; i < model.fNum; i++) {
        switch (model.ModelType) {
        case 0:
            glBegin(GL_TRIANGLES);
            glVertex3f(model.vPoint[model.fPoint[i][0]][0] / scale, model.vPoint[model.fPoint[i][0]][1] / scale, model.vPoint[model.fPoint[i][0]][2] / scale);
            glVertex3f(model.vPoint[model.fPoint[i][1]][0] / scale, model.vPoint[model.fPoint[i][1]][1] / scale, model.vPoint[model.fPoint[i][1]][2] / scale);
            glVertex3f(model.vPoint[model.fPoint[i][2]][0] / scale, model.vPoint[model.fPoint[i][2]][1] / scale, model.vPoint[model.fPoint[i][2]][2] / scale);
            glEnd();
            break;
        case 1:
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
        case 2:
            glBegin(GL_TRIANGLES);
            glNormal3f(model.vnPoint[model.fPoint[i][1]][0], model.vnPoint[model.fPoint[i][1]][1], model.vnPoint[model.fPoint[i][1]][2]);
            glVertex3f(model.vPoint[model.fPoint[i][0]][0] / scale, model.vPoint[model.fPoint[i][0]][1] / scale, model.vPoint[model.fPoint[i][0]][2] / scale);
            glNormal3f(model.vnPoint[model.fPoint[i][3]][0], model.vnPoint[model.fPoint[i][3]][1], model.vnPoint[model.fPoint[i][3]][2]);
            glVertex3f(model.vPoint[model.fPoint[i][2]][0] / scale, model.vPoint[model.fPoint[i][2]][1] / scale, model.vPoint[model.fPoint[i][2]][2] / scale);
            glNormal3f(model.vnPoint[model.fPoint[i][5]][0], model.vnPoint[model.fPoint[i][5]][1], model.vnPoint[model.fPoint[i][5]][2]);
            glVertex3f(model.vPoint[model.fPoint[i][4]][0] / scale, model.vPoint[model.fPoint[i][4]][1] / scale, model.vPoint[model.fPoint[i][4]][2] / scale);
            glEnd();
            break;
        case 3:
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
            if (textureEnabled) {
                glDisable(GL_TEXTURE_2D);
            }
            break;
        }
    }

    glDisable(GL_TEXTURE_2D);
}

// 카메라 설정 함수
void setCamera(int viewport) {
    float* pos = cameraPositions[viewport - 1];
    float* dir = cameraDirections[viewport - 1];
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(pos[0], pos[1], pos[2], 0.0, 0.0, 0.0, dir[0], dir[1], dir[2]);
}

// 씬 그리기 함수
void drawScene() {
    setupPlane(global_model1);
    rendering(global_model1);
}

// 뷰포트 테두리 그리기 함수
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

    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);

    // 뷰포트 1: 위에서 바라보기
    glViewport(0, height / 2, width / 2, height / 2);
    setCamera(1);
    drawScene();
    if (selectedViewport == 1) {
        drawViewportBorder(width / 2, height / 2);
    }

    // 뷰포트 2: 오른쪽에서 바라보기
    glViewport(width / 2, height / 2, width / 2, height / 2);
    setCamera(2);
    drawScene();
    if (selectedViewport == 2) {
        drawViewportBorder(width / 2, height / 2);
    }

    // 뷰포트 3: 앞에서 바라보기
    glViewport(0, 0, width / 2, height / 2);
    setCamera(3);
    drawScene();
    if (selectedViewport == 3) {
        drawViewportBorder(width / 2, height / 2);
    }

    // 뷰포트 4: 랜덤 바라보기
    glViewport(width / 2, 0, width / 2, height / 2);
    setCamera(4);
    drawScene();
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

    glClearColor(1.0, 1.0, 1.0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 0.1, 1000.0);

    glEnable(GL_DEPTH_TEST);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    textureinitialize();  // 초기화 함수 호출
}

// 뷰포트 변경 시 호출되는 함수
void reshape(int new_w, int new_h) {
    glViewport(0, 0, new_w, new_h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(120.0, (float)new_w / (float)new_h, 0.1, 1000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// 모델 데이터 해제 함수
void freeModel(Model model) {
    for (int i = 0; i < model.vNum; i++)
        free(model.vPoint[i]);
    free(model.vPoint);

    for (int i = 0; i < model.vnNum; i++)
        free(model.vnPoint[i]);
    free(model.vnPoint);

    for (int i = 0; i < model.vtNum; i++)
        free(model.vtPoint[i]);
    free(model.vtPoint);

    for (int i = 0; i < model.fNum; i++)
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
    glutAddMenuEntry("Change Plane Color (Random)", 1);
    glutAddMenuEntry("Change Model Color (Random)", 2);
    glutAddMenuEntry("Toggle Lighting", 3);
    glutAddMenuEntry("Change Lighting Color", 4);
    glutAddMenuEntry("Toggle Texture", 5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);  // 오른쪽 버튼에 메뉴 붙이기
}

// 키보드 입력 처리 함수
void keyboardFunc(unsigned char key, int x, int y) {
    switch (key) {
    case '1':
        selectedViewport = 1;
        printf("1 selected");
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
    glutPostRedisplay();
}

// 마우스 이벤트 콜백 함수
void mouseFunc(int button, int state, int x, int y) {
    if (button == 3) {  // 휠 업
        lightPosition[2] += lightMovementSpeed;
        glutPostRedisplay();  // 화면을 새로 그릴 것을 요청
    }
    else if (button == 4) {  // 휠 다운
        lightPosition[1] -= lightMovementSpeed;
        glutPostRedisplay();  // 화면을 새로 그릴 것을 요청
    }
}

// 메인 함수
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("OBJ Viewer");

    init();
    createMenu();  // 메뉴 생성 호출

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboardFunc);  // 키보드 입력 처리 함수
    glutSpecialFunc(specialKeys);  // 방향키 입력 처리 함수

    // 마우스 이벤트 콜백 설정
    glutMouseFunc(mouseFunc);

    glutMainLoop();

    freeModel(global_model1); // 모델 메모리 해제
    return 0;
}

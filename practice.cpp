#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <gl\glut.h>
#include <vector>
#include "lodepng.h"

typedef struct {
    double** vPoint;
    double** vnPoint;
    double** vtPoint;
    int** fPoint;
    int vNum;
    int vnNum;
    int vtNum;
    int fNum;
    int ModelType;
} Model;

Model global_model1;

GLfloat lightPosition[4] = { 0.0, 1.0, -2.0, 1.0 };
GLfloat ambientLight[4] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat diffuseLight[4] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat specular[4] = { 1.0, 1.0, 1.0, 1.0 };

float scale = 0.5;
GLuint textureID;
std::vector<unsigned char> image2;


//plane
void calculateBoundingBox(Model& model, double& minX, double& maxX, double& minY, double& maxY, double& minZ, double& maxZ) {
    minX = minY = minZ = std::numeric_limits<double>::max();
    maxX = maxY = maxZ = std::numeric_limits<double>::min();

    for (int i = 0; i < model.vNum; i++) {
        double x = model.vPoint[i][0];
        double y = model.vPoint[i][1];
        double z = model.vPoint[i][2];
        minX = std::min(minX, x);
        maxX = std::max(maxX, x);
        minY = std::min(minY, y);
        maxY = std::max(maxY, y);
        minZ = std::min(minZ, z);
        maxZ = std::max(maxZ, z);
    }
}



void setupPlane(Model& model) {
    double minX, maxX, minY, maxY, minZ, maxZ;
    calculateBoundingBox(model, minX, maxX, minY, maxY, minZ, maxZ);

    // 평면의 y 위치는 모델의 최소 y값에 조금 더 아래에 위치
    double planeY = minY - 0.01;

    glColor3f(1.0, 1.0, 0.0); // 노란색 설정
    glBegin(GL_QUADS);
    glVertex3f(minX , planeY, minZ);  // 추가된 여백
    printf("%d %d %d", &minX, &planeY, &minZ);
    glVertex3f(minX , planeY, maxZ);  // 추가된 여백
    glVertex3f(maxX , planeY, maxZ);  // 추가된 여백
    glVertex3f(maxX , planeY, minZ);  // 추가된 여백
    glEnd();
}














void rendering(Model model) {

    /*
    GLfloat mat_ambient[] = { 1.0, 1.0, 0.0, 1.0 };
    GLfloat mat_diffuse[] = { 1.0, 1.0, 0.0, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    */


    glColor3f(0.5, 0.5, 0.5);
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
            glBindTexture(GL_TEXTURE_2D, textureID);
            glBegin(GL_TRIANGLES);
            glTexCoord2f(model.vtPoint[model.fPoint[i][1]][0], model.vtPoint[model.fPoint[i][1]][1]);
            glVertex3f(model.vPoint[model.fPoint[i][0]][0] / scale, model.vPoint[model.fPoint[i][0]][1] / scale, model.vPoint[model.fPoint[i][0]][2] / scale);
            glTexCoord2f(model.vtPoint[model.fPoint[i][3]][0], model.vtPoint[model.fPoint[i][3]][1]);
            glVertex3f(model.vPoint[model.fPoint[i][2]][0] / scale, model.vPoint[model.fPoint[i][2]][1] / scale, model.vPoint[model.fPoint[i][2]][2] / scale);
            glTexCoord2f(model.vtPoint[model.fPoint[i][5]][0], model.vtPoint[model.fPoint[i][5]][1]);
            glVertex3f(model.vPoint[model.fPoint[i][4]][0] / scale, model.vPoint[model.fPoint[i][4]][1] / scale, model.vPoint[model.fPoint[i][4]][2] / scale);
            glEnd();
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
            glBindTexture(GL_TEXTURE_2D, textureID);
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
            break;
        }
    }
}

/*
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_TEXTURE_2D);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);


    // 카메라 위치를 모델에 더 가까이 배치
    gluLookAt(0.0, 107.0, 0.0,  // 카메라 위치 (모델 앞쪽에서 더 가깝게)
        0.0, 0.0, 0.0,    // 바라보는 지점 (모델 중심)
        0.0, 0.0, -1.0);   // up 벡터 (0, 1, 0)

    glPushMatrix();


    setupPlane(global_model1);
    rendering(global_model1);

    glPopMatrix();

    glutPostRedisplay();
    glutSwapBuffers();
}
*/


void setCamera(float eyeX, float eyeY, float eyeZ, float upX, float upY, float upZ) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, 0.0, 0.0, 0.0, upX, upY, upZ);
}

void drawScene() {
    setupPlane(global_model1);
    rendering(global_model1);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 각 뷰포트 설정
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);

    // 뷰포트 1: 위에서 바라보기
    glViewport(0, height / 2, width / 2, height / 2);
    setCamera(0.0, 107.0, 0.0, 0.0, 0.0, -1.0);
    drawScene();

    // 뷰포트 2: 오른쪽에서 바라보기
    glViewport(width / 2, height / 2, width / 2, height / 2);
    setCamera(107.0, 0.0, 105.0, 0.0, 1.0, 0.0);
    drawScene();

    // 뷰포트 3: 앞에서 바라보기
    glViewport(0, 0, width / 2, height / 2);
    setCamera(-105.0, 0.0, 107.0, 0.0, 1.0, 0.0);
    drawScene();

    // 뷰포트 4: 랜덤 바라보기
    glViewport(width / 2, 0, width / 2, height / 2);
    setCamera(-30.0, 100.0, 20.0, 0.0, 0.0, -1.0);
    drawScene();

    glutSwapBuffers();
}




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
}

void reshape(int new_w, int new_h) {
    glViewport(0, 0, new_w, new_h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(120.0, (float)new_w / (float)new_h, 0.1, 1000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

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


void changePlaneColor() {
    // 랜덤 색상 설정
    float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    float g = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    float b = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    glColor3f(r, g, b);  // 이후 렌더링에서 이 색상 사용
}

void changeModelColor() {
    // 비슷한 방식으로 모델의 재질 색상 변경
}

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
    }
    glutPostRedisplay();  // 화면을 새로 그릴 것을 요청
}



















//팝업메뉴
void createMenu() {
    glutCreateMenu(menu);
    glutAddMenuEntry("Change Plane Color (Random)", 1);
    glutAddMenuEntry("Change Model Color (Random)", 2);
    glutAddMenuEntry("Toggle Lighting", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);  // 오른쪽 버튼에 메뉴 붙이기
}



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

    glutMainLoop();

    freeModel(global_model1);
    return 0;
}

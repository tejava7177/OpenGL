//#define GL_SILENCE_DEPRECATION      //버전 오류 해결
//
//#include <OpenGL/gl.h>
//#include <OpenGl/glu.h>
//#include <GLUT/glut.h>
//#include <math.h>
//
//void display() {
//    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 배경색을 흰색으로 설정
//    glClear(GL_COLOR_BUFFER_BIT); // 현재 버퍼를 지우고 설정된 배경색으로 새로 그림
//    
//    glBegin(GL_TRIANGLES);
//
//    // 첫 번째 삼각형 (빨간색)
//    glColor3f(1.0f, 0.0f, 0.0f);
//    glVertex2f(0.0f, 0.8f);
//    glVertex2f(-0.2f, 0.0f);
//    glVertex2f(0.2f, 0.0f);
//
//    // 두 번째 삼각형 (초록색)
//    glColor3f(0.0f, 1.0f, 0.0f);
//    glVertex2f(0.0f, 0.8f);
//    glVertex2f(0.2f, 0.0f);
//    glVertex2f(0.4f, 0.8f);
//
//    // 세 번째 삼각형 (파란색)
//    glColor3f(0.0f, 0.0f, 1.0f);
//    glVertex2f(0.0f, 0.8f);
//    glVertex2f(0.4f, 0.8f);
//    glVertex2f(0.2f, 0.0f);
//
//    glEnd();
//    
//    glFlush();
//}
//
//void reshape(int width, int height) {
//    glViewport(0, 0, width, height);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//
//    if (width <= height) {
//        gluOrtho2D(-1.0, 1.0, -1.0 * (GLfloat)height / (GLfloat)width, 1.0 * (GLfloat)height / (GLfloat)width);
//    } else {
//        gluOrtho2D(-1.0 * (GLfloat)width / (GLfloat)height, 1.0 * (GLfloat)width / (GLfloat)height, -1.0, 1.0);
//    }
//    glMatrixMode(GL_MODELVIEW);
//}
//
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitWindowSize(800, 600);
//    glutCreateWindow("OpenGL 겹쳐진 삼각형으로 별 그리기");
//    glutDisplayFunc(display);
//    glutReshapeFunc(reshape);
//
//    glutMainLoop();
//
//    return 0;
//}
//

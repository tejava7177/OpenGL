////
////  timer_Callback.cpp
////  OpenGlTest
////
////  Created by 심주흔 on 2024/03/22.
////
/// 테스트 주석 처리
//
//#define GL_SILENCE_DEPRECATION      //버전 오류 해결
//
//#include <iostream>
//#include <OpenGL/gl.h>
//#include <OpenGl/glu.h>
//#include <GLUT/glut.h>
//
//GLfloat Red = 0.0f;
//GLfloat Green = 0.0f;
//GLfloat Blue = 0.0f;
//
//GLint index_value = 0;
//GLfloat Delta = 0.0f;
//
//unsigned char PALETTE[9][3] = {
//    {255,255,255},
//    {0, 255, 255},
//    {255, 0,255},
//    {192,192,192},
//    {128,128,128},
//    {128,0,0},
//    {0,128,0},
//    {0,0,128},
//    {0,0,0}
//};
//
//void timerProcess(int value){
//    if(Delta < 2.0f){
//        Delta = Delta + 0.01f;
//        
//        if(++index_value >= 8){
//            index_value = 0;
//            glClear(GL_COLOR_BUFFER_BIT);
//        }
//    }
//    
//    else{
//        Delta = 0.0f;
//    }
//    glutPostRedisplay();
//    glutTimerFunc(200, timerProcess, 1);
//}
//
//
////임의의 추가코드
//void init(void) {
//    glClearColor(0.0, 0.0, 0.0, 0.0);
//
//}
//
//void display(){
//    glClear(GL_COLOR_BUFFER_BIT);
//    
//    Red = PALETTE[index_value][0] / 255.0f;
//    Green = PALETTE[index_value][1] / 255.0f;
//    Blue = PALETTE[index_value][2] / 255.0f;
//    
//    glColor3f(Red, Green, Blue);
//    
//    glBegin(GL_POLYGON);
//    glVertex3f(-0.75, -0.75, 0.0);
//    glVertex3f(0.75, -0.75, 0.0);
//    glVertex3f(0.75, 0.75, 0.0);
//    glVertex3f(-0.75, 0.75, 0.0);
//    glEnd();
//    
//    glutSwapBuffers();
//}
//
//void reshape(int new_w, int new_h) {
//    glViewport(0, 0, new_w, new_h);
//    float WidthFactor = (float) new_w / 300.0;
//    float HeightFactor = (float)new_h / 300.0;
//
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//
//    gluOrtho2D(-1.0 * WidthFactor, 1.0 * WidthFactor, -1.0 * HeightFactor, 1.0 * HeightFactor);
//}
//
//int main(int argc,char** argv){
//    glutInit(&argc, argv);
//    
//    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//    
//    glutInitWindowSize(250, 250);
//    glutInitWindowPosition(100, 100);
//    
//    glutCreateWindow("02_4 Timer Callback");
//    init();
//    
//    glutDisplayFunc(display);
//    glutReshapeFunc(reshape);
//    glutTimerFunc(200, timerProcess, 1);
//    glutMainLoop();
//    
//    return 0;
//}

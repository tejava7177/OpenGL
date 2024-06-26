////
////  예제파일.cpp
////  OpenGlTest
////
////  Created by 심주흔 on 2024/03/12.
////
//
//#include "예제파일.hpp"
//#define GL_SILENCE_DEPRECATION
//
//#include <iostream>
//#include <OpenGL/gl.h>
//#include <OpenGl/glu.h>
//#include <GLUT/glut.h>
//
//
//GLenum doubleBuffer;
//GLubyte ubImage[65536];
//
//static void
//Init(void)
//{
//  int j;
//  GLubyte *img;
//  GLsizei imgWidth = 128;
//
//  glMatrixMode(GL_PROJECTION);
//  glLoadIdentity();
//  gluPerspective(60.0, 1.0, 0.1, 1000.0);
//  glMatrixMode(GL_MODELVIEW);
//  glDisable(GL_DITHER);
//
//  /* Create image */
//  img = ubImage;
//  for (j = 0; j < 32 * imgWidth; j++) {
//    *img++ = 0xff;
//    *img++ = 0x00;
//    *img++ = 0x00;
//    *img++ = 0xff;
//  }
//  for (j = 0; j < 32 * imgWidth; j++) {
//    *img++ = 0xff;
//    *img++ = 0x00;
//    *img++ = 0xff;
//    *img++ = 0x00;
//  }
//  for (j = 0; j < 32 * imgWidth; j++) {
//    *img++ = 0xff;
//    *img++ = 0xff;
//    *img++ = 0x00;
//    *img++ = 0x00;
//  }
//  for (j = 0; j < 32 * imgWidth; j++) {
//    *img++ = 0x00;
//    *img++ = 0xff;
//    *img++ = 0x00;
//    *img++ = 0xff;
//  }
//}
//
///* ARGSUSED1 */
//static void
//Key(unsigned char key, int x, int y)
//{
//  switch (key) {
//  case 27:
//    exit(0);
//  }
//}
//
//void
//TexFunc(void)
//{
//  glEnable(GL_TEXTURE_2D);
//  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
//
//#if GL_EXT_abgr
//  glTexImage2D(GL_TEXTURE_2D, 0, 3, 128, 128, 0, GL_ABGR_EXT,
//    GL_UNSIGNED_BYTE, ubImage);
//
//  glBegin(GL_POLYGON);
//  glTexCoord2f(1.0, 1.0);
//  glVertex3f(-0.2, 0.8, -100.0);
//  glTexCoord2f(0.0, 1.0);
//  glVertex3f(-0.8, 0.8, -2.0);
//  glTexCoord2f(0.0, 0.0);
//  glVertex3f(-0.8, 0.2, -2.0);
//  glTexCoord2f(1.0, 0.0);
//  glVertex3f(-0.2, 0.2, -100.0);
//  glEnd();
//#endif
//
//  glTexImage2D(GL_TEXTURE_2D, 0, 3, 128, 128, 0, GL_RGBA,
//    GL_UNSIGNED_BYTE, ubImage);
//
//  glBegin(GL_POLYGON);
//  glTexCoord2f(1.0, 1.0);
//  glVertex3f(0.8, 0.8, -2.0);
//  glTexCoord2f(0.0, 1.0);
//  glVertex3f(0.2, 0.8, -100.0);
//  glTexCoord2f(0.0, 0.0);
//  glVertex3f(0.2, 0.2, -100.0);
//  glTexCoord2f(1.0, 0.0);
//  glVertex3f(0.8, 0.2, -2.0);
//  glEnd();
//
//  glDisable(GL_TEXTURE_2D);
//}
//
//static void
//Draw(void)
//{
//
//  glClearColor(0.0, 0.0, 0.0, 1.0);
//  glClear(GL_COLOR_BUFFER_BIT);
//
//#if GL_EXT_abgr
//  glRasterPos3f(-0.8, -0.8, -1.5);
//  glDrawPixels(128, 128, GL_ABGR_EXT, GL_UNSIGNED_BYTE, ubImage);
//#endif
//
//  glRasterPos3f(0.2, -0.8, -1.5);
//  glDrawPixels(128, 128, GL_RGBA, GL_UNSIGNED_BYTE, ubImage);
//
//  TexFunc();
//
//  if (doubleBuffer) {
//    glutSwapBuffers();
//  } else {
//    glFlush();
//  }
//}
//
//static void
//Args(int argc, char **argv)
//{
//  GLint i;
//
//  doubleBuffer = GL_TRUE;
//
//  for (i = 1; i < argc; i++) {
//    if (strcmp(argv[i], "-sb") == 0) {
//      doubleBuffer = GL_FALSE;
//    } else if (strcmp(argv[i], "-db") == 0) {
//      doubleBuffer = GL_TRUE;
//    }
//  }
//}
//
//int
//main(int argc, char **argv)
//{
//  GLenum type;
//
//  glutInit(&argc, argv);
//  Args(argc, argv);
//
//  type = GLUT_RGB;
//  type |= (doubleBuffer) ? GLUT_DOUBLE : GLUT_SINGLE;
//  glutInitDisplayMode(type);
//  glutCreateWindow("ABGR extension");
//  if (!glutExtensionSupported("GL_EXT_abgr")) {
//    printf("Couldn't find abgr extension.\n");
//    exit(0);
//  }
//#if !GL_EXT_abgr
//  printf("WARNING: client-side OpenGL has no ABGR extension support!\n");
//  printf("         Drawing only RGBA (and not ABGR) images and textures.\n");
//#endif
//  Init();
//  glutKeyboardFunc(Key);
//  glutDisplayFunc(Draw);
//  glutMainLoop();
//  return 0;             /* ANSI C requires main to return int. */
//}

#include <GL/glut.h>

//


void draw_triangle() {
	glBegin(GL_LINE_LOOP);
	glVertex2f(0.0, 25.0);
	glVertex2f(25.0, -25.0);
	glVertex2f(-25.0, -25.0);
	glEnd();
}

void draw_line() {
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(-50.0, 0.0);
	glVertex2f(50.0, 0.0);
	glVertex2f(0.0, -50.0);
	glVertex2f(0.0, 50.0);
	
	glEnd();
}

void display(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	draw_line();
	glColor3f(1.0, 1.0, 1.0);
	draw_triangle();

	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, 0xF0F0);
	glLoadIdentity();
	glTranslatef(-20.0, 0.0, 0.0);
	draw_triangle();

	glLineStipple(1, 0xF00F);
	glLoadIdentity();
	glScalef(1.5, 0.5, 1.0);
	draw_triangle();

	glLineStipple(1, 0x8888);
	//glLoadIdentity();					//초기화를 하지 않으면 영향을 미친다.
	glRotatef(90.0, 0.0, 0.0,1.0);
	draw_triangle();

	glDisable(GL_LINE_STIPPLE);
	glFlush();
}

void myinit(void) {
	glShadeModel(GL_FLAT);
}

void myReshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-50.0, 50.0, -50.0 * (GLfloat)h / (GLfloat)w, 50.0 * (GLfloat)h / (GLfloat)w, -1.0, 1.0);
	else
		glOrtho(-50.0 * (GLfloat)w / (GLfloat)h, 50.0 * (GLfloat)w / (GLfloat)h, -50.0, 50.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(300, 300);


	glutCreateWindow("Object Transformation Program");
	myinit();
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}

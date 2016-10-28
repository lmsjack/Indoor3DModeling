#include <Windows.h>
#include <gl/glut.h>
#include <gl/GL.h>
#include <iostream>
#include <ctime>
#include <cmath>
#include <string>
#include "texture.h"
using namespace std;

#define TEXSIZE 16

GLubyte myTex[TEXSIZE][TEXSIZE][3];

GLfloat mat_specular[] = { 1.0, 1.0f, 1.0f, 1.0f };
GLfloat mat_diffuse[] = { 0.0, 1.0f, 1.0f, 1.0f };
GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 120.0};

GLfloat lit_specular[] = { 1.0, 1.0f, 1.0f, 1.0f };
GLfloat lit_diffuse[] = { 0.0, 1.0f, 1.0f, 1.0f };
GLfloat lit_ambient[] = { 0.5, 0.0f, 0.0f, 1.0f };

GLfloat light_position[] = { 1.0,1.0f,1.0f,0.0f };

GLuint tex[] = { 1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0 };
GLuint tex1, tex2;

void LightSet(void) {
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glLightfv(GL_LIGHT0, GL_SPECULAR, lit_specular);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lit_diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lit_ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}
void init(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(512, 512);
	glutCreateWindow("test");
	glClearColor(0.7, 0.7, 0.7, 1.0);
	LightSet();
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1.0, 0.1, 100.0);
}

void CreateTexture(void) {
	for (int i = 0; i < TEXSIZE; i++) {
		for (int j = 0; j < TEXSIZE; j++) {
			for (int k = 0; k < 3; k++) {
				myTex[i][j][k] = (GLubyte)(255 * float(rand() % 1000)/ 999.0);
			}
		}
	}
}

//void SetupTexture(void)
//{
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXSIZE, TEXSIZE, 0, GL_RGB, GL_UNSIGNED_BYTE, &myTex[0][0][0]);
//
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glEnable(GL_TEXTURE_2D);
//}

void drawAPlane(void) {
	float m = -1;
	float p = 1;
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex3f(m, p, 0);
	glTexCoord2f(0, 0);
	glVertex3f(m, m, 0);
	glTexCoord2f(1, 0);
	glVertex3f(p, m, 0);
	glTexCoord2f(1, 1);
	glVertex3f(p, p, 0);
	glEnd();
}

void drawRect(int num, double radius) {
	double deg1 = num / 8. * 2. * 3.14159, deg2 = (num+1) / 8. * 2. * 3.14159;
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(radius*cos(deg1), radius*sin(1./6 * 2 * 3.14159), radius*sin(deg1));
	glTexCoord2f(0, 1);
	glVertex3f(radius*cos(deg1), radius*sin(-1. / 6 * 2 * 3.14159), radius*sin(deg1));
	glTexCoord2f(1, 1);
	glVertex3f(radius*cos(deg2), radius*sin(-1. / 6 * 2 * 3.14159), radius*sin(deg2));
	glTexCoord2f(1, 0);
	glVertex3f(radius*cos(deg2), radius*sin(1. / 6 * 2 * 3.14159), radius*sin(deg2));
	glEnd();
}

void LightPositioning(void)
{
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

void display() {
	static float t = 0.0;
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1*sin(t), 0, 1*cos(t), 0, 0, 0, 0, 1, 0);
	t += 0.001;
	LightPositioning();
	//glBindTexture(GL_TEXTURE_2D, tex1);
	for (int i = 0; i < 8; i++) {
		glBindTexture(GL_TEXTURE_2D, tex[i]);
		drawRect(i, 5.0);
	}
	//drawAPlane();
	//glBindTexture(GL_TEXTURE_2D, tex2);
	//glutSolidTeapot(1.0);
	glutSwapBuffers();
}

int main(int argc, char * argv[]) {
	//srand((unsigned)time(NULL));
	init(argc, argv);
	//tex1 = setTexture("1.jpg");
	//tex2 = setTexture("2.jpg");
	for (int i = 0; i < 8; i++) {
		tex[i] = setTexture((char *)((to_string(i + 1) + ".jpg").c_str()));
	}
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutMainLoop();
	return 0;
}
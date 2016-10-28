#include <Windows.h>
#include <gl/glut.h>
#include <gl/GL.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cmath>
#include <string>
#include "texture.h"
using namespace std;

GLfloat mat_specular[] = { 1.0, 1.0f, 1.0f, 1.0f };
GLfloat mat_diffuse[] = { 0.0, 1.0f, 1.0f, 1.0f };
GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 120.0 };

GLfloat lit_specular[] = { 1.0, 1.0f, 1.0f, 1.0f };
GLfloat lit_diffuse[] = { 0.0, 1.0f, 1.0f, 1.0f };
GLfloat lit_ambient[] = { 0.5, 0.0f, 0.0f, 1.0f };

GLfloat light_position[] = { 1.0,1.0f,1.0f,0.0f };

GLuint tex1;
struct vertexPoint {
	GLfloat x;
	GLfloat y;
	GLfloat z;

	vertexPoint(GLfloat nx, GLfloat ny, GLfloat nz) :x(nx), y(ny), z(nz) {};
};

vector<vertexPoint> pointCloud;

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


void LightPositioning(void)
{
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

void drawStrip(int div) {
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < pointCloud.size()/ div; i++) {
		glVertex3f(pointCloud[i*div].x/100, pointCloud[i*div].y/100, pointCloud[i*div].z/100);
	}
	glEnd();
}

void display() {
	static float t = 0.0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1 * sin(t), 0, 1 * cos(t), 0, 0, 0, 0, 1, 0);
	t += 0.001;
	LightPositioning();
	glBindTexture(GL_TEXTURE_2D, tex1);
	drawStrip(30);
	glutSwapBuffers();
}

int main(int argc, char * argv[]) {
	init(argc, argv);
	tex1 = setTexture("001.jpg");

	ifstream inFile;
	inFile.open("001.txt");
	while (!inFile.eof())
	{
		GLfloat x, y, z;
		inFile >> x >> y >> z;
		pointCloud.push_back(vertexPoint(x, y, z));
	}
	inFile.close();

	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutMainLoop();
	return 0;
}
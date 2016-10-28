#include <Windows.h>
#include <gl/glut.h>
#include <gl/GL.h>
#include <iostream>
#include <fstream>
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

GLuint tex[] = { 1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0 };
//GLuint tex1;
GLfloat readvertex[1080*1920*3], vertex[1080 * 1920 * 3];
int ct = 0;

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

void drawStrip(int ct) {
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < ct; i++) {
		glVertex3f(vertex[i*3], vertex[i * 3 + 1], vertex[i * 3 + 2]);
	}
	glEnd();
}

void display() {
	static float t = 0.0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.5, 0, 0.5, 0, 0, 0, 0, 1, 0);
	LightPositioning();
	//glBindTexture(GL_TEXTURE_2D, tex1);
	drawStrip(ct);
	glutSwapBuffers();
}

int main(int argc, char * argv[]) {
	init(argc, argv);
	//tex1 = setTexture("001.jpg");

	ifstream inFile;
	inFile.open("001.txt");
	for (int i = 0; i < 1080; i++) {
		for (int j = 0; j < 1920; j++) {
			double x, y, z;
			if (inFile.eof())
				break;
			inFile >> x >> y >> z;
			if (inFile.eof())
				break;
			readvertex[i * 1920 + j * 3] = (float)x;
			
			readvertex[i * 1920 + j * 3 + 1] = (float)y;
			
			readvertex[i * 1920 + j * 3 + 2] = (float)z;
		}
		cout << i <<" rows"<< endl;
	}
	inFile.close();

	for (int i = 0; i < 1080 * 1920 * 3; i++)
		vertex[i] = 0;
	int count = 0;
	for (int i = 0; i < 1080; i++) {
		for (int j = 0; j < 1920; j++) {
			if (readvertex[i * 1920 + j * 3] != 10) {
				vertex[3*count] = readvertex[i * 1920 + j * 3];
				vertex[3*count + 1] = readvertex[i * 1920 + j * 3 + 1];
				vertex[3*count + 2] = readvertex[i * 1920 + j * 3 + 2];
				count++;
				cout << count << " points" << endl;
			}
			
		}
	}
	ct = count;

	ofstream outFile;
	outFile.open("vertexFloat.bin", ios::binary | ios::trunc | ios::out);
	for (int i = 0; i < count * 3 / 1024; i++)
		outFile.write((char *)vertex, 1024);
	outFile.write((char *)vertex, count * 3 % 1024);
	outFile.close();

	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutMainLoop();
	return 0;
}
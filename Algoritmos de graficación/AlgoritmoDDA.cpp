// Nombre               : AlgoritmoDDA.cpp
// Propósito            : Programa para graficar lineas utilizando el Algoritmo DDA.
// Autor                : Ricardo J. Castillo López
// Fecha de creación    : 
// Fecha de modificación: 

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL\glut.h>

#define WIDTH 500
#define HEIGHT 500

using namespace std;

// Función para graficar un pixel:
void Pixel(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

// Función para graficar una linea utilizando el algoritmo DDA:
int AlgoritmoDDA(int x_a, int y_a, int x_b, int y_b) {
	int x0, xn, y0, yn;
	// Identificar x0 y xn:
	if (x_a <= x_b) {
		x0 = x_a; y0 = y_a;
		xn = x_b; yn = y_b;
	}
	else {
		x0 = x_b; y0 = y_b;
		xn = x_a; yn = y_a;
	}

	int dx = xn - x0, dy = yn - y0;
	float m = (float)dy / dx; 
	float x = x0, y = y0;
	int sgn, steps;
	if (dx != 0) {
		if (m >= 0) sgn = 1;
		else sgn = -1;
		if (abs(m) <= 1) { // Primer caso
			steps = dx;
			for (int k = 0; k <= steps; k++) {
				Pixel(x, round(y));
				x++;
				y += m;
			}
		}
		else { // Segundo caso
			steps = abs(dy);
			for (int k = 0; k <= steps; k++) {
				Pixel(round(x), y);
				x += abs(1 / m);
				y += sgn * 1;
			}
		}
	}
	else { // Tercer caso: Linea vertical.
		if (dy >= 0) sgn = 1;
		else sgn = -1;
		steps = abs(dy);
		for (int k = 0; k <= steps; k++) {
			Pixel(x, y);
			y += sgn * 1;
		}
	}
	return 0;
}

// Ejes coordenados:
void ejes(void) {
	glBegin(GL_LINES);
	glVertex2d(0, 250);
	glVertex2d(0, -250);
	glVertex2d(-250, 0);
	glVertex2d(250, 0);
	glEnd();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);  // Color azul
	ejes();
	// Graficar lineas:
	glPointSize(2.0);
	glColor3f(1.0, 0.0, 0.0);
	AlgoritmoDDA(-200, -200, -200, 200); // Linea vertical
	glColor3f(0.0, 1.0, 0.0);
	AlgoritmoDDA(-190, -190, 190, -190); // Linea horizontal
	glColor3f(1.0, 0.0, 1.0);
	AlgoritmoDDA(-160, -160, 50, 180);  // Pendiente positiva m > 1
	AlgoritmoDDA(-160, -160, 170, -90); // Pendiente positiva 0 < m < 1
	glColor3f(0.0, 1.0, 1.0);
	AlgoritmoDDA(170, -130, -130, 140); // Pendiente negativa abs(m) > 1
	AlgoritmoDDA(170, -130, -50, -90); // Pendiente negativa 0 < abs(m) < 1
	glColor3f(1.0, 1.0, 0.0);
	// Triángulo:
	AlgoritmoDDA(50, 50, 200, 50);
	AlgoritmoDDA(50, 50, 125, 170);
	AlgoritmoDDA(125, 170, 200, 50);
	glFlush();
	cout << "Presionar Esc para cerrar la ventana...";
}

void keyInput(unsigned char key, int x, int y) {
	switch (key) {
	case 27: // Esc
		exit(0);
		break;
	default:
		break;
	}
}

void setup() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-250, 250, -250.0, 250.0);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(450, 100);
	glutCreateWindow("Algoritmo DDA para graficar lineas");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyInput);
	setup();
	glutMainLoop();
	return(0);
}
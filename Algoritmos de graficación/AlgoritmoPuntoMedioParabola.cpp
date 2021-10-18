// Nombre               : AlgoritmoPuntoMedioParabola.cpp
// Propósito            : Programa para graficar parábolas utilizando el Algoritmo del Punto Medio.
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

// Función para graficar una parábola utilizando el algoritmo del punto medio:
int AlgoritmoPuntoMedioParabola(int h, int k, float p, int n) {
	// p: distancia focal, n: número de pixeles
	int x = 0, y = 0; // Punto inicial
	float pk = 2 * p;
	while (x <= n) {
		Pixel(h + x, k + y); 
		Pixel(h + x, k - y);  // Por simetria.
		x++;
		if (pk <= 0) {
			pk += 2 * p;
		}
		else {
			y++;
			pk += 2 * p - 2 * y;
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
	// Graficar parábolas:
	glPointSize(2.0);
	glColor3f(1.0, 0.5, 0.0);
	AlgoritmoPuntoMedioParabola(0, 0, 2.5, 250);
	glColor3f(0.0, 1.0, 1.0);
	AlgoritmoPuntoMedioParabola(0, 0, 5, 250);
	glColor3f(0.0, 1.0, 0.0);
	AlgoritmoPuntoMedioParabola(0, 0, 10, 250);
	glColor3f(1.0, 0.0, 1.0);
	AlgoritmoPuntoMedioParabola(-150, -150, 5, 400);
	glColor3f(1.0, 0.0, 0.0);
	AlgoritmoPuntoMedioParabola(-200, 30, 3, 450);
	glColor3f(1.0, 1.0, 0.0);
	AlgoritmoPuntoMedioParabola(50, 150, 2, 200);
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
	glutCreateWindow("Algoritmo del Punto Medio para graficar parábolas");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyInput);
	setup();
	glutMainLoop();
	return(0);
}
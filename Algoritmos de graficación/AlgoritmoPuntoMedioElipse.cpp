// Nombre               : AlgoritmoPuntoMedioElipse.cpp
// Propósito            : Programa para graficar elipses utilizando el Algoritmo del Punto Medio.
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

// Función para graficar una elipse utilizando el algoritmo del punto medio:
int AlgoritmoPuntoMedioElipse(int h, int k, int a, int b) {
	// a: eje mayor, b: eje menor
	int x = 0, y = b; // Punto inicial
	float pk = b * b - 1.0 * a * a * (b - 0.25);
	while (b * b * x <= a * a * y) {  // Región 1.
		Pixel(h + x, k + y);  // Primer cuadrante.
		Pixel(h + x, k - y);  // Segundo cuadrante.
		Pixel(h - x, k - y);  // Tercer cuadrante.
		Pixel(h - x, k + y);  // Cuarto cuadrante.
		x++;
		if (pk <= 0) {
			pk += 2 * b * b * x + b * b;
		}
		else {
			y--;
			pk += 2 * b * b * x - 2 * a * a * y + b * b;
		}
	}

	pk = b * b * pow(x + 0.5, 2) + 1.0 * a * a * pow(y - 1, 2) - 1.0 * a * a * b * b;
	while (b * b * x > a * a * y && y != -1)  // Región 2.
	{
		Pixel(h + x, k + y);  // Primer cuadrante.
		Pixel(h + x, k - y);  // Segundo cuadrante.
		Pixel(h - x, k - y);  // Tercer cuadrante.
		Pixel(h - x, k + y);  // Cuarto cuadrante.
		y--;
		if (pk <= 0) {
			x++;
			pk += 2 * b * b * x - 2 * a * a * y + a * a;
		}
		else {
			pk += -2 * a * a * y + a * a;
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
	// Graficar elipses:
	glPointSize(2.0);
	glColor3f(1.0, 0.5, 0.0);
	AlgoritmoPuntoMedioElipse(125, 125, 100, 35);
	glColor3f(0.0, 1.0, 1.0);
	AlgoritmoPuntoMedioElipse(0, 0, 125, 35);
	glColor3f(0.0, 1.0, 0.0);
	AlgoritmoPuntoMedioElipse(-50, 0, 185, 50);
	glColor3f(1.0, 0.0, 1.0);
	AlgoritmoPuntoMedioElipse(0, 0, 70, 175);
	glColor3f(1.0, 0.0, 0.0);
	AlgoritmoPuntoMedioElipse(50, -150, 180, 40);
	glColor3f(1.0, 1.0, 0.0);
	AlgoritmoPuntoMedioElipse(-50, 150, 180, 40);
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
	glutCreateWindow("Algoritmo del Punto Medio para graficar elipses");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyInput);
	setup();
	glutMainLoop();
	return(0);
}
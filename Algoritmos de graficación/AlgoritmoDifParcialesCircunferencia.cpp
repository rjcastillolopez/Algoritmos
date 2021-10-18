// Nombre               : AlgoritmoDifParcialesCircunferencia.cpp
// Propósito            : Programa para graficar circunferencias utilizando el Algoritmo de Diferencias Parciales.
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

// Función para graficar una circunferencia utilizando el algoritmo del diferencias parciales:
int AlgoritmoDifParcialesCircunferencia(int h, int k, int r) {
	int x = 0, y = r; // Punto inicial
	int dE = 3, dSE = 5 - 2 * r;
	int pk = 1 - r;
	while (x <= y) {
		Pixel(h + x, k + y);  // Primer octante.
		Pixel(h + y, k + x);  // Segundo octante.
		Pixel(h + y, k - x);  // Tercer octante.
		Pixel(h + x, k - y);  // Cuarto octante.
		Pixel(h - x, k - y);  // Quinto octante.
		Pixel(h - y, k - x);  // Sexto octante.
		Pixel(h - y, k + x);  // Séptimo octante.
		Pixel(h - x, k + y);  // Octavo octante.
		x++;
		if (pk <= 0) {
			pk += dE;
			dE = dE + 2;
			dSE = dSE + 2;
		}
		else {
			y--;
			pk += dSE;
			dE = dE + 2;
			dSE = dSE + 4;
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
	// Graficar circunferencias:
	glPointSize(2.0);
	glColor3f(1.0, 0.5, 0.0);
	AlgoritmoDifParcialesCircunferencia(125, 125, 70);
	glColor3f(0.0, 1.0, 1.0);
	AlgoritmoDifParcialesCircunferencia(0, 0, 100);
	glColor3f(0.0, 1.0, 0.0);
	AlgoritmoDifParcialesCircunferencia(50, 25, 120);
	glColor3f(1.0, 0.0, 1.0);
	AlgoritmoDifParcialesCircunferencia(-125, 125, 120);
	glColor3f(1.0, 0.0, 0.0);
	AlgoritmoDifParcialesCircunferencia(-100, -100, 135);
	glColor3f(1.0, 1.0, 0.0);
	AlgoritmoDifParcialesCircunferencia(65, -65, 160);
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
	glutCreateWindow("Algoritmo de Diferencias Parciales para graficar circunferencias");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyInput);
	setup();
	glutMainLoop();
	return(0);
}
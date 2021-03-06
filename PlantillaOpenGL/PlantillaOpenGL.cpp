// PlantillaOpenGL.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

using namespace std;

float posicionXTriangulo = 0;
float posicionYTriangulo = 0;
float angulo = 0.0f;

enum Direccion {Izquierda,Derecha,Arriba,Abajo};
Direccion direccionHorizontalTriangulo = Direccion::Izquierda;
Direccion direccionVerticalTriangulo = Direccion::Abajo;

void dibujarTriangulo() {
	//Utilizar Matrizz Identidad
	glPushMatrix();
	//Transformaciones
	glTranslatef(posicionXTriangulo, posicionYTriangulo, 0.0);
	glRotatef(angulo, 0.0f, 1.0f,0.0f);
	//glScalef(0.2f, 0.2f, 0.2f);
	//glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
	//Dibujar los verticez
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.8f, 0.0f);
	glVertex3f(-0.2f, -0.2f, 0);
	glVertex3f(0.2f, -0.2f, 0);
	glVertex3f(0.0f, 0.2f, 0);
	glEnd();

	//Soltar la Matriz
	glPopMatrix();
}



void dibujar() {
	dibujarTriangulo();
	
}


void actualizar() {
	angulo += 0.1f;
	if (angulo >= 360) {
		angulo += 0.1f;
	}
	if (direccionHorizontalTriangulo == Direccion::Izquierda) {
		if (posicionXTriangulo > -0.8f) {
			posicionXTriangulo -= 0.1f;
		}
		else {
			direccionHorizontalTriangulo = Direccion::Derecha;
		}
	}
	if (direccionHorizontalTriangulo == Direccion::Derecha) {
		if (posicionXTriangulo < 0.8f) {
			posicionXTriangulo += 0.1;
		}
		else {
			direccionHorizontalTriangulo = Direccion::Izquierda;
		}
	}


	if (direccionVerticalTriangulo == Direccion::Abajo) {
		if (posicionYTriangulo > -0.4f) {
			posicionYTriangulo -= 0.1f;
		}
		else {
			direccionVerticalTriangulo = Direccion::Arriba;
		}
	}
	if (direccionVerticalTriangulo == Direccion::Arriba) {
		if (posicionYTriangulo < 0.4f) {
			posicionYTriangulo += 0.1f;
		}
		else {
			direccionVerticalTriangulo = Direccion::Abajo;
		}
	}
	
}

int main()
{
	//Declaramos apuntador de ventana
	//TErminar ejecucion
	GLFWwindow *window;

	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	//si se pudo iniciar el GLFW
	//entonces inicializamos la ventana
	window = glfwCreateWindow(1024, 768,"Ventana", NULL, NULL);
	//si no podemos iniciar la ventana 
	//entonces erminamos la ejecucion
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//Establecemos el contexto
	glfwMakeContextCurrent(window);

	//Una vez establecido el contexto
	//Activamos funciones modernas
	glewExperimental = true;
	GLenum errorGlew = glewInit();
	if (errorGlew != GLEW_OK) {
		cout << glewGetErrorString(errorGlew);
	}
	const GLubyte * versionGL = glGetString(GL_VERSION);
	cout << "Version OpenGL: " << versionGL;


	//ciclo de dibujo (Draw loop)
	while (!glfwWindowShouldClose(window)) {
		//Establecer region de dibujo
		glViewport(0, 0, 1024, 768);
		//establecer el color de borrado
		glClearColor(.2, .5, 1, 1);
		//Borramos
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Rutina de dibujo
		dibujar();
		actualizar();
		//Cambiar los buffers
		glfwSwapBuffers(window);
		//Reconocer si hay entradas
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

    return 0;
}


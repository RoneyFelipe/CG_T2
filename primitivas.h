#pragma once
#include<vector>
#include<cmath>
#include "vec.h"

void rect(vec3 p1, vec3 p2, vec3 p3, vec3 p4, color cor){
	glColor3fv(cor);
	glBegin(GL_QUADS);
	glVertex3fv(&p1.x);
	glVertex3fv(&p2.x);
	glVertex3fv(&p3.x);
	glVertex3fv(&p4.x);
	glEnd();
}

void desenhaCubo(GLuint id,float s)
{
	float d = s / 2.0;

	vec3 v1(-d, d, d);
	vec3 v2(-d, -d, d);
	vec3 v3(d, -d, d);
	vec3 v4(d, d, d);

	vec3 v5(d, d, -d);
	vec3 v6(d, -d, -d);
	vec3 v7(-d, -d, -d);
	vec3 v8(-d, d, -d);

	glNewList(id, GL_COMPILE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glNormal3f(0.f,0.f,1.f);
	rect(v1, v2, v3, v4, vermelho);

	glNormal3f(1.f,0.f,0.f);
	rect(v4, v3, v6, v5, azul);

	glNormal3f(0.f,0.f,-1.f);
	rect(v5, v8, v7, v6, amarelo);

	glNormal3f(-1.f,0.f,0.f);
	rect(v1, v8, v7, v2, verde);

	glNormal3f(0.f,1.f,0.f);
	rect(v1, v4, v5, v8, laranja);

	glNormal3f(0.f,-1.f,0.f);
	rect(v2, v7, v6, v3, violeta);

	glEndList();
}

void desenhaRetangulo(GLuint id,float s)
{

	float d = s / 2.0;

	vec3 v1(-d, d, d);
	vec3 v2(-d, -d, d);
	vec3 v3(d, -d, d);
	vec3 v4(d, d, d);

	vec3 v5(d, 2*d, -d);
	vec3 v6(d, 2*-d, -d);
	vec3 v7(-d, 2*-d, -d);
	vec3 v8(-d, 2*d, -d);

	
	glNewList(id, GL_COMPILE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glNormal3f(0.f,0.f,1.f);
	rect(v1, v2, v3, v4, vermelho);

	glNormal3f(1.f,0.f,0.f);
	rect(v4, v3, v6, v5, azul);

	glNormal3f(0.f,0.f,-1.f);
	rect(v5, v8, v7, v6, amarelo);

	glNormal3f(-1.f,0.f,0.f);
	rect(v1, v8, v7, v2, verde);

	glNormal3f(0.f,1.f,1.f);
	rect(v1, v4, v5, v8, laranja);

	glNormal3f(0.f,-1.f,0.f);
	rect(v2, v7, v6, v3, violeta);

	glEndList();
}

//Sugestão, remover tudo isso aqui relacionado a esfera.
void desenhaEsfera(unsigned int& id, GLfloat raio, GLuint nStacks, GLuint nSectors)
{
	std::vector< std::vector<GLuint> > indices;
	std::vector<vec3> pontos;
	const GLfloat PI = 3.14159265359;

	GLfloat deltaPhi = PI / nStacks;
	GLfloat deltaTheta = 2 * PI / nSectors;

	for (GLuint i = 0; i <= nStacks; i++)
	{
		GLfloat phi = -PI / 2.0 + i * deltaPhi;
		GLfloat temp = raio * cos(phi);
		GLfloat y = raio * sin(phi);
		
		std::vector<GLuint> pt;

		for (GLuint j = 0; j < nSectors; j++)
		{
			GLfloat theta = j * deltaTheta;
			GLfloat x = temp * sin(theta);
			GLfloat z = temp * cos(theta);

			pontos.push_back(vec3(x, y, z));
			GLuint index = pontos.size() - 1;
			pt.push_back(index);
		}

		indices.push_back(pt);
	}

	glNewList(id,GL_COMPILE);
	
	glColor3fv(verde);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	//para ver como malha triangula
	
	for (GLuint i = 0; i < nStacks; i++){
		glBegin(GL_TRIANGLE_STRIP);

		for (GLuint j = 0; j < nSectors; j++){

			GLuint index = indices[i][j];
			glVertex3fv(&pontos[index].x);
			index = indices[i + 1][j];
			glVertex3fv(&pontos[index].x);

			if (j == nSectors - 1)				{
				index = indices[i][0];
				glVertex3fv(&pontos[index].x);
				index = indices[i+1][0];
				glVertex3fv(&pontos[index].x);
			}
		}
		glEnd();
	}

	// --- plota pontos 
	// glColor3fv(vermelho);
	// glPointSize(2.5);
	// glBegin(GL_POINTS);
	// for (GLuint i = 0; i < pontos.size(); i++)
	// {
	// 	glVertex3fv(&pontos[i].x);
	// }
	// glEnd();

	glEndList();
}

void desenhaPiramide(GLuint id, float s) {
    float d = s / 2.0;
    vec3 v1(0, d, 0);
    vec3 v2(-d, -d, d);
    vec3 v3(d, -d, d);
    vec3 v4(d, -d, -d);
    vec3 v5(-d, -d, -d);

	glNewList(id, GL_COMPILE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	float matEspecular[] = {1.f, 1.f, 1.f, 1.f};
	glLightfv(GL_FRONT, GL_SPECULAR, matEspecular);
	glMaterialf(GL_FRONT, GL_SHININESS, 128);

    // Base da pirâmide
    rect(v2, v3, v4, v5, vermelho);

    // Faces laterais
	//Frente
	glNormal3f(0.f,0.f,1.f);
    rect(v1, v2, v3, v1, azul);

	//Direita
	glNormal3f(1.f,0.f,0.f);
    rect(v1, v3, v4, v1, amarelo);

	//Back
	glNormal3f(0.f,0.f,-1.f);
    rect(v1, v4, v5, v1, verde);

	//Esquerda
	glNormal3f(-1.f,0.f,0.f);
    rect(v1, v5, v2, v1, laranja);

	glEndList();
}

void desenhaChao(unsigned int id)
{
	float L = 500.0;
	float incr = 1.0;
	float y = -0.5;
	glNewList(id, GL_COMPILE);

	glColor3fv(preto);
	//glBegin(GL_LINES);
	for (float i = -L; i <= L; i += incr)
	{
		// Verticais
		glVertex3f(i,y,-L);
		glVertex3f(i,y,L);

		// Horizontais
		glVertex3f(-L,y,i);
		glVertex3f(L,y,i);
	}
	glEnd();
	glEndList();
}
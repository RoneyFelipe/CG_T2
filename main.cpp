#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include<iostream>
#include<vector>

#include "cores.h"
#include "primitivas.h"
#include "Camera.h"

static float angulo = 0.0;
static float lastMousePos = 0.0;
static bool firstTimeMouse = true;

// Display List
struct Objeto {
	GLuint id;
	vec3 pos;
	Objeto():id(0),pos(vec3(0.0,0.0,0.0)){}
};

const GLuint total_objetos = 4;
std::vector<Objeto> objetos;

Camera camera(vec3(10.0,15.0,0.0));

void redimensiona(int w, int h)
{
	glViewport(0, 0, w, h);

	float aspect = (float)w / (float)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, aspect, 0.1, 500.0);

	glMatrixMode(GL_MODELVIEW);
}

void desenha()
{
	glLoadIdentity();

	camera.ativar();

	glPushMatrix();
	objetos[0].pos.x = -15.0;
	objetos[0].pos.y = 10.0;
	objetos[0].pos.z = -50.0;
	glTranslatef(objetos[0].pos.x, objetos[0].pos.y, objetos[0].pos.z);
	glRotatef(angulo, 0.0, 1.0, 0.0);
	glCallList(objetos[0].id);
	glPopMatrix();

	glPushMatrix();
	objetos[1].pos.x = 0.0;
	objetos[1].pos.y = 20.0;
	objetos[1].pos.z = -45.0;
	glTranslatef(objetos[1].pos.x, objetos[1].pos.y, objetos[1].pos.z);
	glRotatef(angulo, 0.0, 1.0, 0.0);
	glCallList(objetos[1].id);
	glPopMatrix();

	glPushMatrix();
	objetos[2].pos.x = 15.0;
	objetos[2].pos.y = 15.0;
	objetos[2].pos.z = -40.0;
	glTranslatef(objetos[2].pos.x, objetos[2].pos.y, objetos[2].pos.z);
	glRotatef(angulo, 0.0, 1.0, 0.0);
	glCallList(objetos[2].id);
	glPopMatrix();

	glCallList(objetos[3].id);

	angulo += 0.1;
}

void teclado_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key==GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	else if (key==GLFW_KEY_W &&(action == GLFW_PRESS || action==GLFW_REPEAT))
	{
		// para frente
		camera.forward();
	}
	else if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		// para tras
		camera.back();

	}
	else if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		// esquerda
		camera.left();

	}
	else if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		// direita
		camera.right();
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	float dx;

	if (firstTimeMouse)
	{
		dx = 0;
		lastMousePos = xpos;
		firstTimeMouse = false;
	}
	dx = xpos - lastMousePos;
	lastMousePos = xpos;
	camera.updateYaw(dx);
	camera.update();
}

void luzAmbiente() {
	float ambiente[] = {0.5f, 0.5f, 0.5f, 1.f};
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente);
}
void luzDifusa() {

	float luz_Difusa[] = {0.8f,0.8f,0.8f,1.f};
	glLightfv(GL_LIGHT1, GL_DIFFUSE, luz_Difusa);

}
void luzEspecular() {
	float matEspecular[] = {1.f, 1.f, 1.f, 1.f};
	glLightfv(GL_LIGHT1, GL_SPECULAR, matEspecular);

	glMaterialfv(GL_FRONT, GL_SPECULAR,matEspecular);
	 glMaterialf(GL_FRONT, GL_SHININESS, 128);

	
}
void phong() {
	luzDifusa();
	luzEspecular();
}

void ativarIluminacao() {
	GLfloat position[] =  {1.f,0.f,1.f,1.f};
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	
	glEnable(GL_LIGHT1);
	
 	glLightfv(GL_LIGHT1, GL_POSITION, position);
}

void init(GLFWwindow* window)
{
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetKeyCallback(window, teclado_callback);
	glClearColor(0.0, 0.0, 0.0, 0.0); // cor de fundo

	glEnable(GL_DEPTH_TEST);
	ativarIluminacao();

	// luzDifusa();
	// luzEspecular();
	phong();

	for (int i = 0; i < total_objetos;i++)
	{
		Objeto p;
		objetos.push_back(p);
	}

	objetos[0].id = glGenLists(total_objetos);
	objetos[1].id = objetos[0].id + 1;
	objetos[2].id = objetos[0].id + 2;
	objetos[3].id = objetos[0].id + 3;
	
	desenhaRetangulo(objetos[0].id, 10);
	desenhaCubo(objetos[1].id, 10);
	desenhaPiramide(objetos[2].id, 10);
	desenhaChao(objetos[3].id);
}

int main(void)
{
 
	const int LARGURA = 800;
	const int ALTURA = 600;

	/* Initialize the library */
	glfwInit();

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* window = glfwCreateWindow(LARGURA, ALTURA, "Cenário", NULL, NULL);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// -- inicio
	init(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Poll for and process events */
		glfwPollEvents();

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		int largura, altura;
		glfwGetFramebufferSize(window, &largura, &altura);

		redimensiona(largura, altura);

		desenha();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);
	}

	glDeleteLists(objetos[0].id, total_objetos);
	glfwTerminate();
	return 0;
}
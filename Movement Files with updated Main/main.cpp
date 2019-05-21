#include"lib.h"
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <iostream>
#include "movement.h"

using namespace std;

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

Vertex vertices[] = {
	//Position                            //Color                            //Texcoords

	//Base
	glm::vec3(-0.5f, 0.8f, 0.8f),          glm::vec3(1.f, 1.f, 1.f),          glm::vec2(0.f, 1.f),     //Top left
	glm::vec3(-0.5f, -0.8f, 0.8f),         glm::vec3(1.f, 1.f, 1.f),          glm::vec2(0.f, 0.f),     //Bottom left
	glm::vec3(0.5f, -0.8f, 0.8f),          glm::vec3(1.f, 1.f, 1.f),          glm::vec2(1.f, 0.f),     //Bottom right
	glm::vec3(0.5f, 0.8f, 0.8f),           glm::vec3(1.f, 1.f, 1.f),          glm::vec2(0.f, 0.f),     //Top right

	glm::vec3(-0.6f, 0.9f, 0.8f),          glm::vec3(0.5f, 1.f, 0.5f),          glm::vec2(0.f, 1.f),     //Top left
	glm::vec3(-0.6f, -0.9f, 0.8f),         glm::vec3(0.5f, 1.f, 0.5f),          glm::vec2(0.f, 0.f),     //Bottom left
	glm::vec3(0.6f, -0.9f, 0.8f),          glm::vec3(0.5f, 1.f, 0.5f),          glm::vec2(1.f, 0.f),     //Bottom right
	glm::vec3(0.6f, 0.9f, 0.8f),           glm::vec3(0.5f, 1.f, 0.5f),          glm::vec2(0.f, 0.f),     //Top right

	//Block 1
	glm::vec3(-0.5f, 0.8f, 0.f),          glm::vec3(1.f, 1.f, 0.f),          glm::vec2(1.f, 1.f),     //Top left
	glm::vec3(-0.5f, 0.16f, 0.f),         glm::vec3(1.f, 1.f, 0.f),          glm::vec2(0.f, 0.f),     //Bottom left
	glm::vec3(-0.25f, 0.16f, 0.f),        glm::vec3(0.f, 0.f, 0.f),          glm::vec2(1.f, 0.f),     //Bottom right
	glm::vec3(-0.25f, 0.8f, 0.f),         glm::vec3(1.f, 1.f, 0.f),          glm::vec2(0.f, 0.f),     //Top right

	//Block 2
	glm::vec3(-0.25f, 0.8f, 0.f),         glm::vec3(1.f, 0.f, 0.f),          glm::vec2(0.f, 1.f),     //Top left
	glm::vec3(-0.25f, 0.16f, 0.f),        glm::vec3(1.f, 0.f, 0.f),          glm::vec2(0.f, 0.f),     //Bottom left
	glm::vec3(0.25f, 0.16f, 0.f),         glm::vec3(1.f, 0.f, 0.f),          glm::vec2(1.f, 0.f),     //Bottom right
	glm::vec3(0.25f, 0.8f, 0.f),          glm::vec3(1.f, 0.f, 0.f),          glm::vec2(0.f, 0.f),     //Top right

	//Block 3
	glm::vec3(0.25f, 0.8f, 0.f),          glm::vec3(1.f, 1.f, 0.f),          glm::vec2(0.f, 1.f),     //Top left
	glm::vec3(0.25f, 0.16f, 0.f),         glm::vec3(1.f, 1.f, 0.f),          glm::vec2(0.f, 0.f),     //Bottom left
	glm::vec3(0.5f, 0.16f, 0.f),          glm::vec3(0.f, 0.f, 0.f),          glm::vec2(1.f, 0.f),     //Bottom right
	glm::vec3(0.5f, 0.8f, 0.f),           glm::vec3(1.f, 1.f, 0.f),          glm::vec2(0.f, 0.f),     //Top right

	//Block 4
	glm::vec3(-0.5f, 0.16f, 0.f),         glm::vec3(1.f, 1.f, 0.f),          glm::vec2(0.f, 1.f),     //Top left
	glm::vec3(-0.5f, -0.48f, 0.f),        glm::vec3(1.f, 1.f, 0.f),          glm::vec2(0.f, 0.f),     //Bottom left
	glm::vec3(-0.25f, -0.48f, 0.f),       glm::vec3(0.f, 0.f, 0.f),          glm::vec2(1.f, 0.f),     //Bottom right
	glm::vec3(-0.25f, 0.16f, 0.f),        glm::vec3(1.f, 1.f, 0.f),          glm::vec2(0.f, 0.f),     //Top right

	//Block 5
	glm::vec3(-0.25f, 0.16f, 0.f),        glm::vec3(1.f, 1.f, 0.f),          glm::vec2(0.f, 1.f),     //Top left
	glm::vec3(-0.25f, -0.16f, 0.f),       glm::vec3(1.f, 1.f, 0.f),          glm::vec2(0.f, 0.f),     //Bottom left
	glm::vec3(0.25f, -0.16f, 0.f),        glm::vec3(0.f, 0.f, 0.f),          glm::vec2(1.f, 0.f),     //Bottom right
	glm::vec3(0.25f, 0.16f, 0.f),         glm::vec3(1.f, 1.f, 0.f),          glm::vec2(0.f, 0.f),     //Top right

	//Block 6
	glm::vec3(-0.25f, -0.16f, 0.f),       glm::vec3(1.f, 1.f, 0.f),         glm::vec2(0.f, 1.f),     //Top left
	glm::vec3(-0.25f, -0.48f, 0.f),       glm::vec3(1.f, 1.f, 0.f),         glm::vec2(0.f, 0.f),     //Bottom left
	glm::vec3(0.0f, -0.48f, 0.f),         glm::vec3(0.f, 0.f, 0.f),         glm::vec2(1.f, 0.f),     //Bottom right
	glm::vec3(0.0f, -0.16f, 0.f),         glm::vec3(1.f, 1.f, 0.f),         glm::vec2(0.f, 0.f),     //Top right

	//Block 7
	glm::vec3(0.0f, -0.16f, 0.f),         glm::vec3(1.f, 1.f, 0.f),          glm::vec2(0.f, 1.f),     //Top left
	glm::vec3(0.0f, -0.48f, 0.f),         glm::vec3(1.f, 1.f, 0.f),          glm::vec2(0.f, 0.f),     //Bottom left
	glm::vec3(0.25f, -0.48f, 0.f),        glm::vec3(0.f, 0.f, 0.f),          glm::vec2(1.f, 0.f),     //Bottom right
	glm::vec3(0.25f, -0.16f, 0.f),        glm::vec3(1.f, 1.f, 0.f),          glm::vec2(0.f, 0.f),     //Top right

	//Block 8
	glm::vec3(0.25f, 0.16f, 0.f),         glm::vec3(1.f, 1.f, 0.f),         glm::vec2(0.f, 1.f),     //Top left
	glm::vec3(0.25f, -0.48f, 0.f),        glm::vec3(1.f, 1.f, 0.f),         glm::vec2(0.f, 0.f),     //Bottom left
	glm::vec3(0.5f, -0.48f, 0.f),         glm::vec3(0.f, 0.f, 0.f),         glm::vec2(1.f, 0.f),     //Bottom right
	glm::vec3(0.5f, 0.16f, 0.f),          glm::vec3(1.f, 1.f, 0.f),         glm::vec2(0.f, 0.f),     //Top right

	//Block 9
	glm::vec3(-0.5f, -0.48f, 0.f),        glm::vec3(1.f, 1.f, 0.f),         glm::vec2(0.f, 1.f),     //Top left
	glm::vec3(-0.5f, -0.8f, 0.f),         glm::vec3(1.f, 1.f, 0.f),         glm::vec2(0.f, 0.f),     //Bottom left
	glm::vec3(-0.25f, -0.8f, 0.f),        glm::vec3(0.f, 0.f, 0.f),         glm::vec2(1.f, 0.f),     //Bottom right
	glm::vec3(-0.25f, -0.48f, 0.f),        glm::vec3(1.f, 1.f, 0.f),         glm::vec2(0.f, 0.f),     //Top right

	//Block 10
	glm::vec3(0.25f, -0.48f, 0.f),        glm::vec3(1.f, 1.f, 0.f),          glm::vec2(0.f, 1.f),     //Top left
	glm::vec3(0.25f, -0.8f, 0.f),         glm::vec3(1.f, 1.f, 0.f),          glm::vec2(0.f, 0.f),     //Bottom left
	glm::vec3(0.5f, -0.8f, 0.f),          glm::vec3(0.f, 0.f, 0.f),          glm::vec2(1.f, 0.f),     //Bottom right
	glm::vec3(0.5f, -0.48f, 0.f),        glm::vec3(1.f, 1.f, 0.f),          glm::vec2(0.f, 0.f),      //Top right

	//Exit
	glm::vec3(-0.25f, -0.8f, 0.f),        glm::vec3(0.f, 0.f, 1.f),         glm::vec2(0.f, 0.f),    //Top left
	glm::vec3(-0.25f, -0.9f, 0.f),        glm::vec3(0.f, 0.f, 1.f),         glm::vec2(1.f, 0.f),     //Bottom left
	glm::vec3(0.25f, -0.9f, 0.f),          glm::vec3(0.f, 0.f, 1.f),          glm::vec2(1.f, 0.f),     //Bottom right
	glm::vec3(0.25f, -0.8f, 0.f),           glm::vec3(0.f, 0.f, 1.f),          glm::vec2(0.f, 0.f)    //Top right
};
unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

GLuint indices[] = {
	//Block1
	0, 1, 2,
	0, 2, 3,

	//Block 2
	4, 5, 6,
	4, 6, 7,

	//Block 3
	8, 9, 10,
	8, 10, 11,

	//Block 4
	12, 13, 14,
	12, 14, 15,

	//Block 5
	16, 17, 18,
	16, 18, 19,

	//Block 6
	20, 21, 22,
	20, 22, 23,

	//Block 7
	24, 25, 26,
	24, 26, 27,

	//Block 8
	28, 29, 30,
	28, 30, 31,

	//Block 9
	32, 33, 34,
	32, 34, 35,

	//Block 10
	36, 37, 38,
	36, 38, 39,

	//Base:
	40, 41, 42,
	40, 42, 43,

	//base 3:
	44, 45, 46,
	44, 46, 47,

	48, 49, 50,
	48, 50, 51
};
unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

void updateInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

void framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH) {
	glViewport(0, 0, fbW, fbH);
}

bool loadShaders(GLuint &program) {

	bool loadSuccess = true;
	char infoLog[512];
	GLint success;

	std::string temp = "";
	std::string src = "";

	std::ifstream in_file;

	//Vertex
	in_file.open("vertex_core.glsl");

	if (in_file.is_open()) {
		while (std::getline(in_file, temp))
			src += temp + "\n";
	}
	else {
		std::cout << "ERROR:: LOADSHADERS::COULD_NOT_OPEN_VERTEX_FILE" << "\n";
		loadSuccess = false;
	}

	in_file.close();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* vertSrc = src.c_str();
	glShaderSource(vertexShader, 1, &vertSrc, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR:: LOADSHADERS::COULD_NOT_VERTEX_SHADER" << "\n";
		std::cout << infoLog << "\n";
		loadSuccess = false;
	}

	temp = "";
	src = "";

	//Fragment
	in_file.open("fragment_core.glsl");

	if (in_file.is_open()) {
		while (std::getline(in_file, temp))
			src += temp + "\n";
	}
	else {
		std::cout << "ERROR:: LOADSHADERS::COULD_NOT_OPEN_FRAGMENT_FILE" << "\n";
		loadSuccess = false;
	}

	in_file.close();

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* fragSrc = src.c_str();
	glShaderSource(fragmentShader, 1, &fragSrc, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR:: LOADSHADERS::COULD_NOT_FRAGMENT_SHADER" << "\n";
		std::cout << infoLog << "\n";
		loadSuccess = false;
	}

	//Program
	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR:: LOADSHADERS::COULD_NOT_LINK_PROGRAM" << "\n";
		std::cout << infoLog << "\n";
		loadSuccess = false;
	}


	//END
	glUseProgram(0);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return loadSuccess;
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {

	float x = ((2.0 / SCREEN_WIDTH) * xpos) - 1.0;
	float y = (((2.0 / SCREEN_HEIGHT) * ypos) - 1.0) * -1.0;

	cout << "Xpos: " << x << " Ypos: " << y << endl;

}

int main() {

	//MOUSE START
	int state;
	int oldState = GLFW_RELEASE;
	int indexOfFirstPositionVecOfSelectedBlock;
	double xposStart;
	double yposStart;
	double xposEnd;
	double yposEnd;
	int direction;

	//MOUSE END

	//INIT GLFW
	glfwInit();

	//CREATE WINDOW

	int framebufferWidth = 0;
	int framebufferHeight = 0;

        /*

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

        */

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "KLOTSKI", NULL, NULL);

	glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);

	glfwMakeContextCurrent(window);



	//INIT GLEW (NEEDS WINDOW AND OPENGL CONTEXT)
	glewExperimental = GL_TRUE;


	//ERROR
	if (glewInit() != GLEW_OK) {
		std::cout << "ERROR::MAIN.CPP::GLEW_INIT_FAILED" << "\n";
		glfwTerminate();
	}


	//OPENGL OPTIONS
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//SHADER INIT
	GLuint core_program;
	if (!loadShaders(core_program))
		glfwTerminate();


	//VAO, VBO, EBO
	//GEN VAO AND BIND
	GLuint VAO;    // Vertex Array Object
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);


	//Gen VAO AND BIND
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	//GEN EBO AND BIND AND SEND DATA
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//SET VERTEXATTRIBPOINTERS AND ENABLE (INPUT ASSEMBLY)
	//Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);
	//Texcoord
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
	glEnableVertexAttribArray(2);

	//BIND VAO 0
	glBindVertexArray(0);




	//MAIN LOOP
	while (!glfwWindowShouldClose(window)) {


		

		// MOUSE START

		//glfwSetCursorPosCallback(window, cursor_position_callback);



		state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

		if (state == GLFW_PRESS && oldState == GLFW_RELEASE) {

			glfwGetCursorPos(window, &xposStart, &yposStart);

			xposStart = ((2.0 / SCREEN_WIDTH) * xposStart) - 1.0;
			yposStart = (((2.0 / SCREEN_HEIGHT) * yposStart) - 1.0) * -1.0;

			indexOfFirstPositionVecOfSelectedBlock = selectBlock(xposStart, yposStart, vertices);

			cout << "  SELECTED BLOCK: " << indexOfFirstPositionVecOfSelectedBlock;

		}

		else if(state == GLFW_RELEASE && oldState == GLFW_PRESS) {
		
			glfwGetCursorPos(window, &xposEnd, &yposEnd);

			xposEnd = ((2.0 / SCREEN_WIDTH) * xposEnd) - 1.0;
			yposEnd = (((2.0 / SCREEN_HEIGHT) * yposEnd) - 1.0) * -1.0;

			direction = getDirection(xposEnd, yposEnd, indexOfFirstPositionVecOfSelectedBlock, vertices);

			if (isSpaceEmpty(direction, xposEnd, yposEnd, indexOfFirstPositionVecOfSelectedBlock, vertices)) {

				cout << "  SELECTED BLOCK: " << indexOfFirstPositionVecOfSelectedBlock;

				cout << "  Direction: " << direction;

				switch (direction) {

				case 1:

					moveLeft(VAO, VBO, EBO, indices, indexOfFirstPositionVecOfSelectedBlock, state, vertices);

					// Vertex Array Object
					glGenVertexArrays(1, &VAO);
					glBindVertexArray(VAO);

					//Gen VAO AND BIND
					glGenBuffers(1, &VBO);
					glBindBuffer(GL_ARRAY_BUFFER, VBO);
					glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


					//GEN EBO AND BIND AND SEND DATA
					glGenBuffers(1, &EBO);
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

					//SET VERTEXATTRIBPOINTERS AND ENABLE (INPUT ASSEMBLY)
					//Position
					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
					glEnableVertexAttribArray(0);
					//Color
					glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
					glEnableVertexAttribArray(1);
					//Texcoord
					glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
					glEnableVertexAttribArray(2);

					//BIND VAO 0
					glBindVertexArray(0);

					break;

				case 2:

					moveRight(VAO, VBO, EBO, indices, indexOfFirstPositionVecOfSelectedBlock, state, vertices);

					// Vertex Array Object
					glGenVertexArrays(1, &VAO);
					glBindVertexArray(VAO);


					//Gen VAO AND BIND
					glGenBuffers(1, &VBO);
					glBindBuffer(GL_ARRAY_BUFFER, VBO);
					glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


					//GEN EBO AND BIND AND SEND DATA
					glGenBuffers(1, &EBO);
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

					//SET VERTEXATTRIBPOINTERS AND ENABLE (INPUT ASSEMBLY)
					//Position
					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
					glEnableVertexAttribArray(0);
					//Color
					glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
					glEnableVertexAttribArray(1);
					//Texcoord
					glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
					glEnableVertexAttribArray(2);

					//BIND VAO 0
					glBindVertexArray(0);

					break;

				case 3:

					moveUp(VAO, VBO, EBO, indices, indexOfFirstPositionVecOfSelectedBlock, state, vertices);

					// Vertex Array Object
					glGenVertexArrays(1, &VAO);
					glBindVertexArray(VAO);


					//Gen VAO AND BIND
					glGenBuffers(1, &VBO);
					glBindBuffer(GL_ARRAY_BUFFER, VBO);
					glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


					//GEN EBO AND BIND AND SEND DATA
					glGenBuffers(1, &EBO);
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

					//SET VERTEXATTRIBPOINTERS AND ENABLE (INPUT ASSEMBLY)
					//Position
					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
					glEnableVertexAttribArray(0);
					//Color
					glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
					glEnableVertexAttribArray(1);
					//Texcoord
					glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
					glEnableVertexAttribArray(2);

					//BIND VAO 0
					glBindVertexArray(0);

					break;

				case 4:

					moveDown(VAO, VBO, EBO, indices, indexOfFirstPositionVecOfSelectedBlock, state, vertices);

					// Vertex Array Object
					glGenVertexArrays(1, &VAO);
					glBindVertexArray(VAO);


					//Gen VAO AND BIND
					glGenBuffers(1, &VBO);
					glBindBuffer(GL_ARRAY_BUFFER, VBO);
					glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


					//GEN EBO AND BIND AND SEND DATA
					glGenBuffers(1, &EBO);
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

					//SET VERTEXATTRIBPOINTERS AND ENABLE (INPUT ASSEMBLY)
					//Position
					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
					glEnableVertexAttribArray(0);
					//Color
					glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
					glEnableVertexAttribArray(1);
					//Texcoord
					glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
					glEnableVertexAttribArray(2);

					//BIND VAO 0
					glBindVertexArray(0);

					break;

				default:

					cout << "You shouldn't be here";

					break;

				}
			}
		}
		
		oldState = state;

		//MOUSE END

        glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1);
		glMatrixMode(GL_MODELVIEW);  //resets matrix mdoe back to default
		glLoadIdentity();


		//UPDATE INPUT ---
		glfwPollEvents();


		//UPDATE ---
		updateInput(window);

		//CLEAR
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		//Use a program
		glUseProgram(core_program);

		//Bind vertex array object (VAO)
		glBindVertexArray(VAO);

		//Draw
		glDrawElements(GL_TRIANGLES, nrOfIndices, GL_UNSIGNED_INT, 0);


		//END DRAW
		glfwSwapBuffers(window);
		glFlush();
	}

	//END OF PROGRAM
	glfwDestroyWindow(window);
	glfwTerminate();


	//DELETE PROGRAM
	glDeleteProgram(core_program);
	return 0;

}

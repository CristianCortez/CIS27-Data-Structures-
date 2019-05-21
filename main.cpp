#include"Vertex.h"
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <iostream>
#include "movement.h"

using namespace std;

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	/*
	if (key == GLFW_KEY_R && action == GLFW_PRESS) {

		keyPressReset == GLFW_PRESS;

	}
	else if (key == GLFW_KEY_R && action == GLFW_RELEASE) {

		keyPressUndo == GLFW_RELEASE;

	}
	else if (key == GLFW_KEY_BACKSPACE && action == GLFW_PRESS) {

		keyPressUndo == GLFW_PRESS;

	}
	else if (key == GLFW_KEY_BACKSPACE && action == GLFW_RELEASE) {

		keyPressUndo == GLFW_RELEASE;

	}

	*/

}


int main() {

	Vertex vertices[52];
	initVertexAry(vertices);
	unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

	GLuint indices[78];
	initIndices(indices);
	unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

	//MOUSE START
	int stateMouse;
	int oldStateMouse = GLFW_RELEASE;
	int keyPressReset;
	int oldkeyPressReset = GLFW_RELEASE;
	int keyPressUndo;
	int oldkeyPressUndo = GLFW_RELEASE;
	int indexOfFirstPositionVecOfSelectedBlock;
	double xposStart;
	double yposStart;
	double xposEnd;
	double yposEnd;
	int direction;
	int winFlag;

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



		stateMouse = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

		if (stateMouse == GLFW_PRESS && oldStateMouse == GLFW_RELEASE) {

			glfwGetCursorPos(window, &xposStart, &yposStart);

			xposStart = ((2.0 / SCREEN_WIDTH) * xposStart) - 1.0;
			yposStart = (((2.0 / SCREEN_HEIGHT) * yposStart) - 1.0) * -1.0;

			indexOfFirstPositionVecOfSelectedBlock = selectBlock(xposStart, yposStart, vertices);

			cout << "  SELECTED BLOCK: " << indexOfFirstPositionVecOfSelectedBlock;

		}

		else if(stateMouse == GLFW_RELEASE && oldStateMouse == GLFW_PRESS) {
		
			glfwGetCursorPos(window, &xposEnd, &yposEnd);

			xposEnd = ((2.0 / SCREEN_WIDTH) * xposEnd) - 1.0;
			yposEnd = (((2.0 / SCREEN_HEIGHT) * yposEnd) - 1.0) * -1.0;

			direction = getDirection(xposEnd, yposEnd, indexOfFirstPositionVecOfSelectedBlock, vertices);

			if (isSpaceEmpty(direction, xposEnd, yposEnd, indexOfFirstPositionVecOfSelectedBlock, vertices)) {

				cout << "  SELECTED BLOCK: " << indexOfFirstPositionVecOfSelectedBlock;

				cout << "  Direction: " << direction;

				switch (direction) {

				case 1:

					moveLeft(indexOfFirstPositionVecOfSelectedBlock, vertices);

					//push(vertices[indexOfFirstPositionVecOfSelectedBlock], 
					//	vertices[indexOfFirstPositionVecOfSelectedBlock + 1], 
					//	vertices[indexOfFirstPositionVecOfSelectedBlock + 2], 
					//	vertices[indexOfFirstPositionVecOfSelectedBlock + 3])

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

					moveRight(indexOfFirstPositionVecOfSelectedBlock, vertices);

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

					cout << "   DID IT CHANGE :" << vertices[indexOfFirstPositionVecOfSelectedBlock].position[1];

					moveUp(indexOfFirstPositionVecOfSelectedBlock, vertices);

					cout << "   DID IT CHANGE :" << vertices[indexOfFirstPositionVecOfSelectedBlock].position[1];

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

					moveDown(indexOfFirstPositionVecOfSelectedBlock, vertices);

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

			indexOfFirstPositionVecOfSelectedBlock = -1;
			xposStart = -99.0;
			yposStart = -99.0;
			xposEnd = -99.0;
			yposEnd = -99.0;
			direction = -1;

		}
		
		oldStateMouse = stateMouse;

		//MOUSE END




		winFlag = winCondition(vertices); //DO SOMETHING WITH THIS

		glfwSetKeyCallback(window, key_callback);


		keyPressReset = glfwGetKey(window, GLFW_KEY_R);

		keyPressUndo = glfwGetKey(window, GLFW_KEY_BACKSPACE);











		if (keyPressReset == GLFW_PRESS && oldkeyPressReset == GLFW_RELEASE) {

			initVertexAry(vertices);
			cout << "RESET";

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


		}

		else if (keyPressUndo == GLFW_PRESS && oldkeyPressUndo == GLFW_RELEASE) {

			//UNDO

			cout << "BACKSPACE";

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


		}

		oldkeyPressReset = keyPressReset;

		oldkeyPressUndo = keyPressUndo;













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

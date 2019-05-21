#include"lib.h"
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <iostream>
#include "movement.h"

using namespace std;



void moveLeft(GLuint VAO, GLuint VBO, GLuint EBO, GLuint indices[], int index, int state, Vertex vertices[]) {

	vertices[index].position[0] -= 0.25;
	vertices[index + 1].position[0] -= 0.25;
	vertices[index + 2].position[0] -= 0.25;
	vertices[index + 3].position[0] -= 0.25;

	//REDRAW
	redraw(VAO, VBO, EBO, indices, vertices);

}

void moveRight(GLuint VAO, GLuint VBO, GLuint EBO, GLuint indices[], int index, int state, Vertex vertices[]) {

	vertices[index].position[0] += 0.25;
	vertices[index + 1].position[0] += 0.25;
	vertices[index + 2].position[0] += 0.25;
	vertices[index + 3].position[0] += 0.25;

	//REDRAW
	redraw(VAO, VBO, EBO, indices, vertices);

}

void moveUp(GLuint VAO, GLuint VBO, GLuint EBO, GLuint indices[], int index, int state, Vertex vertices[]) {

	vertices[index].position[1] += 0.32;
	vertices[index + 1].position[1] += 0.32;
	vertices[index + 2].position[1] += 0.32;
	vertices[index + 3].position[1] += 0.32;

	//REDRAW
	redraw(VAO, VBO, EBO, indices, vertices);

}

void moveDown(GLuint VAO, GLuint VBO, GLuint EBO, GLuint indices[], int index, int state, Vertex vertices[]) {

	vertices[index].position[1] -= 0.32;
	vertices[index + 1].position[1] -= 0.32;
	vertices[index + 2].position[1] -= 0.32;
	vertices[index + 3].position[1] -= 0.32;

	//REDRAW
	redraw(VAO, VBO, EBO, indices, vertices);

}

int selectBlock(double xpos, double ypos, Vertex vertices[]) {

	int index = -1;

	for (int i = 8; i <= 44; i += 4) {

		if (xpos > vertices[i].position[0] && xpos < vertices[i + 2].position[0] && ypos < vertices[i].position[1] && ypos > vertices[i + 2].position[1]) {

			index = i;

		}

	}

	return index;

}

bool isSpaceEmpty(int direction, double xpos, double ypos, int index, Vertex vertices[]) { //NEED TO REDO WITH DIRECTION AS AN ARG

	bool isEmpty = true;
	double distanceBetweenStartAndEndX;
	double distanceBetweenStartAndEndY;

	if (xpos > 0.5f || xpos < -0.5f || ypos > 0.8f || ypos < -0.8f) {

		isEmpty = false;

	}
	else {

		switch (direction) {

		case 1:

			//LEFT

			distanceBetweenStartAndEndX = xpos - vertices[index].position[0];

			if (distanceBetweenStartAndEndX < 0) {

				distanceBetweenStartAndEndX = -distanceBetweenStartAndEndX;

			}

			if (distanceBetweenStartAndEndX > 0.25) {

				isEmpty = false;

			}

			break;

		case 2:

			//RIGHT

			distanceBetweenStartAndEndX = xpos - vertices[index + 2].position[0];

			if (distanceBetweenStartAndEndX < 0) {

				distanceBetweenStartAndEndX = -distanceBetweenStartAndEndX;

			}

			if (distanceBetweenStartAndEndX > 0.25) {

				isEmpty = false;

			}

			break;

		case 3:

			//UP

			distanceBetweenStartAndEndY = ypos - vertices[index].position[1];

			//cout << "DISTANCE BETWEEN Y: " << distanceBetweenStartAndEndY << "           ";

			if (distanceBetweenStartAndEndY < 0) {

				distanceBetweenStartAndEndY = -distanceBetweenStartAndEndY;

			}

			if (distanceBetweenStartAndEndY > 0.32) {

				//cout << "HMMMMMMMMMMMMMM";

				isEmpty = false;

			}

			break;

		case 4:

			//DOWN

			distanceBetweenStartAndEndY = ypos - vertices[index + 2].position[1];

			if (distanceBetweenStartAndEndY < 0) {

				distanceBetweenStartAndEndY = -distanceBetweenStartAndEndY;

			}

			if (distanceBetweenStartAndEndY > 0.32) {

				isEmpty = false;

			}

			break;

		}

		for (int i = 8; i <= 44; i += 4) {

			if (xpos > vertices[i].position[0] && xpos < vertices[i + 2].position[0] && ypos < vertices[i].position[1] && ypos > vertices[i + 2].position[1]) {

				isEmpty = false;


			}
		}
	}

	return isEmpty;

}

void redraw(GLuint VAO, GLuint VBO, GLuint EBO, GLuint indices[], Vertex vertices[]) {

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

int getDirection(double xposEnd, double yposEnd, int index, Vertex vertices[]) {

	int direction = 0;

	if (yposEnd < vertices[index].position[1] && yposEnd > vertices[index + 2].position[1] && xposEnd < vertices[index].position[0]) {

		//LEFT

		direction = 1;

	}
	else if (yposEnd < vertices[index].position[1] && yposEnd > vertices[index + 2].position[1] && xposEnd > vertices[index + 2].position[0]) {

		//RIGHT

		direction = 2;

	}
	else if (xposEnd > vertices[index].position[0] && xposEnd < vertices[index + 2].position[0] && yposEnd > vertices[index].position[1]) {

		//UP

		direction = 3;

	}

	else if (xposEnd > vertices[index].position[0] && xposEnd < vertices[index + 2].position[0] && yposEnd < vertices[index + 2].position[1]) {

		//DOWN

		direction = 4;

	}

	return direction;

}

void resetGame(Vertex vertices[]) {



}


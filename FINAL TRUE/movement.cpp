/*
Salvador
*/

#include"Vertex.h"
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <iostream>
#include "movement.h"

using namespace std;



void moveLeft(int index, Vertex vertices[]) {

	vertices[index].position[0] -= 0.25;
	vertices[index + 1].position[0] -= 0.25;
	vertices[index + 2].position[0] -= 0.25;
	vertices[index + 3].position[0] -= 0.25;

}

void moveRight(int index, Vertex vertices[]) {

	vertices[index].position[0] += 0.25;
	vertices[index + 1].position[0] += 0.25;
	vertices[index + 2].position[0] += 0.25;
	vertices[index + 3].position[0] += 0.25;

}

void moveUp(int index, Vertex vertices[]) {

	vertices[index].position[1] += 0.32;
	vertices[index + 1].position[1] += 0.32;
	vertices[index + 2].position[1] += 0.32;
	vertices[index + 3].position[1] += 0.32;

}

void moveDown(int index, Vertex vertices[]) {

	vertices[index].position[1] -= 0.32;
	vertices[index + 1].position[1] -= 0.32;
	vertices[index + 2].position[1] -= 0.32;
	vertices[index + 3].position[1] -= 0.32;

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

bool isSpaceEmpty(int direction, double xpos, double ypos, int index, Vertex vertices[]) { //NEED TO CHECK CASES WITH BIGGER BLOCKS

	bool isEmpty = true;
	double distanceBetweenStartAndEndX;
	double distanceBetweenStartAndEndY;
	double possibleXpos;
	double possibleYpos;
	int isThereABlock;
	int isThereABlock2;

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

			switch (direction) {

			case 1:

				isThereABlock = selectBlock(vertices[index + 1].position[0] - 0.05, vertices[index + 1].position[1] + 0.05, vertices);
				isThereABlock2 = selectBlock(vertices[index].position[0] - 0.05, vertices[index].position[1] - 0.05, vertices);

				if (isThereABlock != -1) {

					isEmpty = false;

				}



				else if (isThereABlock2 != -1) {

					isEmpty = false;

				}


				/*
				//LEFT

				if (vertices[index].position[0] == vertices[i + 3].position[0] && vertices[index + 1].position[0] == vertices[i + 2].position[0] &&                ((vertices[index].position[1] > vertices[i + 3].position[1] && vertices[index + 1].position[1] < vertices[i + 3].position[1] && vertices[index + 1].position[1] >= vertices[i + 2].position[1]) || (vertices[index].position[1] > vertices[i + 2].position[1] && vertices[index + 1].position[1] < vertices[i + 2].position[1] && vertices[index].position[1] <= vertices[i + 3].position[1]))) {

					isEmpty = false;

					cout << "              YOU CANT MOVE BIG INTO SMALL            " << vertices[i + 3].position[1] << "      " << vertices[i + 2].position[1];

				}

				break;

				*/

				break;

			case 2:

				isThereABlock = selectBlock(vertices[index + 2].position[0] + 0.05, vertices[index + 2].position[1] + 0.05, vertices);

				isThereABlock2 = selectBlock(vertices[index + 3].position[0] + 0.05, vertices[index + 3].position[1] - 0.05, vertices);

				if (isThereABlock != -1) {

					isEmpty = false;

				}

				else if (isThereABlock2 != -1) {

					isEmpty = false;

				}



				/*
				//RIGHT

				if ((vertices[index + 3].position[1] > vertices[i].position[1] && vertices[index + 2].position[1] < vertices[i].position[1] && vertices[index + 2].position[1] >= vertices[i + 1].position[1])) {


					cout << "ITS THIS ONE             ";


				}

				if (vertices[index + 3].position[0] == vertices[i].position[0] && vertices[index + 2].position[0] == vertices[i + 1].position[0] &&                ((vertices[index + 3].position[1] > vertices[i].position[1] && vertices[index + 2].position[1] < vertices[i].position[1] && vertices[index + 2].position[1] >= vertices[i + 1].position[1]) || (vertices[index + 3].position[1] > vertices[i + 1].position[1] && vertices[index + 2].position[1] < vertices[i + 1].position[1] && vertices[index + 3].position[1] <= vertices[i].position[1]))) {

					isEmpty = false;

					cout << "              YOU CANT MOVE BIG INTO SMALL            " << vertices[i].position[1] << "      " << vertices[i + 1].position[1];

				}

				break;

				*/

				break;

			case 3:

				isThereABlock = selectBlock(vertices[index].position[0] + 0.05, vertices[index].position[1] + 0.05, vertices);
				isThereABlock2 = selectBlock(vertices[index + 3].position[0] - 0.05, vertices[index + 3].position[1] + 0.05, vertices);

				if (isThereABlock != -1) {

					isEmpty = false;

					cout << " BLOCK IN THE WAY AT INDEX : " << isThereABlock;

				}

				else if (isThereABlock2 != -1) {

					isEmpty = false;

					cout << " BLOCK IN THE WAY AT INDEX : " << isThereABlock2;

				}


				/*

				//UP

				if ((((vertices[index].position[0] < vertices[i + 1].position[0] && vertices[index + 3].position[0] > vertices[i + 1].position[0]) && vertices[index + 3].position[0] <= vertices[i + 2].position[0]) || ((vertices[index].position[0] < vertices[i + 2].position[0] && vertices[index + 3].position[0] > vertices[i + 2].position[0]) && vertices[index].position[0] >= vertices[i + 1].position[0])) && vertices[index].position[1] == vertices[i + 1].position[1] && vertices[index + 3].position[1] == vertices[i + 2].position[1]) {

					isEmpty = false;

				}

				*/


				break;

			case 4:

				isThereABlock = selectBlock(vertices[index + 1].position[0] + 0.05, vertices[index + 1].position[1] - 0.05, vertices);
				isThereABlock2 = selectBlock(vertices[index + 2].position[0] - 0.05, vertices[index + 2].position[1] - 0.05, vertices);


				if (isThereABlock != -1) {

					isEmpty = false;

					cout << " BLOCK IN THE WAY AT INDEX : " << isThereABlock;

				}

				else if (isThereABlock2 != -1) {

					isEmpty = false;

					cout << " BLOCK IN THE WAY AT INDEX : " << isThereABlock2;

				}




				/*

				//DOWN

				if ((((vertices[index + 1].position[0] < vertices[i].position[0] && vertices[index + 2].position[0] > vertices[i].position[0]) && vertices[index + 2].position[0] <= vertices[i + 3].position[0]) || ((vertices[index + 1].position[0] < vertices[i + 3].position[0] && vertices[index + 2].position[0] > vertices[i + 3].position[0]) && vertices[index + 1].position[0] >= vertices[i].position[0])) && vertices[index + 1].position[1] == vertices[i].position[1] && vertices[index + 2].position[1] == vertices[i + 3].position[1]) {

					isEmpty = false;

				}

				*/

				break;

			}

			if (xpos > vertices[i].position[0] && xpos < vertices[i + 2].position[0] && ypos < vertices[i].position[1] && ypos > vertices[i + 2].position[1]) {

				isEmpty = false; //HANDELS CASE FOR 1x1 BLOCKS

				//cout << "              YOU CANT MOVE SMALL INTO BIG            ";

			}

		}
	}

	return isEmpty;

}

void redraw(GLFWwindow* window, GLuint VAO, GLuint VBO, GLuint EBO, GLuint indices[], Vertex vertices[]) {

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


	//updateInput(window);

	//CLEAR
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//Bind vertex array object (VAO)
	glBindVertexArray(VAO);

	//Draw
	//glDrawElements(GL_TRIANGLES, nrOfIndices, GL_UNSIGNED_INT, 0);


	//END DRAW
	glfwSwapBuffers(window);
	glFlush();

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

	Vertex resetVertices[] = {
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

	vertices = resetVertices; //MAY NEED TO INTERATE THROUGH AND CHANGE VALUES
	//HAVE TO REDRAW AFTER

}

int winCondition(Vertex vertices[]) {

	int didYouWin = 0;

	if (vertices[13].position[0] == vertices[48].position[0] && vertices[13].position[1] == vertices[48].position[1] && vertices[14].position[0] == vertices[51].position[0] && vertices[14].position[1] == vertices[51].position[1]) {


		cout << "YOU WIN CONGRATS";

		didYouWin = 1;

		//DO SOMETHING WITH THIS

	}

	return didYouWin;

}

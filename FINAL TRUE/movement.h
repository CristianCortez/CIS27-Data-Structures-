#ifndef MOVEMENT_H
#define MOVEMENT_H
#include "Vertex.h"

void moveLeft(int index, Vertex vertices[]);

void moveRight(int index, Vertex vertices[]);

void moveUp(int index, Vertex vertices[]);

void moveDown(int index, Vertex vertices[]);

int selectBlock(double xpos, double ypos, Vertex vertices[]);

bool isSpaceEmpty(int direction, double xpos, double ypos, int indexOfFirstPositionVecOfSelectedBlock, Vertex vertices[]);

void redraw(GLFWwindow* window, GLuint VAO, GLuint VBO, GLuint EBO, GLuint indices[], Vertex vertices[]);

int getDirection(double xposEnd, double yposEnd, int index, Vertex vertices[]);

void resetGame(Vertex vertices[]);

int winCondition(Vertex vertices[]);
#endif // !MOVEMENT_H
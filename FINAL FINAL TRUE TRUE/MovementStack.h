/*
Cristian Cortez
*/

#ifndef MOVEMENTSTACK_H
#define MOVEMENTSTACK_H
#pragma once
#include "Vertex.h"
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

struct StackNode {
	glm::vec3 ltop;
	glm::vec3 lbottom;
	glm::vec3 rbottom;;
	glm::vec3 rtop;
};

typedef struct StackNode TSStackNode;

struct Stack {
	int index;
	TSStackNode block;
	struct Stack* next;
};

typedef struct Stack TStack;
typedef struct Stack* TStackPtr;
typedef struct Stack* TStackAddr;

TStackPtr createPosStack(int index, glm::vec3 postionTL, glm::vec3 positionBL,
	glm::vec3 positonBR, glm::vec3 positonTR);

void push(TStackAddr*, TStackPtr);

TStackPtr pop(TStackAddr*);

void destroyStackNode(TStackAddr*);

void destroyStack(TStackAddr*);

#endif // !MOVEMENTSTACK_H

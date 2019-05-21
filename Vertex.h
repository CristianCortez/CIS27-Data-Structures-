#ifndef VERTEX_H
#define VERTEX_H
#pragma once
#include<iostream>
#include <fstream>
#include <string>
#include <sstream>

#include<gl/glew.h>
#include<GLFW/glfw3.h>

#include<glm/glm.hpp>
#include<glm/vec2.hpp>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
#include<glm/mat4x4.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include<SOIL2/SOIL2.h>

using namespace std;

struct Vertex {
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texcoord;
};


void initVertexAry(Vertex VertexAry[]);
void initIndices(GLuint indices[]);



#endif
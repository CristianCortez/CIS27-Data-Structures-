/*
Cristian C
*/

#include "Vertex.h"

using namespace std;

void initVertexAry(Vertex VertexAry[]) {
	// :: WHITE BASE ::
	VertexAry[0] =
	{
		glm::vec3(-0.5f, 0.8f, 0.8f), glm::vec3(1.f, 1.f, 1.f), glm::vec2(0.f, 1.f), //Top left
	};
	VertexAry[1] = {
		glm::vec3(-0.5f, -0.8f, 0.8f), glm::vec3(1.f, 1.f, 1.f), glm::vec2(0.f, 0.f),     //Bottom left
	};
	VertexAry[2] = {
		glm::vec3(0.5f, -0.8f, 0.8f), glm::vec3(1.f, 1.f, 1.f), glm::vec2(1.f, 0.f),     //Bottom right
	};
	VertexAry[3] = {
		glm::vec3(0.5f, 0.8f, 0.8f),  glm::vec3(1.f, 1.f, 1.f), glm::vec2(0.f, 0.f),     //Top right
	};

	// :: GREEN BASE ::
	VertexAry[4] = {
		glm::vec3(-0.6f, 0.9f, 0.8f), glm::vec3(0.5f, 1.f, 0.5f), glm::vec2(0.f, 1.f),     //Top left
	};
	VertexAry[5] = {
		glm::vec3(-0.6f, -0.9f, 0.8f), glm::vec3(0.5f, 1.f, 0.5f), glm::vec2(0.f, 0.f),     //Bottom left
	};
	VertexAry[6] = {
		glm::vec3(0.6f, -0.9f, 0.8f), glm::vec3(0.5f, 1.f, 0.5f), glm::vec2(1.f, 0.f),     //Bottom right
	};
	VertexAry[7] = {
		glm::vec3(0.6f, 0.9f, 0.8f), glm::vec3(0.5f, 1.f, 0.5f), glm::vec2(0.f, 0.f),     //Top right
	};

	// :: BLOCK 1 ::
	VertexAry[8] = {
	glm::vec3(-0.5f, 0.8f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(1.f, 1.f),     //Top left
	};
	VertexAry[9] = {
		glm::vec3(-0.5f, 0.16f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(0.f, 0.f),     //Bottom left
	};
	VertexAry[10] = {
		glm::vec3(-0.25f, 0.16f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec2(1.f, 0.f),     //Bottom right
	};
	VertexAry[11] = {
		glm::vec3(-0.25f, 0.8f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(0.f, 0.f),     //Top right
	};

	// :: BLOCK 2::
	VertexAry[12] = {
	glm::vec3(-0.25f, 0.8f, 0.f), glm::vec3(1.f, 0.f, 0.f), glm::vec2(0.f, 1.f),     //Top left
	};
	VertexAry[13] = {
		glm::vec3(-0.25f, 0.16f, 0.f), glm::vec3(1.f, 0.f, 0.f), glm::vec2(0.f, 0.f),     //Bottom left
	};
	VertexAry[14] = {
		glm::vec3(0.25f, 0.16f, 0.f), glm::vec3(1.f, 0.f, 0.f), glm::vec2(1.f, 0.f),     //Bottom right}
	};
	VertexAry[15] = {
		glm::vec3(0.25f, 0.8f, 0.f), glm::vec3(1.f, 0.f, 0.f), glm::vec2(0.f, 0.f),     //Top right
	};

	// :: BLOCK 3 ::
	VertexAry[16] = {
	glm::vec3(0.25f, 0.8f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(0.f, 1.f),     //Top left
	};
	VertexAry[17] = {
		glm::vec3(0.25f, 0.16f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(0.f, 0.f),     //Bottom left
	};
	VertexAry[18] = {
		glm::vec3(0.5f, 0.16f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec2(1.f, 0.f),     //Bottom right
	};
	VertexAry[19] = {
		glm::vec3(0.5f, 0.8f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(0.f, 0.f),     //Top right
	};

	// :: BLOCK 4 ::
	VertexAry[20] = {
	glm::vec3(-0.5f, 0.16f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(0.f, 1.f),     //Top left
	};
	VertexAry[21] = {
		glm::vec3(-0.5f, -0.48f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(0.f, 0.f),     //Bottom left
	};
	VertexAry[22] = {
		glm::vec3(-0.25f, -0.48f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec2(1.f, 0.f),     //Bottom right
	};
	VertexAry[23] = {
		glm::vec3(-0.25f, 0.16f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(0.f, 0.f),     //Top right
	};

	// :: BLOCK 5 ::
	VertexAry[24] = {
	glm::vec3(-0.25f, 0.16f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(0.f, 1.f),     //Top left
	};
	VertexAry[25] = {
		glm::vec3(-0.25f, -0.16f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(0.f, 0.f),     //Bottom left
	};
	VertexAry[26] = {
		glm::vec3(0.25f, -0.16f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec2(1.f, 0.f),     //Bottom right
	};
	VertexAry[27] = {
		glm::vec3(0.25f, 0.16f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(0.f, 0.f),     //Top right
	};

	// :: BLOCK 6 ::
	VertexAry[28] = {
	glm::vec3(-0.25f, -0.16f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(0.f, 1.f),     //Top left
	};
	VertexAry[29] = {
		glm::vec3(-0.25f, -0.48f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(0.f, 0.f),     //Bottom left
	};
	VertexAry[30] = {
		glm::vec3(0.0f, -0.48f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec2(1.f, 0.f),     //Bottom right
	};
	VertexAry[31] = {
		glm::vec3(0.0f, -0.16f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(0.f, 0.f),     //Top right
	};

	// :: BLOCK 7 ::
	VertexAry[32] = {
	glm::vec3(0.0f, -0.16f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(0.f, 1.f),     //Top left
	};
	VertexAry[33] = {
		glm::vec3(0.0f, -0.48f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(0.f, 0.f),     //Bottom left
	};
	VertexAry[34] = {
		glm::vec3(0.25f, -0.48f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec2(1.f, 0.f),     //Bottom right
	};
	VertexAry[35] = {
		glm::vec3(0.25f, -0.16f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(0.f, 0.f),     //Top right
	};

	// :: BLOCK 8 ::
	VertexAry[36] = {
	glm::vec3(0.25f, 0.16f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(0.f, 1.f),     //Top left
	};
	VertexAry[37] = {
		glm::vec3(0.25f, -0.48f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(0.f, 0.f),     //Bottom left
	};
	VertexAry[38] = {
		glm::vec3(0.5f, -0.48f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec2(1.f, 0.f),     //Bottom right
	};
	VertexAry[39] = {
		glm::vec3(0.5f, 0.16f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(0.f, 0.f),     //Top right
	};

	// :: BLOCK 9 ::
	VertexAry[40] = {
	glm::vec3(-0.5f, -0.48f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(0.f, 1.f),     //Top left
	};
	VertexAry[41] = {
		glm::vec3(-0.5f, -0.8f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(0.f, 0.f),     //Bottom left
	};
	VertexAry[42] = {
		glm::vec3(-0.25f, -0.8f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec2(1.f, 0.f),     //Bottom right
	};
	VertexAry[43] = {
		glm::vec3(-0.25f, -0.48f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(0.f, 0.f),     //Top right
	};

	// :: BLOCK 10 ::
	VertexAry[44] = {
	glm::vec3(0.25f, -0.48f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(0.f, 1.f),     //Top left
	};
	VertexAry[45] = {
		glm::vec3(0.25f, -0.8f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(0.f, 0.f),     //Bottom left
	};
	VertexAry[46] = {
		glm::vec3(0.5f, -0.8f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec2(1.f, 0.f),     //Bottom right
	};
	VertexAry[47] = {
		glm::vec3(0.5f, -0.48f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(0.f, 0.f),      //Top right
	};

	// :: BLOCK EXIT ::
	VertexAry[48] = {
	glm::vec3(-0.25f, -0.8f, 0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(0.f, 0.f),    //Top left
	};
	VertexAry[49] = {
		glm::vec3(-0.25f, -0.9f, 0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(1.f, 0.f),     //Bottom left
	};
	VertexAry[50] = {
		glm::vec3(0.25f, -0.9f, 0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(1.f, 0.f),     //Bottom right
	};
	VertexAry[51] = {
		glm::vec3(0.25f, -0.8f, 0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(0.f, 0.f)    //Top right
	};
}

void initIndices(GLuint indices[]) {
	for (int i = 0; i < 13; i++)
		for (int j = 0; j < 3; j++) {
			indices[i * 6 + j] = i * 4 + j;
			if (j % 3 == 0) {
				//indices[i * 6 + j] = i * 4 + j;
				indices[i * 6 + j + 3] = indices[i * 6 + j];
			}
			else {
				//indices[i * 6 + j] = i * 4 + j + 1;
				//indices[i * 6 + j] = indices[i * 6 - j + 1] + 1;
				indices[i * 6 + j + 3] = indices[i * 6 + j] + 1;
			}

		}
};

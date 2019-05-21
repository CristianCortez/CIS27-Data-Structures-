


void moveLeft(GLuint VAO, GLuint VBO, GLuint EBO, GLuint indices[], int index, int state, Vertex vertices[]);

void moveRight(GLuint VAO, GLuint VBO, GLuint EBO, GLuint indices[], int index, int state, Vertex vertices[]);

void moveUp(GLuint VAO, GLuint VBO, GLuint EBO, GLuint indices[], int index, int state, Vertex vertices[]);

void moveDown(GLuint VAO, GLuint VBO, GLuint EBO, GLuint indices[], int index, int state, Vertex vertices[]);

int selectBlock(double xpos, double ypos, Vertex vertices[]);

bool isSpaceEmpty(int direction, double xpos, double ypos, int indexOfFirstPositionVecOfSelectedBlock, Vertex vertices[]);

void redraw(GLuint VAO, GLuint VBO, GLuint EBO, GLuint indices[], Vertex vertices[]);

int getDirection(double xposEnd, double yposEnd, int index, Vertex vertices[]);

void resetGame(Vertex vertices[]);
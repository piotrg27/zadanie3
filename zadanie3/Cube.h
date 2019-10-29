#ifndef _CUBE_H_
#define _CUBE_H_

#include "Includes.h"

#include "Shader.h"
#include "Texture.h"

class Cube
{
private:
	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> indices;
	GLuint vbo;
	GLuint vao;
	GLuint ibo;

	ShaderProgram shaderProgram;
public:
	Cube();
	void setup(glm::vec2 size, ShaderProgram shader);
	void draw();
	~Cube();
};
#endif
#include "Cube.h"



Cube::Cube()
{
}

void Cube::setup(glm::vec2 size, ShaderProgram shader)
{
	shaderProgram = shader;

	vertices.push_back(glm::vec3(0, 0, 1));
	vertices.push_back(glm::vec3(1, 0, 1));
	vertices.push_back(glm::vec3(1, 1, 1));
	vertices.push_back(glm::vec3(0, 1, 1));

	vertices.push_back(glm::vec3(0, 0, 0));
	vertices.push_back(glm::vec3(1, 0, 0));
	vertices.push_back(glm::vec3(1, 1, 0));
	vertices.push_back(glm::vec3(0, 1, 0));

	indices.push_back(0); indices.push_back(1); indices.push_back(2);
	indices.push_back(2); indices.push_back(3); indices.push_back(0);

	indices.push_back(1); indices.push_back(5); indices.push_back(6);
	indices.push_back(6); indices.push_back(2); indices.push_back(1);

	indices.push_back(7); indices.push_back(6); indices.push_back(5);
	indices.push_back(5); indices.push_back(4); indices.push_back(7);

	indices.push_back(4); indices.push_back(0); indices.push_back(3);
	indices.push_back(3); indices.push_back(7); indices.push_back(4);

	indices.push_back(4); indices.push_back(5); indices.push_back(1);
	indices.push_back(1); indices.push_back(0); indices.push_back(4);

	indices.push_back(3); indices.push_back(2); indices.push_back(6);
	indices.push_back(6); indices.push_back(7); indices.push_back(3);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*vertices.size(), vertices.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Cube::draw()
{
	glUseProgram(shaderProgram.getID());
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, (void*)0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
}

Cube::~Cube()
{
}

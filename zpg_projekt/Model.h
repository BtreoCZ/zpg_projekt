#pragma once
//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>

//Include GLM
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate,glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

//Include the standard C++ headers
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "tree.h"
#include "sphere.h"
class Model
{
	public:
	Model();
	~Model();
	void createFromFloats(const float* values, GLsizeiptr count);
	void createFromFloatsWithNormals(const float* values, GLsizei count);
	void bind();
	void draw();
	GLuint VBO;
	GLuint VAO;
private:
	GLsizeiptr count;
	
};


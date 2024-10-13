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
#include "Shader.h"


using namespace std;
struct Vertex {
	float position[4];
	float color[4];
};
const Vertex b[] = {
{ { -1.f, -0.f, .5f, 1 }, { 1, 1, 0, 1 } },
{ { -1.f, 1.f, .5f, 1 }, { 1, 0, 0, 1 } },
{ { 0.f, 1.f, .5f, 1 }, { 0, 0, 0, 1 } },
{ { 0.f, 0.f, .5f, 1 }, { 0, 1, 0, 1 } },
};
const Vertex a[] = {
 -.5f, -.5f, .5f,  0, 0, 1,
 -.5f, .5f, .5f,  0, 0, 1,
   .5f, .5f, .5f,  0, 0, 1,
   .5f, -.5f, .5f,  0, 0, 1 };



class Application
{
	public:
		vector<Model> models;
		vector<Shader> shaders;
		void run();
		void init();
		void createShaders();
		void createModels();
		GLFWwindow* window;
		int width, height;
		float ratio;
	private:
		

};


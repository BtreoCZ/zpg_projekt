#include "Model.h"
using namespace std;
Model::Model()
{
    this->count = 0;
    this->VAO = 0;
    this->VBO = 0;
}

Model::~Model()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Model::createFromFloats(const float* values, GLsizeiptr count)
{

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    this->count = count;

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(values), values, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(0);

}

void Model::createFromFloatsWithNormals(const float* values, GLsizei count)
{
    this->count = count;

    glGenBuffers(1, &this->VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(values), values, GL_STATIC_DRAW);

    glGenVertexArrays(1, &this->VAO); //generate the VAO
    glBindVertexArray(this->VAO); //bind the VAO
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),(GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),(GLvoid*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}
void Model::bind()
{
	glBindVertexArray(this->VAO);
}

void Model::draw()
{
	glDrawArrays(GL_TRIANGLES, 0, 2880);
}

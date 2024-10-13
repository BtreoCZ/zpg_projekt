#include "Shader.h"
#include <iostream>


Shader::Shader()
{
    shaderProgram = 0;
}

void Shader::createShaderProgram(const char* vertexSource, const char* fragmentSource) {

    
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    checkCompileErrors(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    checkCompileErrors(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    checkCompileErrors(shaderProgram);
}

void Shader::use() {
    glUseProgram(shaderProgram);
}

void Shader::checkCompileErrors(GLuint shader) {
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar* strInfoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);
        fprintf(stderr, "Shader compilation failure: %s\n", strInfoLog);
        delete[] strInfoLog;
    }
    else {
        glGetProgramiv(shader, GL_LINK_STATUS, &status);
        if (status == GL_FALSE) {
            GLint infoLogLength;
            glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
            GLchar* strInfoLog = new GLchar[infoLogLength + 1];
            glGetProgramInfoLog(shader, infoLogLength, NULL, strInfoLog);
            fprintf(stderr, "Program linking failure: %s\n", strInfoLog);
            delete[] strInfoLog;
        }
    }
}
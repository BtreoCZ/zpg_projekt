#pragma once
#include <vector>
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Camera.h"

class Scene {
private:
    std::vector<Mesh*> objects;
    Camera* camera;
    ShaderProgram* shader;  

public:
    Scene() : camera(nullptr), shader(nullptr) {}

    void setCamera(Camera* cam) {
        camera = cam;
    }

    void setShader(ShaderProgram* shaderProgram) {
        shader = shaderProgram;
    }

    void addObject(Mesh* object) {
        objects.push_back(object);
    }

    void render() {
        if (shader && camera) {
            for (auto& object : objects) {
                shader->use();
                glm::mat4 mvp = camera->getMVP(object->getModelMatrix());
                GLuint mvpLocation = glGetUniformLocation(shader->getProgramID(), "MVP");

                if (mvpLocation == -1) {
                    fprintf(stderr, "ERROR: Could not find uniform MVP in shader program\n");
                }
                else {
                    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &mvp[0][0]);
                }

                object->render();
            }
        }
    }
};

#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
private:
    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;

public:
    void setPerspective(float fov, float aspectRatio, float nearPlane, float farPlane) {
        projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
    }

    void setLookAt(glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp) {
        position = cameraPosition;
        target = cameraTarget;
        up = cameraUp;
        viewMatrix = glm::lookAt(position, target, up);
    }

    
    glm::mat4 getViewMatrix() const {
        return viewMatrix;
    }

    
    glm::mat4 getProjectionMatrix() const {
        return projectionMatrix;
    }

    
    glm::mat4 getMVP(const glm::mat4& modelMatrix) const {
        return projectionMatrix * viewMatrix * modelMatrix;
    }
};

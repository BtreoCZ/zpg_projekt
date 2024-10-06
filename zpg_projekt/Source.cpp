#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Window.h"  // Pokud máš vlastní třídu Window, jinak nahradíme glfw přímo
#include "InputHandler.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Camera.h"
#include "Scene.h"

// Inicializace okna (lze také použít Window třídu)
Window window;
InputHandler inputHandler;
ShaderProgram shaderProgram;
Scene scene;
Camera camera;

void setupScene() {
    // Vytvoření shaderového programu
    const char* vertexShaderSrc = R"(
        #version 330
        layout(location = 0) in vec3 vp;
        uniform mat4 MVP;
        void main() {
            gl_Position = MVP * vec4(vp, 1.0);
        }
    )";

    const char* fragmentShaderSrc = R"(
        #version 330
        out vec4 frag_colour;
        void main() {
            frag_colour = vec4(0.5, 0.0, 0.5, 1.0);
        }
    )";

    if (!shaderProgram.loadShaders(vertexShaderSrc, fragmentShaderSrc)) {
        fprintf(stderr, "ERROR: could not compile shaders\n");
        exit(-1);
    }

    camera.setPerspective(45.0f, 4.0f / 3.0f, 0.01f, 100.0f);
    camera.setLookAt(glm::vec3(10, 10, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

    Mesh triangle;
    float triangleVertices[] = {
        0.0f,  0.0f, 0.0f,
        1.0f,  0.0f, 0.0f,
        0.0f, -1.0f, 0.0f
    };
    triangle.initialize(triangleVertices, sizeof(triangleVertices));

    const Vertex b[] = {
    { { -1.f, -0.f, .5f, 1 }, { 1, 1, 0, 1 } },
    { { -1.f, 1.f, .5f, 1 }, { 1, 0, 0, 1 } },
    { { 0.f, 1.f, .5f, 1 }, { 0, 0, 0, 1 } },
    { { 0.f, 0.f, .5f, 1 }, { 0, 1, 0, 1 } },
    };


    scene.setCamera(&camera);
    scene.setShader(&shaderProgram);
    scene.addObject(&triangle);
}

int main(void) {
    // Inicializace okna
    if (!window.initialize(800, 600, "OpenGL Scene")) {
        fprintf(stderr, "ERROR: could not initialize GLFW or create window\n");
        return -1;
    }

    inputHandler.initializeCallbacks(window.getWindow());


    setupScene();


    while (window.isWindowOpen()) {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        scene.render();


        window.pollEvents();
        window.swapBuffers();
    }

    //scene.destroy();   // Mělo by obsahovat destrukci všech objektů
    shaderProgram.destroy();
    window.terminate();

    return 0;
}

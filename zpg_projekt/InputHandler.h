#pragma once
#include <GLFW/glfw3.h>
#include <stdio.h>

class InputHandler {
public:
    void initializeCallbacks(GLFWwindow* window) {
        glfwSetKeyCallback(window, keyCallback);
        glfwSetCursorPosCallback(window, cursorCallback);
        glfwSetMouseButtonCallback(window, mouseButtonCallback);
        glfwSetWindowSizeCallback(window, windowSizeCallback);
    }

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
        printf("Key Callback: key=%d, scancode=%d, action=%d, mods=%d\n", key, scancode, action, mods);
    }

    static void cursorCallback(GLFWwindow* window, double xpos, double ypos) {
        printf("Cursor Callback: x=%.2f, y=%.2f\n", xpos, ypos);
    }

    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
        if (action == GLFW_PRESS) {
            printf("Mouse Button Pressed: button=%d, action=%d, mods=%d\n", button, action, mods);
        }
    }

    static void windowSizeCallback(GLFWwindow* window, int width, int height) {
        printf("Window Size Callback: width=%d, height=%d\n", width, height);
        glViewport(0, 0, width, height);
    }
};


#include "Application.h"

static void error_callback(int error, const char* description) {
    fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int
    action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);


}

static void window_focus_callback(GLFWwindow* window, int focused) {
    printf("window_focus_callback \n");
}

static void window_iconify_callback(GLFWwindow* window, int iconified) {
    printf("window_iconify_callback \n");
}

static void window_size_callback(GLFWwindow* window, int width, int
    height) {
    printf("resize %d, %d \n", width, height);
    glViewport(0, 0, width, height);
}

static void cursor_callback(GLFWwindow* window, double x, double y) {
    printf("cursor_callback \n");
}

static void button_callback(GLFWwindow* window, int button, int action,
    int mode) {
    if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n",
        button, action, mode);
}

void Application::run()
{

    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(this->window)) {
        // clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glUseProgram(shaderProgram);
        //glBindVertexArray(VAO);
        //// draw triangles
        //glDrawArrays(GL_TRIANGLE_FAN, 0, 4); //mode,first,count

        //glUseProgram(shaderProgram2);
        //glBindVertexArray(VAO2);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
               /* GLint idModelTransform = glGetUniformLocation(shaders[0],
            "modelMatrix");
        glm::mat4 M = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f,
            0.1f));
        glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &M[0][0]);*/
        
        this->shaders[0].use();   
        this->models[0].bind();
        //glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 92814);
        glBindVertexArray(0);

        //glBindVertexArray(VAO_strom);
        //glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(tree));
        // update other events like input handling
        glfwPollEvents();
        // put the stuff we’ve been drawing onto the display
        glfwSwapBuffers(this->window);
    }

    glfwDestroyWindow(this->window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void Application::init()
{
    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit < -> 100 units
    glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.01f,
        100.0f);

    // Camera matrix
    glm::mat4 View = glm::lookAt(
        glm::vec3(10, 10, 10), // Camera is at (4,3,-3), in World Space
        glm::vec3(0, 0, 0), // and looks at the origin
        glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model = glm::mat4(1.0f);


    //glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
    
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        exit(EXIT_FAILURE);
    }
    //inicializace konkretni verze
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE,
        GLFW_OPENGL_CORE_PROFILE);

    this->window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
    if (!this->window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(this->window);
    glfwSwapInterval(1);

    // start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit();

    // get version info
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("Vendor %s\n", glGetString(GL_VENDOR));
    printf("Renderer %s\n", glGetString(GL_RENDERER));
    printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    printf("Using GLFW %i.%i.%i\n", major, minor, revision);

    // Sets the key callback
    glfwSetKeyCallback(this->window, key_callback);

    glfwSetCursorPosCallback(this->window, cursor_callback);

    glfwSetMouseButtonCallback(this->window, button_callback);

    glfwSetWindowFocusCallback(this->window, window_focus_callback);

    glfwSetWindowIconifyCallback(this->window, window_iconify_callback);

    glfwSetWindowSizeCallback(this->window, window_size_callback);

    
    glfwGetFramebufferSize(this->window, &this->width, &this->height);
    this->ratio = this->width / (float)this->height;
    glViewport(0, 0, this->width, this->height);

}

void Application::createShaders()
{
    const char* vertex_shader =
        "#version 330\n"
        "layout(location=0) in vec3 vp;"
        "void main () {"
        "     gl_Position = vec4 (vp, 1.0);"
        "}";

    const char* vertex_shader2 =
        "#version 330\n"
        "layout(location=0) in vec3 vp;"
        "layout(location=1) in vec3 vn;"
        "uniform mat4 modelMatrix;"
        "out vec3 color;"
        "void main () {"
        "     gl_Position = vec4 (vp, 1.0);"
        "     color = vn;"
        "}";





    const char* fragment_shader =
        "#version 330\n"
        "out vec4 frag_colour;"
        "in vec3 color;"
        "void main () {"
        "     frag_colour = vec4 (color, 1.0);"
        "}";

    const char* fragment_shader2 =
        "#version 330\n"
        "out vec4 frag_colour;"
        "void main () {"
        "     frag_colour = vec4 (1.0, 1.0, 0.0, 1.0);"
        "}";

    Shader shader;
    shader.createShaderProgram(vertex_shader2,fragment_shader);
    this->shaders.push_back(shader);


}

void Application::createModels()
{
    Model model;
    model.createFromFloatsWithNormals(sphere, sizeof(sphere));
    this->models.push_back(model);
}

#include "Application.h"


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
"     gl_Position = modelMatrix * vec4 (vp, 1.0);"
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


int main(void)
{
    Application *app = new Application;

    app->init();

    app->createShaders();

    app->createModels();

	app->run();
	return 0;
}

#include "Window.h"

Window::Window(WindowData& data)
{
    CreateOpenGLWindow(data);
}

Window::~Window()
{
	Destroy();
    LOG_INFO("Window destroyed");
}

void Window::update()
{
	glfwSwapBuffers(window);
}

void Window::CreateOpenGLWindow(WindowData& data)
{
    Windata.width = data.width;
    Windata.height = data.height;
    Windata.name = data.name;

    if (!glfwInit()) {
        LOG_ERROR("Failed to initialize GLFW");
        exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(Windata.width, Windata.height, Windata.name.c_str(), nullptr, nullptr);
    if (window == nullptr) {
        LOG_ERROR("Failed to create GLFW window");
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG_ERROR("Failed to initialize GLAD");
        exit(-1);
    }
}

void Window::Destroy()
{
	glfwDestroyWindow(window);
}
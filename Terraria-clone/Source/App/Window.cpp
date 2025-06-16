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
	glfwSwapBuffers(m_window);
    glfwPollEvents();
}

void Window::CreateOpenGLWindow(WindowData& data)
{
    m_Windata.width = data.width;
    m_Windata.height = data.height;
    m_Windata.name = data.name;

    if (!glfwInit()) {
        LOG_ERROR("Failed to initialize GLFW");
        exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(m_Windata.width, m_Windata.height, m_Windata.name.c_str(), nullptr, nullptr);
    if (m_window == nullptr) {
        LOG_ERROR("Failed to create GLFW window");
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(0);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG_ERROR("Failed to initialize GLAD");
        exit(-1);
    }
    glEnable(GL_DEPTH_BUFFER_BIT);

    glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
        {
            LOG_INFO("Window closed");
        });
}

void Window::Destroy()
{
	glfwDestroyWindow(m_window);
}
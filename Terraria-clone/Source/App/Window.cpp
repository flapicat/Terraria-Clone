#include "trpch.h"
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

    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
            glViewport(0, 0, width, height);
            //LOG_INFO("Framebuffer resized to {0}x{1}", width, height);
        });

    glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            if (action == GLFW_PRESS){
                //LOG_INFO("Key pressed: {0}", key);
            }
            else if (action == GLFW_RELEASE){
                //LOG_INFO("Key Released: {0}", key);
            }
        });

    glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
            if (action == GLFW_PRESS){
                //LOG_INFO("Mouse Button Pressed: {0}", button);
            }
            else if (action == GLFW_RELEASE){
                //LOG_INFO("Mouse Button Released: {0}", button);
            }
        });

    glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos) {
            //LOG_INFO("Mouse moved to: ({}, {})", xpos, ypos);
        });

    glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xoffset, double yoffset) {
            if (yoffset > 0)
            {
                m_ScrollUp = true;
            }
            else if (yoffset < 0)
            {
                m_ScrollDown = true;
            }
            else
            {
                m_ScrollUp = false;
                m_ScrollDown = false;
            }
            //LOG_INFO("Scroll: ({}, {})", xoffset, yoffset);
        });
}

void Window::Destroy()
{
	glfwDestroyWindow(m_window);
}

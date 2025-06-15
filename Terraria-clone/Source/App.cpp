#include "App.h"

App* App::s_Instance = nullptr;

App::App()
{
    s_Instance = this;
    LOG_INFO("Window try to create");
    Window::WindowData data{ 1600, 900, "Terraria" };
    m_window = std::make_unique<Window>(data);
    LOG_INFO("Window created width: {0}, height: {1}, title: {2}", data.width, data.height, data.name);

}

void App::Run()
{
    while (running) 
    {
        glfwPollEvents();
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //UPDATE
        if (glfwWindowShouldClose(m_window->GetNativeWindow()))
        {
            running = false;
        }

        m_window->update();
    }

    glfwTerminate();
}


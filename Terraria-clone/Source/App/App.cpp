#include "App.h"

App* App::s_Instance = nullptr;

App::App()
{
    s_Instance = this;
    LOG_INFO("Window try to create");
    Window::WindowData data{ 1600, 900, "Terraria" };
    m_window = std::make_unique<Window>(data);
    LOG_INFO("Window created width: {0}, height: {1}, title: {2}", data.width, data.height, data.name);

    m_game = std::make_unique<Game>();
}

void App::Run()
{
    while (running) 
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        m_game->update();

        //UPDATE
        if (glfwWindowShouldClose(m_window->GetNativeWindow()))
        {
            running = false;
        }

        //RENDER
        m_game->render();

        m_window->update();
    }

    glfwTerminate();
}


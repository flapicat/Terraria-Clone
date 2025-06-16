#include "App.h"

App* App::s_Instance = nullptr;

App::App()
{
    s_Instance = this;
    Window::WindowData data{ 1600, 900, "Terraria" };
    m_window = std::make_unique<Window>(data);
    LOG_INFO("Window created width: {0}, height: {1}, title: {2}", data.width, data.height, data.name);

    m_game = std::make_unique<Game>();
    m_game->SetApp(this);
}

void App::Run()
{
    while (running) 
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //UPDATE
        DeltaTime::updateDeltaTime();
        if (glfwWindowShouldClose(m_window->GetNativeWindow()))
        {
            running = false;
        }
        m_game->update();

        //RENDER
        m_game->render();

        m_window->update();
    }

    glfwTerminate();
}


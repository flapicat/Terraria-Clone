#include "App.h"

App* App::s_Instance = nullptr;

App::App()
{
    s_Instance = this;
    LOG_INFO("Window try to create");
    Window::WindowData data{ 1600, 900, "Terraria" };
    m_window = std::make_unique<Window>(data);
    LOG_INFO("Window created width: {0}, height: {1}, title: {2}", data.width, data.height, data.name);

    float vertices[] = {
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    m_shader = std::make_unique<Shader>("assets/shaders/default.vert", "assets/shaders/default.frag");

    VA = std::make_unique<VertexArray>();
    VA->bind();

    std::shared_ptr<VertexBuffer> VB = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
    std::shared_ptr<IndexBuffer>  IB = std::make_unique<IndexBuffer>(indices, sizeof(indices) / sizeof(unsigned int));

    VA->setVertexBuffer(VB);
    VA->setIndexBuffer(IB);

    VA->unbind();
}

void App::Run()
{
    while (running) 
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //UPDATE
        if (glfwWindowShouldClose(m_window->GetNativeWindow()))
        {
            running = false;
        }
        //RENDER
        m_shader->use();
        VA->bind();
        glDrawElements(GL_TRIANGLES, VA->getIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);


        m_window->update();
    }

    glfwTerminate();
}


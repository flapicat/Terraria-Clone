#include "Game.h"
#include "AppHeader.h"

Game::Game()
    :m_camera(-1600, 1600, -900, 900)
{
    m_camera.SetPosition(glm::vec3(0.0f,0.0f,0.0f));
    m_camera.SetRotation(0.0f);

    float vertices[] = {
         50.5f,  100.5f, 0.0f,
         50.5f, -100.5f, 0.0f,
        -50.5f, -100.5f, 0.0f,
        -50.5f,  100.5f, 0.0f
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    m_shader = std::make_unique<Shader>("assets/shaders/default.vert", "assets/shaders/default.frag");

    m_VA = std::make_unique<VertexArray>();
    m_VA->bind();

    std::shared_ptr<VertexBuffer> VB = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
    std::shared_ptr<IndexBuffer>  IB = std::make_unique<IndexBuffer>(indices, sizeof(indices) / sizeof(unsigned int));

    m_VA->setVertexBuffer(VB);
    m_VA->setIndexBuffer(IB);

    m_VA->unbind();
}

void Game::update()
{
    handleInput();
}

void Game::render()
{
    object.UpdateModel();
    m_shader->use();
    m_shader->setMat4("u_ViewProjection", m_camera.GetViewProjectionMatrix());
    m_shader->setMat4("u_Model", object.GetModel());

    m_VA->bind();
    glDrawElements(GL_TRIANGLES, m_VA->getIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
}

void Game::handleInput()
{
    float playerSpeed = 100;
    float deltaTime = DeltaTime::getDeltaTime();
    glm::vec3 pos = object.GetPosition();
    if (Input::IskeyPressed(GLFW_KEY_A))
    {
        pos.x -= 10.0f * playerSpeed * deltaTime;
    }
    if (Input::IskeyPressed(GLFW_KEY_D))
    {
        pos.x += 10.0f * playerSpeed * deltaTime;
    }
    if (Input::IskeyPressed(GLFW_KEY_W))
    {
        pos.y += 10.0f * playerSpeed * deltaTime;
    }
    if (Input::IskeyPressed(GLFW_KEY_S))
    {
        pos.y -= 10.0f * playerSpeed * deltaTime;
    }
    object.setPosition(pos);
}

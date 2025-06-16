#include "Game.h"
#include <Log.h>

Game::Game()
{
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

void Game::update()
{
    handleInput();
}

void Game::render()
{
    m_shader->use();
    VA->bind();
    glDrawElements(GL_TRIANGLES, VA->getIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);

}

void Game::handleInput()
{
}

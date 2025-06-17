#include "trpch.h"
#include "Game.h"

Game::Game()
    :m_camera(-1600, 1600, -900, 900)
{
    m_camera.SetPosition(glm::vec3(0.0f,0.0f,0.0f));
    m_camera.SetRotation(0.0f);

    m_shader = std::make_unique<Shader>("assets/shaders/default.vert", "assets/shaders/default.frag");
}

void Game::update()
{
    handleInput();
    m_player.update();
}

void Game::render()
{
    m_shader->use();
    m_shader->setMat4("u_ViewProjection", m_camera.GetViewProjectionMatrix());
    m_player.render(m_shader);
}
void Game::handleInput()
{
    float deltaTime = DeltaTime::getDeltaTime();
}

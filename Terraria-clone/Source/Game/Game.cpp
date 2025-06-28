#include "trpch.h"
#include "Game.h"
#include "Input.h"

Game::Game()
    :m_camera(-1600, 1600, -900, 900), map(4200,1200)
{
    LoadAssets();
    m_camera.SetPosition(glm::vec3(0.0f,0.0f,0.0f));
    m_camera.SetRotation(0.0f);

    m_TextureShader = std::make_shared<Shader>("assets/shaders/TextureShader.vert", "assets/shaders/TextureShader.frag");
}

void Game::update()
{
    handleInput();
    m_player.update();
    AttachCameraToPlayer(attachCameraToPlayer);
}

void Game::render()
{
    m_TextureShader->use();
    m_TextureShader->setMat4("u_ViewProjection", m_camera.GetViewProjectionMatrix());
    map.render(m_TextureShader);
    m_player.render(m_TextureShader);
}

void Game::AttachCameraToPlayer(bool x)
{
    if (x)
    {
        m_camera.SetPosition(m_player.GetPosition());
    }
}

void Game::handleInput()
{

}

#include "trpch.h"
#include "Player.h"

#include "input.h"

Player::Player()
{
    m_VA = std::make_unique<VertexArray>();
    m_VA->bind();
    
    std::shared_ptr<VertexBuffer> VB = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
    std::shared_ptr<IndexBuffer>  IB = std::make_unique<IndexBuffer>(indices, sizeof(indices) / sizeof(unsigned int));
    
    m_VA->setVertexBuffer(VB);
    m_VA->setIndexBuffer(IB);
    
    m_VA->unbind();
}

void Player::update()
{
    input();
}

void Player::render(std::unique_ptr<Shader>& shader)
{
    this->UpdateModel();
    shader->use();
    shader->setMat4("u_Model", this->GetModel());

    m_VA->bind();
    glDrawElements(GL_TRIANGLES, m_VA->getIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
}

void Player::input()
{
    float deltaTime = DeltaTime::getDeltaTime();

    glm::vec3 pos = this->GetPosition();
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
    this->setPosition(pos);
}

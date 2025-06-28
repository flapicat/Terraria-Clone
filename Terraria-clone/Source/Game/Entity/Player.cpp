#include "trpch.h"
#include "Player.h"
#include "input.h"

Player::Player()
{
    std::vector<glm::vec3> vertexPos = {
        { 30.0f,  60.0f, 0.0f },
        { 30.0f, -60.0f, 0.0f },
        {-30.0f, -60.0f, 0.0f },
        {-30.0f,  60.0f, 0.0f }
    };

    std::vector<unsigned int> indices = {
        0, 1, 3,
        1, 2, 3
    };

    std::vector<Vertex::Vertex> VertexVertices = Vertex::CreateVertex(vertexPos, &vertexTexCords);
    FloatVertices = Vertex::CreateVerticesFloat(VertexVertices);

    m_VA.reset(new VertexArray());
    m_VA->bind();

    std::shared_ptr<VertexBuffer> VB; 
    VB.reset(new VertexBuffer(FloatVertices.data() , FloatVertices.size() * sizeof(float)));
    m_VA->setVertexBuffer(VB);

    std::shared_ptr<IndexBuffer>  IB; 
    IB.reset(new IndexBuffer(indices.data() , indices.size()));
    m_VA->setIndexBuffer(IB);
    
    m_VA->unbind();
}

void Player::update()
{
    input();
}

void Player::render(const std::shared_ptr<Shader>& shader)
{
    this->UpdateModel();

    shader->use();
    shader->setMat4("u_Model", this->GetModel());
    shader->setInt("u_Texture", 0);

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
    if (Input::IskeyPressed(GLFW_KEY_LEFT_CONTROL))
    {
        playerSpeed = 1000;
    }
    else
    {
        playerSpeed = 100;
    }
    this->setPosition(pos);
}

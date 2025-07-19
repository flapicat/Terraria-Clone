#include "trpch.h"
#include "Player.h"
#include "input.h"

#include "App.h"

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
}

void Player::render(const std::shared_ptr<Shader>& shader)
{
    this->UpdateModel();

    shader->use();
    shader->setMat4("u_Model", this->GetModel());
    shader->setInt("u_Texture", 0);

    m_VA->bind();
    glDrawElements(GL_TRIANGLES, m_VA->getIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
    m_VA->unbind();
}

void Player::SetPlayerPositionBasedOnBlocks(glm::vec3& position)
{
    position = glm::vec3(floor(position.x * 60), floor(position.y * 60), floor(position.z * 60));
    this->setPosition(position);
}

void Player::SetPlayerHeightBasedOnBlocks(int height)
{
    glm::vec3 pos = this->GetPosition();
    pos.y = height;
    this->setPosition(pos);
}

glm::vec3 Player::GetPlayerPositionBasedOnBlocks() const
{
    return glm::vec3(floor(GetPosition().x/60), floor(GetPosition().y / 60), floor(GetPosition().z / 60));
}

glm::vec2 Player::GetMouseWorldPos(const glm::mat4& viewProj, float width, float height)
{
    double mouseX, mouseY;
    GLFWwindow* window = static_cast<GLFWwindow*>(App::Get().GetWindow().GetNativeWindow());
    glfwGetCursorPos(window, &mouseX, &mouseY);

    float ndcX = (2.0f * mouseX) / width - 1.0f;
    float ndcY = 1.0f - (2.0f * mouseY) / height;
    glm::vec4 clipCoords = glm::vec4(ndcX, ndcY, 0.0f, 1.0f);

    glm::mat4 invViewProj = glm::inverse(viewProj);
    glm::vec4 worldPos = invViewProj * clipCoords;

    return glm::vec2(worldPos.x,worldPos.y);
}

glm::vec2 Player::GetMousePosBasedOnBlocks(const glm::mat4& viewProj, float width, float height)
{
    glm::vec2 pos = GetMouseWorldPos(viewProj, width, height);
    return glm::vec2(floor(pos.x/60),floor(pos.y/60));
}

void Player::input(glm::vec2 mapSize)
{
    //LOG_WARN("POS: {0},{1},{2}", GetPlayerPositionBasedOnBlocks().x, GetPlayerPositionBasedOnBlocks().y , GetPlayerPositionBasedOnBlocks().z);
    float deltaTime = DeltaTime::getDeltaTime();

    glm::vec3 pos = this->GetPosition();
    if (Input::IskeyPressed(GLFW_KEY_A))
    {
        pos.x -= 10.0f * playerSpeed * deltaTime;
        if (pos.x /60 < -mapSize.x / 2)
        {
            pos.x = -(mapSize.x / 2) * 60;
        }
    }
    if (Input::IskeyPressed(GLFW_KEY_D))
    {
        pos.x += 10.0f * playerSpeed * deltaTime;
        if (pos.x / 60 > mapSize.x / 2)
        {
            pos.x = (mapSize.x / 2) * 60;
        }
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

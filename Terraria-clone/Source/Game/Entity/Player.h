#pragma once

#include "Render/VertexData.h"
#include "Render/VertexArray.h"
#include "Render/Buffer.h"
#include "Render/Shader.h"

#include "Entity/Entity.h"

class Player : public Entity
{
public:
	Player();
	void update();
	void render(const std::shared_ptr<Shader>& shader);
    void SetPlayerPositionBasedOnBlocks(glm::vec3& position);
    glm::vec3 GetPlayerPositionBasedOnBlocks() const;
    void SetPlayerHeightBasedOnBlocks(int height);
    int GetPlayerHeight() const { return playerHeight; };
    glm::vec2 GetMouseWorldPos(const glm::mat4& viewProj, float width, float height);
    glm::vec2 GetMousePosBasedOnBlocks(const glm::mat4& viewProj, float width, float height);
	void input(glm::vec2 mapSize);
private:
    int playerHeight = 2;
    float playerSpeed = 100; 
    std::vector<float> FloatVertices;

    std::vector<glm::vec2> vertexTexCords = {
        {0.0f, 0.0f},
        {0.0f, 0.0f},
        {0.0f, 0.0f},
        {0.0f, 0.0f}
    };

    std::shared_ptr<VertexArray> m_VA;
};


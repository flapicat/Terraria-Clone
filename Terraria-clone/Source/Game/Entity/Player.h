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
	void input();
private:
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


#pragma once

#include "Render/VertexData.h"
#include "Render/VertexArray.h"
#include "Render/Buffer.h"
#include "Render/Shader.h"

#include "Object/Object.h"

class Player : public Object
{
public:
	Player();
	void update();
	void render(const std::shared_ptr<Shader>& shader);
	void input();
private:
    float playerSpeed = 100; 
    std::vector<float> FloatVertices;

    std::vector<glm::vec3> vertexPos = {
        { 50.0f,  100.0f, 0.0f },
        { 50.0f, -100.0f, 0.0f },
        {-50.0f, -100.0f, 0.0f },
        {-50.0f,  100.0f, 0.0f }
    };
    std::vector<glm::vec2> vertexTexCords = {
        {0.0f, 0.0f},
        {0.0f, 0.0f},
        {0.0f, 0.0f},
        {0.0f, 0.0f}
    };

    std::vector<unsigned int> indices = {
        0, 1, 3,
        1, 2, 3
    };

    std::shared_ptr<VertexArray> m_VA;
};


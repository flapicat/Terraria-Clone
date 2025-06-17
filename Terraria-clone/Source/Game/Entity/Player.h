#pragma once

#include "Render/VertexArray.h"
#include "Render/Buffer.h"
#include "Render/Shader.h"

#include "Object/Object.h"

class Player : public Object
{
public:
	Player();
	void update();
	void render(std::unique_ptr<Shader>& shader);
	void input();
private:
    float playerSpeed = 100;
    float vertices[12] = {
         50.5f,  100.5f, 0.0f,
         50.5f, -100.5f, 0.0f,
        -50.5f, -100.5f, 0.0f,
        -50.5f,  100.5f, 0.0f
    };
    unsigned int indices[6] = {
        0, 1, 3,
        1, 2, 3
    };
    std::shared_ptr<VertexArray> m_VA;
};


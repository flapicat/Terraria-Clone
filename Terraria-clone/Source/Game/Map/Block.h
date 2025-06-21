#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Render/Texture.h"

class Block
{
public:
    Block(TextureCoords texture);
    std::vector<glm::vec2> GetTexCoords() const { return vertexTexCords; }
private:
    std::vector<glm::vec2> vertexTexCords = {
        {0.0f, 0.0f},
        {0.0f, 0.0f},
        {0.0f, 0.0f},
        {0.0f, 0.0f}
    };
};
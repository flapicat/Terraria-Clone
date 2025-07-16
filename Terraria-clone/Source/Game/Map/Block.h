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

namespace TextureName
{
    constexpr TextureCoords AIR(22, 1);
    constexpr TextureCoords DIRT_TEXTURE_1(2, 1);
    constexpr TextureCoords DIRT_TEXTURE_2(2, 2);
    constexpr TextureCoords GRASS_TEXTURE_1(3, 1);
    constexpr TextureCoords STONE_TEXTURE_1(4, 1);
    constexpr TextureCoords SAND_TEXTURE_1(6, 1);
}
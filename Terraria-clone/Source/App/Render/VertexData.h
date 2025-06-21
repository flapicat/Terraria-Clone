#pragma once
#include <glm/glm.hpp>

namespace Vertex
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec2 texCoord;

        Vertex(const glm::vec3& pos = {},
            const glm::vec2& tex = {})
            : position(pos), texCoord(tex)
        {
        }
    };

    inline std::vector<Vertex> CreateVertex(const std::vector<glm::vec3>& positions,
        const std::vector<glm::vec2>* texCoords = nullptr)
    {
        std::vector<Vertex> vertices;
        int size = positions.size();
        for (int i = 0; i < size; i++)
        {
            glm::vec2 tex = texCoords && i < texCoords->size() ? (*texCoords)[i] : glm::vec2(0.0f);
            vertices.emplace_back(positions[i], tex);
        }

        return vertices;
    }

    inline std::vector<float> CreateVerticesFloat(const std::vector<Vertex>& vertices)
    {
        std::vector<float> floatData;
        for (const auto& v : vertices)
        {
            floatData.push_back(v.position.x);
            floatData.push_back(v.position.y);
            floatData.push_back(v.position.z);

            floatData.push_back(v.texCoord.x);
            floatData.push_back(v.texCoord.y);
        }
        return floatData;
    }
}
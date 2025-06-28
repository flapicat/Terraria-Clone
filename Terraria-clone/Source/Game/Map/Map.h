#pragma once
#include "Assets.h"
#include "Blocks.h"

#include "Render/Shader.h"
#include "Render/VertexArray.h"
#include "Render/Buffer.h"

#include "NoiseGeneration.h"

class Map
{
public:
	Map(int width, int height);

	void render(const std::shared_ptr<Shader>& shader);
private:
	int MapWidth, MapHeight; 
	std::vector<std::string> mapMatrix;
	std::shared_ptr<VertexArray> m_VA;
private:
	void generate(std::vector<float>& vertices, std::vector<unsigned int>& indices);
};

inline std::unordered_map<char, std::vector<glm::vec2>> texCashe =
{
	{ 'G', Blocks[GRASS1].GetTexCoords() },
	{ 'S', Blocks[STONE1].GetTexCoords() },
	{ 'X', Blocks[DIRT1].GetTexCoords() },
};
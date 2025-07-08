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
public:
	std::vector<std::string> GetMapMatrix() const { return mapMatrix; };
	glm::vec2 GetMapSize() const { return glm::vec2(MapWidth, MapHeight); };
	int getHeightBasedOnX(int xPos) const;
	void EraseBlockAtPos(int width, int height);
	void PlaceBlockAtPos(int width, int height, char blockType);
	void ReloadAllMap();
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
	{ 'W', Blocks[SAND1].GetTexCoords() },
};
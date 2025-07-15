#pragma once
#include "Assets.h"
#include "Blocks.h"

#include "Render/Shader.h"
#include "Render/VertexArray.h"
#include "Render/Buffer.h"

#include "Chunk.h"
#include "NoiseGeneration.h"

enum MapSize
{
	SMALL,
	NORMAL,
	LARGE
};

class Map
{
public:
	Map(MapSize size);

	void render(const std::shared_ptr<Shader>& shader);
	void setBlockAtPosition(int x, int y, char BlockChar);
	char getBlockAtPosition(int x, int y);

private:
	int mapWidth;
	int mapHeight;
	glm::vec3 m_position = { 0.0,0.0,0.0 };
	std::vector<std::vector<Chunk>> m_Chunks;
};
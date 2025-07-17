#pragma once
#include "Assets.h"
#include "Blocks.h"

#include "Render/Shader.h"
#include "Render/VertexArray.h"
#include "Render/Buffer.h"

#include "Chunk.h"

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

	void render(const std::shared_ptr<Shader>& shader, glm::vec3 cameraPos, glm::vec2 viewportSize);

	void setBlockAtPositionUnSafe(int BlockX, int BlockY, char BlockChar);
	void setBlockAtPosition(int BlockX, int BlockY, char BlockChar);
	void setBlockAtPositionWithoutReloading(int BlockX, int BlockY, char BlockChar);
	char getBlockAtPosition(int x, int y);
	void EraseBlockAtPosition(int x, int y);
private:
	void generateMap(int width,int height);
private:
	int mapWidthInWorldSpace; int mapHeightInWorldSpace;
	int mapWidthInTiles; int mapHeightInTiles;

	glm::vec3 m_position = { 0.0,0.0,0.0 };
	std::vector<std::vector<Chunk>> m_Chunks;
};

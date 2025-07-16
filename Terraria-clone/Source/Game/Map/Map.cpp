#include "trpch.h"
#include "Map.h"

const int CHUNK_SIZE = 16;
const int TILE_SIZE = 30;

Map::Map(MapSize size)
{
	int NumOfChunksX = 10;
	int NumOfChunksY = 10;
	mapWidth = NumOfChunksX * CHUNK_SIZE * TILE_SIZE;
	mapHeight = NumOfChunksY * CHUNK_SIZE * TILE_SIZE;
	//switch (size)
	//{
	//case SMALL:
	//	//4400 × 1200 (TILES)
	//	mapWidth = 4400;
	//	mapHeight = 1200;
	//	NumOfChunksX = 275;
	//	NumOfChunksY = 75;
	//	break;
	//case NORMAL:
	//	//6400 × 2000 (TILES)
	//	mapWidth = 6400;
	//	mapHeight = 2000;
	//	NumOfChunksX = 400;
	//	NumOfChunksY = 125;;
	//	break;
	//case LARGE:
	//	//8400 × 2400 (TILES)
	//	mapWidth = 8400;
	//	mapHeight = 2400;
	//	NumOfChunksX = 525;
	//	NumOfChunksY = 150;
	//	break;
	//}

	m_position = { 0.0,0.0,0.0 };
	//m_position = { -mapWidth / 2, mapHeight / 4,0.0 };

	m_Chunks.resize(NumOfChunksX);
	for (int x = 0; x < NumOfChunksX; x++)
	{
		for (int y = 0; y < NumOfChunksY; y++)
		{
			m_Chunks[x].push_back(Chunk(glm::vec3(
				(x * 30 * 16) + m_position.x,
				-(y * 30 * 16) + m_position.y,
				0.0))
			);
		}
	}
}

void Map::render(const std::shared_ptr<Shader>& shader)
{
	Textures::blocksTexture.bind();

	for (int x = 0; x < m_Chunks.size(); x++)
	{
		for (int y = 0; y < m_Chunks[x].size(); y++)
		{
			m_Chunks[x][y].render(shader);
		}
	}

	Textures::blocksTexture.unbind();
}

void Map::setBlockAtPosition(int BlockX, int BlockY, char BlockChar)
{
	int chunkIndexX = 0;
	int chunkIndexY = 0;

	chunkIndexX = floor(BlockX / CHUNK_SIZE);
	chunkIndexY = floor(BlockY / CHUNK_SIZE);

	Chunk& chunk = m_Chunks[chunkIndexX][chunkIndexY];

	int localX = 0;
	int localY = 0;

	int x = BlockX / CHUNK_SIZE; x;
	int y = BlockY / CHUNK_SIZE; y;
	localX = BlockX - CHUNK_SIZE * x;
	localY = BlockY - CHUNK_SIZE * y;

	if (localX >= 0 && localX < CHUNK_SIZE && localY >= 0 && localY < CHUNK_SIZE)
	{
		//LOG_WARN("Setting local ({0}, {1}) in chunk ({2}, {3}) with {4}", localX, localY, chunkIndexX, chunkIndexY, BlockChar);
		chunk.SetBlockAtPositionInsideChunk(localX, localY, BlockChar);
		chunk.ReloadAllChunk();
	}
}

char Map::getBlockAtPosition(int BlockX, int BlockY)
{
	int chunkIndexX = 0;
	int chunkIndexY = 0;

	chunkIndexX = floor(BlockX / CHUNK_SIZE);
	chunkIndexY = floor(BlockY / CHUNK_SIZE);

	Chunk& chunk = m_Chunks[chunkIndexX][chunkIndexY];

	int localX = 0;
	int localY = 0;

	int x = BlockX / CHUNK_SIZE; x;
	int y = BlockY / CHUNK_SIZE; y;
	localX = BlockX - CHUNK_SIZE * x;
	localY = BlockY - CHUNK_SIZE * y;

	char blockChar = chunk.GetBlockAtPositionInsideChunk(localX, localY);
	return blockChar;
}

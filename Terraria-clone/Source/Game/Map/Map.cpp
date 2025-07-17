#include "trpch.h"
#include "Map.h"

#include "FastNoiseLite.h"

const int CHUNK_SIZE = 16;
const int TILE_SIZE = 60;

Map::Map(MapSize size)
{
	int NumOfChunksX = 10;
	int NumOfChunksY = 10;
	//switch (size)
	//{
	//case SMALL:
	//	//4400 × 1200 (TILES)
	//	NumOfChunksX = 275;
	//	NumOfChunksY = 75;
	//	break;
	//case NORMAL:
	//	//6400 × 2000 (TILES)
	//	NumOfChunksX = 400;
	//	NumOfChunksY = 125;
	//	break;
	//case LARGE:
	//	//8400 × 2400 (TILES)
	//	NumOfChunksX = 525;
	//	NumOfChunksY = 150;
	//	break;
	//}
	mapWidthInWorldSpace = NumOfChunksX * CHUNK_SIZE * TILE_SIZE;
	mapHeightInWorldSpace = NumOfChunksY * CHUNK_SIZE * TILE_SIZE;
	mapWidthInTiles = NumOfChunksX * CHUNK_SIZE;
	mapHeightInTiles = NumOfChunksY * CHUNK_SIZE;

	m_position = { 0.0,0.0,0.0 };

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
	generateMap(mapWidthInTiles, mapHeightInTiles);
}

void Map::render(const std::shared_ptr<Shader>& shader, glm::vec3 cameraPos, glm::vec2 viewportSize)
{
	//LOG_WARN("cameraPOS: {0},{1}", cameraPos.x, cameraPos.y);
	const int marginX = 2;
	const int marginY = 1;

	int chunkWorldSize = CHUNK_SIZE * TILE_SIZE;
	int chunkCountX = m_Chunks.size();
	int chunkCountY = m_Chunks[0].size();

	int startX = std::max(0, (int)std::floor(cameraPos.x / chunkWorldSize) - marginX);
	int endX = std::min(chunkCountX, (int)std::floor((cameraPos.x + viewportSize.x) / chunkWorldSize) + marginX);

	int startY = std::max(0, (int)std::floor(-cameraPos.y / chunkWorldSize) - marginY);
	int endY = std::min(chunkCountY, (int)std::floor((-cameraPos.y + viewportSize.y) / chunkWorldSize) + marginY);
	
	//LOG_WARN("X:{0};{1} Y:{2};{3} ", startX, endX, startY, endY);

	int ChunkRendered = 0;
	Textures::blocksTexture.bind();
	for (int x = startX; x < endX; x++)
	{
		for (int y = startY; y < endY; y++)
		{
			m_Chunks[x][y].render(shader);
			ChunkRendered++;
		}
	}
	//LOG_WARN("{0}", ChunkRendered);
	Textures::blocksTexture.unbind();
}

void Map::setBlockAtPositionUnSafe(int BlockX, int BlockY, char BlockChar)
{
	int chunkX = BlockX / CHUNK_SIZE;
	int chunkY = BlockY / CHUNK_SIZE;
	int localX = BlockX % CHUNK_SIZE;
	int localY = BlockY % CHUNK_SIZE;
	m_Chunks[chunkX][chunkY].SetBlockAtPositionInsideChunk(localX, localY, BlockChar);
}

void Map::setBlockAtPosition(int BlockX, int BlockY, char BlockChar)
{
	if (getBlockAtPosition(BlockX, BlockY) != BlockChar)
	{
		int chunkIndexX = 0;
		int chunkIndexY = 0;

		chunkIndexX = floor(BlockX / CHUNK_SIZE);
		chunkIndexY = floor(BlockY / CHUNK_SIZE);

		if (chunkIndexX >= 0 && chunkIndexX < m_Chunks[0].size() && chunkIndexY >= 0 && chunkIndexY < m_Chunks.size())
		{
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
	}
}

void Map::setBlockAtPositionWithoutReloading(int BlockX, int BlockY, char BlockChar)
{
	int chunkIndexX = 0;
	int chunkIndexY = 0;

	chunkIndexX = floor(BlockX / CHUNK_SIZE);
	chunkIndexY = floor(BlockY / CHUNK_SIZE);

	if (chunkIndexX >= 0 && chunkIndexX < m_Chunks[0].size() && chunkIndexY >= 0 && chunkIndexY < m_Chunks.size())
	{
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
		}
	}
}

void Map::EraseBlockAtPosition(int x, int y)
{
	setBlockAtPosition(x, y, 'A');
}

char Map::getBlockAtPosition(int BlockX, int BlockY)
{
	int chunkIndexX = 0;
	int chunkIndexY = 0;

	chunkIndexX = floor(BlockX / CHUNK_SIZE);
	chunkIndexY = floor(BlockY / CHUNK_SIZE);

	if (chunkIndexX >= 0 && chunkIndexX < m_Chunks[0].size() && chunkIndexY >= 0 && chunkIndexY < m_Chunks.size())
	{
		Chunk& chunk = m_Chunks[chunkIndexX][chunkIndexY];

		int localX = 0;
		int localY = 0;

		int x = BlockX / CHUNK_SIZE; x;
		int y = BlockY / CHUNK_SIZE; y;
		localX = BlockX - CHUNK_SIZE * x;
		localY = BlockY - CHUNK_SIZE * y;

		if (localX >= 0 && localX < CHUNK_SIZE && localY >= 0 && localY < CHUNK_SIZE)
		{
			char blockChar = chunk.GetBlockAtPositionInsideChunk(localX, localY);
			return blockChar;
		}
	}
	LOG_WARN("TRYING TO GET BLOCK OUTSIDE MAP");
}

void Map::generateMap(int width, int height)
{
	LOG_WARN("{0}; {1}", width, height);
	//TERRAIN
	int horizontLevel = height * 0.7;
	int randomSeed = rand();
	{
		FastNoiseLite horizontNoise;
		horizontNoise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
		horizontNoise.SetFrequency(0.01f);
		horizontNoise.SetSeed(randomSeed);

		int HorizontY = 0;

		for (int x = 0; x < width; ++x) {
			float noiseValue = horizontNoise.GetNoise((float)x, 0.0f);
			int variation = static_cast<int>(noiseValue * 7); // Range: [-7, 7]
			int TerrainLevel = horizontLevel + variation;
			TerrainLevel = std::clamp(TerrainLevel, 0, height - 1);

			for (int y = 0; y <= TerrainLevel; y++) {  // Invert Y: bottom is mapHeight - 1
				int flippedY = height - y - 1;

				if (y == TerrainLevel) {
					setBlockAtPositionWithoutReloading(x, flippedY, 'G'); // Grass
				}
				else if (y > TerrainLevel - 5) {
					setBlockAtPositionWithoutReloading(x, flippedY, 'X'); // Dirt
				}
				else {
					setBlockAtPositionWithoutReloading(x, flippedY, 'S'); // Stone
				}
				LOG_WARN("{0}; {1}", x, y);
			}
		}
	}

	//CAVES
	{
		randomSeed = rand();
		FastNoiseLite caveNoise;
		caveNoise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
		caveNoise.SetFrequency(0.05f);
		caveNoise.SetSeed(randomSeed);

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				if (getBlockAtPosition(x, y) == 'S' && y > horizontLevel - 50)
				{
					float caveValue = caveNoise.GetNoise((float)x, (float)y);

					if (caveValue > 0.8f) {
						setBlockAtPositionWithoutReloading(x, y, 'A');
					}
				}
			}
		}
	}

	//Reloading all chunks
	for (auto& chunkColumn : m_Chunks)
	{
		for (auto& chunk : chunkColumn)
		{
			chunk.ReloadAllChunk();
		}
	}
}

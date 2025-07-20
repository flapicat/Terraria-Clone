#include "trpch.h"
#include "Map.h"

#include "FastNoiseLite.h"

const int CHUNK_SIZE = 16;
const int TILE_SIZE = 60;

Map::Map(MapSize size)
{
	m_NumOfChunksX = 20;
	m_NumOfChunksY = 20;
	switch (size)
	{
	case SMALL:
		//4400 × 1200 (TILES)
		m_NumOfChunksX = 275;
		m_NumOfChunksY = 75;
		break;
	case NORMAL:
		//6400 × 2000 (TILES)
		m_NumOfChunksX = 400;
		m_NumOfChunksY = 125;
		break;
	case LARGE:
		//8400 × 2400 (TILES)
		m_NumOfChunksX = 525;
		m_NumOfChunksY = 150;
		break;
	}
	mapWidthInWorldSpace = m_NumOfChunksX * CHUNK_SIZE * TILE_SIZE;
	mapHeightInWorldSpace = m_NumOfChunksY * CHUNK_SIZE * TILE_SIZE;
	mapWidthInTiles = m_NumOfChunksX * CHUNK_SIZE;
	mapHeightInTiles = m_NumOfChunksY * CHUNK_SIZE;

	m_position = { 0.0,0.0,0.0 };

	m_Chunks.resize(m_NumOfChunksX);
	for (int x = 0; x < m_NumOfChunksX; x++)
	{
		m_Chunks[x].resize(m_NumOfChunksY);
		for (int y = 0; y < m_NumOfChunksY; y++)
		{
			m_Chunks[x][y] = std::make_unique<Chunk>(glm::vec3(
				(x * TILE_SIZE / 2 * CHUNK_SIZE) + m_position.x,
				-(y * TILE_SIZE / 2 * CHUNK_SIZE) + m_position.y,
				0.0)
			);
		}
	}
	m_GenerationThreadRunning = true;
	m_GenerationThread = std::thread(&Map::generationThreadLoop, this);
}

Map::~Map()
{
	{
		std::lock_guard<std::mutex> lock(m_QueueMutex);
		m_GenerationThreadRunning = false;
	}
	m_QueueCV.notify_one();
	if (m_GenerationThread.joinable())
		m_GenerationThread.join();
}

void Map::update(glm::vec3 camPos, glm::vec2 viewport)
{
	if (camPos != m_cameraPos)
	{
		m_cameraPos = camPos;
		m_viewport = viewport;
		for (int x = 0; x < m_Chunks.size(); x++) {
			for (int y = 0; y < m_Chunks[x].size(); y++) {
				if (isChunkInCameraView(x, y, m_cameraPos, m_viewport, 2, 2))
				{
					int flippedY = m_Chunks[x].size() - 1 - y;
					Chunk& chunk = *m_Chunks[x][flippedY];
					if (!chunk.getIsChunkGenerated()) {
						requestChunkGeneration(x, flippedY);
					}
				}
			}
		}
	}
}

void Map::render(const std::shared_ptr<Shader>& shader)
{
	int ChunkRendered = 0;
	Textures::blocksTexture.bind();

	for (int x = 0; x < m_Chunks.size(); x++) {
		int height = m_Chunks[x].size();
		for (int y = height - 1; y >= 0; y--) {
			if (isChunkInCameraView(x, y, m_cameraPos, m_viewport, 2, 2))
			{
				Chunk& chunk = *m_Chunks[x][y];
				chunk.render(shader);
				ChunkRendered++;
			}
		}
	}
	Textures::blocksTexture.unbind();
}

void Map::setBlockAtPositionUnSafe(int BlockX, int BlockY, char BlockChar)
{
	int chunkX = BlockX / CHUNK_SIZE;
	int chunkY = BlockY / CHUNK_SIZE;
	int localX = BlockX % CHUNK_SIZE;
	int localY = BlockY % CHUNK_SIZE;
	m_Chunks[chunkX][chunkY]->SetBlockAtPositionInsideChunk(localX, localY, BlockChar);
}

void Map::setBlockAtPosition(int BlockX, int BlockY, char BlockChar)
{
	if (getBlockAtPosition(BlockX, BlockY) != BlockChar)
	{
		int chunkIndexX = 0;
		int chunkIndexY = 0;

		chunkIndexX = floor(BlockX / CHUNK_SIZE);
		chunkIndexY = floor(BlockY / CHUNK_SIZE);

		if (chunkIndexX >= 0 && chunkIndexX < m_Chunks.size() && chunkIndexY >= 0 && chunkIndexY < m_Chunks[0].size())
		{
			Chunk& chunk = *m_Chunks[chunkIndexX][chunkIndexY];

			int localX = 0;
			int localY = 0;

			int x = BlockX / CHUNK_SIZE;
			int y = BlockY / CHUNK_SIZE;
			localX = BlockX - CHUNK_SIZE * x;
			localY = BlockY - CHUNK_SIZE * y;

			if (localX >= 0 && localX < CHUNK_SIZE && localY >= 0 && localY < CHUNK_SIZE)
			{
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

	if (chunkIndexX >= 0 && chunkIndexX < m_Chunks.size() && chunkIndexY >= 0 && chunkIndexY < m_Chunks[0].size())
	{
		Chunk& chunk = *m_Chunks[chunkIndexX][chunkIndexY];

		int localX = 0;
		int localY = 0;

		int x = BlockX / CHUNK_SIZE; x;
		int y = BlockY / CHUNK_SIZE; y;
		localX = BlockX - CHUNK_SIZE * x;
		localY = BlockY - CHUNK_SIZE * y;

		if (localX >= 0 && localX < CHUNK_SIZE && localY >= 0 && localY < CHUNK_SIZE)
		{
			chunk.SetBlockAtPositionInsideChunk(localX, localY, BlockChar);
		}
	}
}

void Map::EraseBlockAtPosition(int x, int y)
{
	setBlockAtPosition(x, y, 'A');
}

bool Map::isChunkInCameraView(int chunkX, int chunkY, glm::vec3 cameraPos, glm::vec2 viewportSize, int marginx, int marginy)
{
	const int marginX = marginx;
	const int marginY = marginy;

	int chunkWorldSize = CHUNK_SIZE * TILE_SIZE;

	int camChunkX = (int)std::floor(cameraPos.x / chunkWorldSize);
	int camChunkY = (int)std::floor(-cameraPos.y / chunkWorldSize);

	int viewChunksX = (int)std::ceil(viewportSize.x / chunkWorldSize);
	int viewChunksY = (int)std::ceil(viewportSize.y / chunkWorldSize);

	int startX = std::max(0, camChunkX - (viewChunksX / 2) - marginX);
	int endX = std::min((int)m_Chunks.size(), camChunkX + (viewChunksX / 2) + marginX);

	int startY = std::max(0, camChunkY - (viewChunksY / 2) - marginY);
	int endY = std::min((int)m_Chunks[0].size(), camChunkY + (viewChunksY / 2) + marginY);

	return (chunkX >= startX && chunkX < endX &&
		chunkY >= startY && chunkY < endY);
}

void Map::reloadAllMap()
{
	for (size_t x = 0; x < m_Chunks.size(); x++)
	{
		for (size_t y = 0; y < m_Chunks[x].size(); y++)
		{
			m_Chunks[x][y]->ReloadAllChunk();
		}
	}
}

char Map::getBlockAtPosition(int BlockX, int BlockY)
{
	int chunkIndexX = 0;
	int chunkIndexY = 0;

	chunkIndexX = floor(BlockX / CHUNK_SIZE);
	chunkIndexY = floor(BlockY / CHUNK_SIZE);

	if (chunkIndexX >= 0 && chunkIndexX < m_Chunks.size() && chunkIndexY >= 0 && chunkIndexY < m_Chunks[0].size())
	{
		Chunk& chunk = *m_Chunks[chunkIndexX][chunkIndexY];

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
	return ' ';
	LOG_WARN("TRYING TO GET BLOCK OUTSIDE MAP");
}

void Map::generateChunk(int chunkX, int chunkY)
{
	int startX = chunkX * CHUNK_SIZE;
	int startY = chunkY * CHUNK_SIZE;
	int endX = startX + CHUNK_SIZE;
	int endY = startY + CHUNK_SIZE;

	int height = mapHeightInTiles;
	int horizontLevel = height * 0.7;

	static FastNoiseLite horizontNoise, caveNoise;
	static bool noiseInitialized = false;
	if (!noiseInitialized)
	{
		int seedHorizont = rand();
		int seedCaves = rand();

		horizontNoise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
		horizontNoise.SetFrequency(0.01f);
		horizontNoise.SetSeed(seedHorizont);

		caveNoise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
		caveNoise.SetFrequency(0.05f);
		caveNoise.SetSeed(seedCaves);

		noiseInitialized = true;
	}

	Chunk& chunk = *m_Chunks[chunkX][chunkY];

	//     TERRAIN GENERATION    
	for (int x = startX; x < endX; ++x)
	{
		float noiseVal = horizontNoise.GetNoise((float)x, 0.0f);
		int variation = static_cast<int>(noiseVal * 7);
		int terrainLevel = horizontLevel + variation;
		terrainLevel = std::clamp(terrainLevel, 0, height - 1);

		for (int y = startY; y < endY; ++y)
		{
			int flippedY = height - y - 1;

			if (y <= terrainLevel)
			{
				char block;
				if (y == terrainLevel) {
					block = 'G';
				}
				else if (y > terrainLevel - 5) {
					block = 'X';
				}
				else {
					block = 'S';
				}
				setBlockAtPositionWithoutReloading(x, flippedY, block);
			}
		}
	}

	//     CAVE GENERATION    
	for (int y = startY; y < endY; ++y)
	{
		for (int x = startX; x < endX; ++x)
		{
			int flippedY = height - y - 1;

			if (getBlockAtPosition(x, flippedY) == 'S' && y < horizontLevel - 20)
			{
				float caveVal = caveNoise.GetNoise((float)x, (float)y);
				if (caveVal > 0.8f)
				{
					setBlockAtPositionWithoutReloading(x, flippedY, 'A');
				}
			}
		}
	}
}

void Map::generationThreadLoop()
{
	while (true) {
		std::pair<int, int> chunkCoords;

		{
			std::unique_lock<std::mutex> lock(m_QueueMutex);
			m_QueueCV.wait(lock, [this]() {
				return !m_GenerationQueue.empty() || !m_GenerationThreadRunning;
				});

			if (!m_GenerationThreadRunning) {
				break;
			}
			{
				chunkCoords = m_GenerationQueue.front();
				m_GenerationQueue.pop();
				m_PendingChunks.erase(chunkCoords);
			}
		}

		int x = chunkCoords.first;
		int y = chunkCoords.second;

		if (!m_Chunks[x][y]->getIsChunkGenerated()) {
			generateChunk(x, y);
			m_Chunks[x][y]->setChunkIsGenerated(true);
			m_Chunks[x][y]->ReloadAllChunk();
		}
	}
}

void Map::requestChunkGeneration(int x, int y)
{
	std::lock_guard<std::mutex> lock(m_QueueMutex);

	if (m_Chunks[x][y]->getIsChunkGenerated())
		return;

	if (m_PendingChunks.find({ x, y }) != m_PendingChunks.end())
		return;

	m_GenerationQueue.emplace(x, y);
	m_PendingChunks.emplace(x, y);
	m_QueueCV.notify_one();
}
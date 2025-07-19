#pragma once
#include "Assets.h"
#include "Blocks.h"

#include "Render/Shader.h"
#include "Render/VertexArray.h"
#include "Render/Buffer.h"

#include "Chunk.h"

#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <set>

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
	~Map();

	void update(glm::vec3 camPos, glm::vec2 viewport);
	void render(const std::shared_ptr<Shader>& shader);

	void setBlockAtPositionUnSafe(int BlockX, int BlockY, char BlockChar);
	void setBlockAtPosition(int BlockX, int BlockY, char BlockChar);
	void setBlockAtPositionWithoutReloading(int BlockX, int BlockY, char BlockChar);
	char getBlockAtPosition(int x, int y);
	void EraseBlockAtPosition(int x, int y);
	bool isChunkInCameraView(int chunkX, int chunkY, glm::vec3 cameraPos, glm::vec2 viewportSize, int marginx, int marginy);
	void reloadAllMap();
private:
	void generateChunk(int chunkX,int chunkY);
private:
	int mapWidthInWorldSpace; int mapHeightInWorldSpace;
	int mapWidthInTiles; int mapHeightInTiles;
	int m_NumOfChunksX;
	int m_NumOfChunksY;
	glm::vec3 m_position = { 0.0,0.0,0.0 };
	std::vector<std::vector<std::unique_ptr<Chunk>>> m_Chunks;
	glm::vec3 m_cameraPos = {0,0,0};
	glm::vec2 m_viewport;
private:
	//THREAD CODE
	std::thread m_GenerationThread;
	std::queue<std::pair<int, int>> m_GenerationQueue;
	std::set<std::pair<int, int>> m_PendingChunks;
	std::mutex m_QueueMutex;
	std::condition_variable m_QueueCV;
	bool m_GenerationThreadRunning = true;
private:
	void generationThreadLoop();
	void requestChunkGeneration(int x, int y);
};

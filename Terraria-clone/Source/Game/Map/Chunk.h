#pragma once

#include "Assets.h"
#include "Blocks.h"

#include "Render/Shader.h"
#include "Render/VertexArray.h"
#include "Render/Buffer.h"

class Chunk
{
public:
	Chunk() = default;
	Chunk(glm::vec3 position);
	void render(const std::shared_ptr<Shader>& shader);
public:
	std::vector<std::string>& GetChunkMatrix() { return m_ChunkMatrix; };
	glm::vec2 GetChunkSize() const { return glm::vec2(m_chunkWidth, m_chunkHeight); };
	glm::vec2 GetChunkAbsolutePosition() const { return m_position; };
	void SetBlockAtPositionInsideChunk(int x, int y, char blockChar);
	char GetBlockAtPositionInsideChunk(int x, int y);
	void setChunkIsGenerated(bool x) { isGenerated = x; }
	bool getIsChunkGenerated() const { return isGenerated; }
	void ReloadAllChunk();
private:
	bool isGenerated = false;
	const int m_chunkWidth = 16;
	const int m_chunkHeight = 16;
	std::array<std::vector<glm::vec2>, 256> texCacheArray = {};
	glm::vec3 m_position;
	std::vector<std::string> m_ChunkMatrix;
	std::shared_ptr<VertexArray> m_VA;
private:
	void initTexCache();
	void generate(std::vector<float>& vertices, std::vector<unsigned int>& indices);
private:
	std::vector<float> m_pendingVertices;
	std::vector<unsigned int> m_pendingIndices;
	std::atomic<bool> m_needsUpload = false;
	std::mutex m_meshMutex;
};
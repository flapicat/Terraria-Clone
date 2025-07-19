#pragma once

#include "Assets.h"
#include "Blocks.h"

#include "Render/Shader.h"
#include "Render/VertexArray.h"
#include "Render/Buffer.h"

class Chunk
{
public:
	Chunk(glm::vec3 position);
	void render(const std::shared_ptr<Shader>& shader);
public:
	std::vector<std::string>& GetChunkMatrix() { return ChunkMatrix; };
	glm::vec2 GetChunkSize() const { return glm::vec2(chunkWidth, chunkHeight); };
	glm::vec2 GetChunkAbsolutePosition() const { return m_position; };
	void SetBlockAtPositionInsideChunk(int x, int y, char blockChar);
	char GetBlockAtPositionInsideChunk(int x, int y);
	void setChunkIsGenerated(bool x) { isGenerated = x; }
	bool getIsChunkGenerated() const { return isGenerated; }
	void ReloadAllChunk();
private:
	bool isGenerated = false;
	const int chunkWidth = 16;
	const int chunkHeight = 16;
	glm::vec3 m_position;
	std::vector<std::string> ChunkMatrix;
	std::shared_ptr<VertexArray> m_VA;
private:
	void generate(std::vector<float>& vertices, std::vector<unsigned int>& indices);
private:
	std::vector<float> m_pendingVertices;
	std::vector<unsigned int> m_pendingIndices;
	std::atomic<bool> m_needsUpload = false;
	std::mutex m_meshMutex;
};
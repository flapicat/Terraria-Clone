#pragma once

#include "Assets.h"
#include "Blocks.h"

#include "Render/Shader.h"
#include "Render/VertexArray.h"
#include "Render/Buffer.h"

#include "NoiseGeneration.h"

class Chunk
{
public:
	Chunk(glm::vec3 position);
	void render(const std::shared_ptr<Shader>& shader);
public:
	std::vector<std::string>& GetChunkMatrix() { return mapMatrix; };
	glm::vec2 GetChunkSize() const { return glm::vec2(chunkWidth, chunkHeight); };
	glm::vec2 GetChunkAbsolutePosition() const { return m_position; };
	void SetBlockAtPositionInsideChunk(int x, int y, char blockChar);
	char GetBlockAtPositionInsideChunk(int x, int y);
	void ReloadAllChunk();
private:
	const int chunkWidth = 16;
	const int chunkHeight = 16;
	glm::vec3 m_position;
	std::vector<std::string> mapMatrix;
	std::shared_ptr<VertexArray> m_VA;
private:
	void generate(std::vector<float>& vertices, std::vector<unsigned int>& indices);
};
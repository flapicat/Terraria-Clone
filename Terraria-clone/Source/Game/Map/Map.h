#pragma once
#include "Assets.h"
#include "Blocks.h"

#include "Render/Shader.h"
#include "Render/VertexArray.h"
#include "Render/Buffer.h"

class Map
{
public:
	Map(int width, int height);

	const std::vector<float>& GetVertices() const { return vertices; }
	const std::vector<unsigned int>& GetIndices() const { return indices; }

	void render(const std::shared_ptr<Shader>& shader);
private:
	int MapWidth, MapHeight;
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	std::shared_ptr<VertexArray> m_VA;
private:
	void generate();
};
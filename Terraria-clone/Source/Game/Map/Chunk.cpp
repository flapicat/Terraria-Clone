#include "trpch.h"
#include "Chunk.h"

inline std::unordered_map<char, std::vector<glm::vec2>> texCashe =
{
	{ 'G', Blocks[GRASS1].GetTexCoords() },
	{ 'S', Blocks[STONE1].GetTexCoords() },
	{ 'X', Blocks[DIRT1].GetTexCoords() },
	{ 'W', Blocks[SAND1].GetTexCoords() },
};

Chunk::Chunk(glm::vec3 position)
{
	//TEMP
	mapMatrix.resize(chunkHeight, std::string(chunkWidth, 'A'));
	for (int y = 0; y < mapMatrix.size(); y++) {
		for (int x = 0; x < mapMatrix[y].size(); x++) {
			char& tile = mapMatrix[chunkHeight - y - 1][x];
			tile = 'X';
		}
	}
	//
	m_position = position;
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	generate(vertices, indices);

	m_VA.reset(new VertexArray());
	m_VA->bind();

	std::shared_ptr<VertexBuffer> VB;
	VB.reset(new VertexBuffer(vertices.data(), vertices.size() * sizeof(float)));
	m_VA->setVertexBuffer(VB);

	std::shared_ptr<IndexBuffer>  IB;
	IB.reset(new IndexBuffer(indices.data(), indices.size()));
	m_VA->setIndexBuffer(IB);

	m_VA->unbind();
}

void Chunk::render(const std::shared_ptr<Shader>& shader)
{
	glm::mat4 m_model = glm::mat4(1.0f);
	m_model = glm::translate(m_model, m_position);

	shader->use();
	shader->setInt("u_Texture", 0);
	shader->setMat4("u_Model", m_model);

	m_VA->bind();
	glDrawElements(GL_TRIANGLES, m_VA->getIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
}

void Chunk::SetBlockAtPositionInsideChunk(int x, int y, char blockChar)
{
	if (x >= 0 && x < chunkWidth && y >= 0 && y < chunkHeight)
	{
		mapMatrix[y][x] = blockChar;
		ReloadAllChunk();
	}
}

char Chunk::GetBlockAtPositionInsideChunk(int x, int y)
{
	if (x >= 0 && x < chunkWidth && y >= 0 && y < chunkHeight)
	{
		return mapMatrix[y][x];
	}
	return 'e';
}


void Chunk::ReloadAllChunk()
{
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	generate(vertices, indices);

	m_VA = std::make_shared<VertexArray>();
	m_VA->bind();

	std::shared_ptr<VertexBuffer> VB = std::make_shared<VertexBuffer>(vertices.data(), vertices.size() * sizeof(float));
	m_VA->setVertexBuffer(VB);

	std::shared_ptr<IndexBuffer> IB = std::make_shared<IndexBuffer>(indices.data(), indices.size());
	m_VA->setIndexBuffer(IB);

	m_VA->unbind();
}

void Chunk::generate(std::vector<float>& vertices, std::vector<unsigned int>& indices)
{

	vertices.clear();
	vertices.reserve(chunkWidth * chunkHeight * 20); // 20 floats per block

	indices.clear();
	indices.reserve(chunkWidth * chunkHeight * 6);   // 6 indices per block

	unsigned int offset = 0;

	const float BlockSize = 60.0f;

	float xpos = 0.0f;
	float ypos = 0.0f;
	float z = 0.0f;


	for (int y = 0; y < mapMatrix.size(); y++) {
		for (int x = 0; x < mapMatrix[y].size(); x++) {
			char tile = mapMatrix[y][x];
			xpos = m_position.x + x * BlockSize;
			ypos = m_position.y + y * -BlockSize;
			z = 0.0f;

			if (tile == 'A') continue;

			auto& tex = texCashe[tile];

			vertices.insert(vertices.end(), {
				xpos              , ypos + BlockSize, z, tex[3].x, tex[3].y,
				xpos + BlockSize  , ypos + BlockSize, z, tex[0].x, tex[0].y,
				xpos + BlockSize  , ypos            , z, tex[1].x, tex[1].y,
				xpos              , ypos            , z, tex[2].x, tex[2].y
				});

			indices.insert(indices.end(), {
				offset + 0, offset + 1, offset + 2,
				offset + 2, offset + 3, offset + 0
				});

			offset += 4;
		}
	}
}

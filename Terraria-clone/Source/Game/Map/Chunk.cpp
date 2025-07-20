#include "trpch.h"
#include "Chunk.h"


void Chunk::initTexCache()
{
	texCacheArray['A'] = Blocks[AIR].GetTexCoords();
	texCacheArray['G'] = Blocks[GRASS1].GetTexCoords();
	texCacheArray['S'] = Blocks[STONE1].GetTexCoords();
	texCacheArray['X'] = Blocks[DIRT1].GetTexCoords();
	texCacheArray['W'] = Blocks[SAND1].GetTexCoords();
}

Chunk::Chunk(glm::vec3 position)
{
	initTexCache();
	m_ChunkMatrix.resize(m_chunkHeight, std::string(m_chunkWidth, 'A'));

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
	if (m_needsUpload)
	{
		std::lock_guard<std::mutex> lock(m_meshMutex);
		if (!m_pendingVertices.empty() && !m_pendingIndices.empty())
		{
			m_VA = std::make_shared<VertexArray>();
			m_VA->bind();

			auto VB = std::make_shared<VertexBuffer>(m_pendingVertices.data(), m_pendingVertices.size() * sizeof(float));
			auto IB = std::make_shared<IndexBuffer>(m_pendingIndices.data(), m_pendingIndices.size());

			m_VA->setVertexBuffer(VB);
			m_VA->setIndexBuffer(IB);
			m_VA->unbind();

			m_pendingVertices.clear();
			m_pendingIndices.clear();
			m_needsUpload = false;
		}
	}

	if (!m_VA) return;

	glm::mat4 m_model = glm::translate(glm::mat4(1.0f), m_position);

	shader->use();
	shader->setInt("u_Texture", 0);
	shader->setMat4("u_Model", m_model);

	m_VA->bind();
	glDrawElements(GL_TRIANGLES, m_VA->getIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
	m_VA->unbind();
}

void Chunk::SetBlockAtPositionInsideChunk(int x, int y, char blockChar)
{
	if (x >= 0 && x < m_chunkWidth && y >= 0 && y < m_chunkHeight)
	{
		m_ChunkMatrix[y][x] = blockChar;
		ReloadAllChunk();
	}
}

char Chunk::GetBlockAtPositionInsideChunk(int x, int y)
{
	if (x >= 0 && x < m_chunkWidth 
		&& y >= 0 && y < m_chunkHeight)
	{
		return m_ChunkMatrix[y][x];
	}
	return 'e';
}


void Chunk::ReloadAllChunk()
{
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	generate(vertices, indices);

	{
		std::lock_guard<std::mutex> lock(m_meshMutex);
		m_pendingVertices = std::move(vertices);
		m_pendingIndices = std::move(indices);
		m_needsUpload = true;
	}
}


void Chunk::generate(std::vector<float>& vertices, std::vector<unsigned int>& indices)
{
	vertices.clear();
	vertices.reserve(m_chunkWidth * m_chunkHeight * 20); // 20 floats per block

	indices.clear();
	indices.reserve(m_chunkWidth * m_chunkHeight * 6);   // 6 indices per block

	unsigned int offset = 0;

	const float BlockSize = 60.0f;

	float xpos = 0.0f;
	float ypos = 0.0f;
	float z = 0.0f;


	for (int y = 0; y < m_ChunkMatrix.size(); y++) {
		for (int x = 0; x < m_ChunkMatrix[y].size(); x++) {
			char tile = m_ChunkMatrix[y][x];
			xpos = m_position.x + x * BlockSize;
			ypos = m_position.y + y * -BlockSize;
			z = 0.0f;

			//if (tile == 'A') continue;

			auto& tex = texCacheArray[tile];

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

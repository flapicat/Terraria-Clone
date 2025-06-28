#include "trpch.h"
#include "Map.h"

Map::Map(int width, int height)
	:MapWidth(width), MapHeight(height)
{
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	GenertateTerrain(MapWidth, MapHeight, mapMatrix);
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

void Map::render(const std::shared_ptr<Shader>& shader)
{
	shader->use();
	Textures::blocksTexture.bind();

	shader->setInt("u_Texture", 0);
	shader->setMat4("u_Model", glm::mat4(1.0f));
	
	m_VA->bind();
	glDrawElements(GL_TRIANGLES, m_VA->getIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
	Textures::blocksTexture.unbind(); 
}

void Map::generate(std::vector<float>& vertices, std::vector<unsigned int>& indices)
{
	vertices.clear();
	vertices.reserve(MapWidth * MapHeight * 20); // 20 floats per block

	indices.clear();
	indices.reserve(MapWidth * MapHeight * 6);   // 6 indices per block

	unsigned int offset = 0;

	const float BlockSize = 60.0f;
	float startPosX = -MapWidth/2;
	float startPosY = (-MapHeight / 2) + MapHeight /6;

	float xpos = 0.0f;
	float ypos = 0.0f;
	float z = 0.0f;


	for (int y = 0 ; y < mapMatrix.size() ; y++) {
		for (int x = 0; x < mapMatrix[y].size(); x++) {
			char tile = mapMatrix[y][x];
			xpos = (x + startPosX) * BlockSize;
			ypos = (y + startPosY) * -BlockSize;
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

	LOG_INFO("Map generated");
}

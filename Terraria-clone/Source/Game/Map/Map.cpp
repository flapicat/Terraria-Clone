#include "trpch.h"
#include "Map.h"

Map::Map(int width, int height)
	:MapWidth(width), MapHeight(height)
{
	generate();

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
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	Textures::blocksTexture.unbind(); 
}

void Map::generate()
{
	vertices.clear();
	indices.clear();

	unsigned int offset = 0;

	auto& tex = Blocks[AIR].GetTexCoords();

	for (int x = 0; x < MapWidth; x++)
	{
		for (int y = 0; y < MapHeight; y++)
		{
			float BlockSize = 60.0f;
			float startPosX = -(BlockSize /2);
			float startPosY = 3.0f;
			float xpos = (x + startPosX) * BlockSize;
			float ypos = (y + startPosY) * -BlockSize;
			float z = 0.0f;


			y == 0 ? tex = Blocks[GRASS1].GetTexCoords() : tex = Blocks[DIRT1].GetTexCoords();

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

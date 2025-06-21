#include"trpch.h"
#include "Texture.h"

Texture::Texture()
{
}

void Texture::loadTexture(const char* filepath)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannels;
	unsigned char* data = stbi_load(filepath, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		LOG_WARN("Failed to load BLOCK texture");
	}
	stbi_image_free(data);
	LOG_TRACE("Texture Loaded: {0}", filepath);
}

void setBlockTexture(std::vector<glm::vec2>& vertexTexCords, TextureCoords texture)
{
	auto UVs = getTileUVs(texture.GetU(), texture.GetV());
	vertexTexCords[0].x = UVs[0].u;
	vertexTexCords[0].y = UVs[0].v;

	vertexTexCords[1].x = UVs[1].u;
	vertexTexCords[1].y = UVs[1].v;

	vertexTexCords[2].x = UVs[2].u;
	vertexTexCords[2].y = UVs[2].v;

	vertexTexCords[3].x = UVs[3].u;
	vertexTexCords[3].y = UVs[3].v;
}

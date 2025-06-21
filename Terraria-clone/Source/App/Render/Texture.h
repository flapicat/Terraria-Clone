#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <glm/glm.hpp>

#include "TextureCoord.h"

struct TextureCoords {
	int u;
	int v;

	constexpr TextureCoords(int u = 0, int v = 0) :
		u(u), v(v) 
	{
	}

	std::pair<int, int> GetTextureCoords() const {
		return { u, v };
	}

	int GetU() const { return u; }
	int GetV() const { return v; }
};

class Texture
{
public:
	Texture();
	Texture(const char* filepath) { loadTexture(filepath); }

	void bind(GLenum textureUnit = GL_TEXTURE0) const {
		glActiveTexture(textureUnit);
		glBindTexture(GL_TEXTURE_2D, texture);
	}
	void unbind(){
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void loadTexture(const char* filepath);
	unsigned int getTexture() { return texture; };
private:
	unsigned int texture;
};

void setBlockTexture(std::vector<glm::vec2>& vertexTexCords, TextureCoords texture);

namespace TextureName
{
	constexpr TextureCoords AIR(71,7);
	constexpr TextureCoords DIRT_TEXTURE_1(2, 1);
	constexpr TextureCoords DIRT_TEXTURE_2(2, 2);
	constexpr TextureCoords GRASS_TEXTURE_1(3, 1);
}
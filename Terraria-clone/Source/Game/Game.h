#pragma once
#include "Render/Shader.h"
#include "Render/Buffer.h"
#include "Render/VertexArray.h"

class Game
{
public:
	Game();
	void update();
	void render();
private:
	void handleInput();
	std::unique_ptr<Shader> m_shader;
	std::shared_ptr<VertexArray> VA;

};


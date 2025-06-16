#pragma once

#include "Render/VertexArray.h"
#include "Render/Buffer.h"
#include "Render/Shader.h"
#include "Render/OrthographicCamera.h"

#include "Object/Object.h"

class App;

class Game
{
public:
	Game();
	void update();
	void render();
	void SetApp(App* app) { m_app = app; }
private:
	void handleInput(); 
	std::unique_ptr<Shader> m_shader;
	std::shared_ptr<VertexArray> m_VA;
	OrthographicCamera m_camera;

	Object object;

	App* m_app;
};

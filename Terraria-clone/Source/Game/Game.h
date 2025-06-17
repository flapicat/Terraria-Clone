#pragma once

#include "DeltaTime.h"

#include "Render/Shader.h"
#include "Render/OrthographicCamera.h"

#include "Entity/Player.h"

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
	OrthographicCamera m_camera;
	Player m_player;

	App* m_app;
};

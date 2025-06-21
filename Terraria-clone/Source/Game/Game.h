#pragma once

#include "Assets.h"
#include "DeltaTime.h"

#include "Render/Shader.h"
#include "Render/OrthographicCamera.h"

#include "Entity/Player.h"
#include "Map/Map.h"

class App;

class Game
{
public:
	Game();
	void update();
	void render();
	void SetApp(App* app) { m_app = app; }
	void AttachCameraToPlayer(bool x);
private:
	void handleInput(); 
private:
	bool attachCameraToPlayer = true;
	std::shared_ptr<Shader> m_TextureShader;
	OrthographicCamera m_camera;
	Player m_player;
	Map map;

	App* m_app;
};

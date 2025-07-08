#pragma once

#include "Assets.h"
#include "DeltaTime.h"

#include "Render/Shader.h"
#include "Render/OrthographicCamera.h"

#include "Entity/Player.h"
#include "Map/Map.h"

#include "ImGui/ImGuiAPI.h"

class App;

class Game
{
public:
	Game();
	~Game();
	void update();
	void render();
	void SetApp(App* app) { m_app = app; }
	void AttachCameraToPlayer(bool x);
private:
	void handleInput(); 
	std::string charToBlockName(char blockChar);
private:
	//GAME CONTROLLER
	const std::vector<char> blocksCharacterType = {'A','G','X','S','W'};
	int BlockIterator = 0;
	char currentBlock = blocksCharacterType[BlockIterator];
	//GAME
	bool attachCameraToPlayer = true;
	std::shared_ptr<Shader> m_TextureShader;
	OrthographicCamera m_camera;
	Player m_player;
	Map m_map;
	ImGuiAPI* imguiAPI;

	App* m_app;
};

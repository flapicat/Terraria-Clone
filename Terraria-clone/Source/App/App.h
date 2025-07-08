#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "DeltaTime.h"
#include "Log.h"
#include "Window.h"

#include "Game.h"

class App
{
public:
	App();
	void Run();
	void HandleInput();

	inline Window& GetWindow() { return *m_window; }
	inline static App& Get() { return *s_Instance; }
private:
	static App* s_Instance;
	bool running = true;
	std::unique_ptr<Window> m_window;
	std::unique_ptr<Game> m_game;
};


#pragma once

#include <memory>
#include <iostream>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Log.h"
#include "Window.h"
#include "Input.h"

#include "Game.h"

class App
{
public:
	App();
	void Run();

	std::unique_ptr<Window>& GetWindow() { return m_window; };
	static App* Get() { return s_Instance; };
private:
	static App* s_Instance;
	bool running = true;
	std::unique_ptr<Window> m_window;
	std::unique_ptr<Game> m_game;
};


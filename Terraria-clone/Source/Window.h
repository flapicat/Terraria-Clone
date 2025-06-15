#pragma once
#include <iostream>
#include <string>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Log.h"

class Window
{
public:
	struct WindowData
	{
		int width;
		int height;
		std::string name;
	};
	Window(WindowData& data);
	~Window();
	void update();
	void CreateOpenGLWindow(WindowData& data);
	void Destroy();

	inline GLFWwindow*& GetNativeWindow() { return window; };

	inline int GetWidth() { return Windata.width; }
	inline int GetHeight() { return Windata.height; }
private:
	GLFWwindow* window = nullptr;
	WindowData Windata;
};


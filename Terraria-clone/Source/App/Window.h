#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>

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

	inline GLFWwindow*& GetNativeWindow() { return m_window; };

	inline int GetWidth() { return m_Windata.width; }
	inline int GetHeight() { return m_Windata.height; }
private:
	GLFWwindow* m_window = nullptr;
	WindowData m_Windata;
};

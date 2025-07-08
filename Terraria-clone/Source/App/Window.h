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

	inline GLFWwindow* GetWindowPointer() { return m_window; };
	inline void* GetNativeWindow() { return m_window; };

	inline int GetWidth() { return m_Windata.width; }
	inline int GetHeight() { return m_Windata.height; }

	static inline bool GetScrollUp() { return m_ScrollUp; }
	static inline bool GetScrollDown() { return m_ScrollDown; }
	static inline bool SetScrollUp(bool x) { return m_ScrollUp = x; }
	static inline bool SetScrollDown(bool x) { return m_ScrollDown = x; }
private:
	static inline bool m_ScrollUp = false;
	static inline bool m_ScrollDown = false;
	GLFWwindow* m_window;
	WindowData m_Windata;
};

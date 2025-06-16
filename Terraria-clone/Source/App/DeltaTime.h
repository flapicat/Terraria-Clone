#pragma once
#include <GLFW/glfw3.h>

class DeltaTime
{
public:
	static void updateDeltaTime();
	static float getDeltaTime() { return s_DeltaTime; }
	static float getFPS() { return s_FPS; }
private:
	inline static float s_DeltaTime = 0.0f;
	inline static float s_LastFrame = glfwGetTime();
	inline static float s_FrameCount = 0;
	inline static float s_TotalTime = 0;
	inline static float s_FPS = 0;
};

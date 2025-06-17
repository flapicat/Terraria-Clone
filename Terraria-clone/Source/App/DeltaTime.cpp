#include "trpch.h"
#include "DeltaTime.h"

void DeltaTime::updateDeltaTime()
{
	//deltaTime
	float currentFrame = glfwGetTime();
	s_DeltaTime = currentFrame - s_LastFrame;
	s_LastFrame = currentFrame;

	//FPS
	s_TotalTime += s_DeltaTime;
	s_FrameCount++;
	s_FPS = 1.0f / s_DeltaTime;
}

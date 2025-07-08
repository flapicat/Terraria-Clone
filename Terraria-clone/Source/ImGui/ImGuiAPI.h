#pragma once
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

class ImGuiAPI
{
public:
	ImGuiAPI();
	~ImGuiAPI();

	void Create();
	void Close();

	void Begin();
	void End();
};


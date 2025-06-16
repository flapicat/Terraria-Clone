#include "Input.h"

Input* Input::s_instance = new Input;

bool Input::keyPressedImpl(int keyCode)
{
	auto window = App::Get()->GetWindow()->GetNativeWindow();
	bool x = glfwGetKey(window, keyCode) == GLFW_PRESS;
	return x;
}

bool Input::keyReleasedImpl(int keyCode)
{
	auto window = App::Get()->GetWindow()->GetNativeWindow();
	bool x = glfwGetKey(window, keyCode) == GLFW_RELEASE;
	return x;
}

bool Input::IsMouseButtonPressedImpl(int button)
{
	auto window = App::Get()->GetWindow()->GetNativeWindow();
	bool x = glfwGetMouseButton(window, button) == GLFW_PRESS;
	return x;
}

bool Input::IsMouseButtonReleasedImpl(int button)
{
	auto window = App::Get()->GetWindow()->GetNativeWindow();
	bool x = glfwGetMouseButton(window, button) == GLFW_RELEASE;
	return x;
}

std::pair<float, float> Input::GetMousePositionImpl()
{
	auto window = App::Get()->GetWindow()->GetNativeWindow();
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	return {(float)xpos, (float)ypos};
}

float Input::GetMouseXImpl()
{
	auto [x, y] = GetMousePositionImpl();
	return x;
}

float Input::GetMouseYImpl()
{
	auto [x, y] = GetMousePositionImpl();
	return y;
}

#include "trpch.h"
#include "Input.h"

Input* Input::s_instance = new Input;

bool Input::IskeyPressedImpl(int keyCode)
{
	auto window = static_cast<GLFWwindow*>(App::Get().GetWindow().GetNativeWindow());
	bool x = glfwGetKey(window, keyCode) == GLFW_PRESS;
	return x;
}

bool Input::OnkeyPressedImpl(int keyCode)
{
	auto window = static_cast<GLFWwindow*>(App::Get().GetWindow().GetNativeWindow());
	bool x;
	auto key = glfwGetKey(window, keyCode);
	if (lastState == (key == GLFW_RELEASE))
	{
		x = (key == GLFW_PRESS);
		lastState = x;
	}
	else
	{
		x = false;
	}
	return x;
}

bool Input::IskeyReleasedImpl(int keyCode)
{
	auto window = static_cast<GLFWwindow*>(App::Get().GetWindow().GetNativeWindow());
	bool x = glfwGetKey(window, keyCode) == GLFW_RELEASE;
	return x;
}

bool Input::OnkeyReleasedImpl(int keyCode)
{
	auto window = static_cast<GLFWwindow*>(App::Get().GetWindow().GetNativeWindow());
	bool x;
	auto key = glfwGetKey(window, keyCode);
	if (lastState == (key == GLFW_PRESS))
	{
		x = (key == GLFW_RELEASE);
		lastState = x;
	}
	else
	{
		x = false;
	}
	return x;
}

bool Input::OnScrollUpImpl()
{
	if (App::Get().GetWindow().GetScrollUp() == true)
	{
		App::Get().GetWindow().SetScrollUp(false);
		return true;
	}

	return false;
}

bool Input::OnScrollDownImpl()
{
	if (App::Get().GetWindow().GetScrollDown() == true)
	{
		App::Get().GetWindow().SetScrollDown(false);
		return true;
	}

	return false;
}

bool Input::IsMouseButtonPressedImpl(int button)
{
	auto window = static_cast<GLFWwindow*>(App::Get().GetWindow().GetNativeWindow());
	bool x = glfwGetMouseButton(window, button) == GLFW_PRESS;
	return x;
}

bool Input::IsMouseButtonReleasedImpl(int button)
{
	auto window = static_cast<GLFWwindow*>(App::Get().GetWindow().GetNativeWindow());
	bool x = glfwGetMouseButton(window, button) == GLFW_RELEASE;
	return x;
}

std::pair<float, float> Input::GetMousePositionImpl()
{
	auto window = static_cast<GLFWwindow*>(App::Get().GetWindow().GetNativeWindow());
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

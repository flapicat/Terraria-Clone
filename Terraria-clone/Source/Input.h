#pragma once
#include <utility>
#include "App.h"

class Input
{
public:
	inline static bool keyPressed(int keyCode) { return s_instance->keyPressedImpl(keyCode); };
	inline static bool keyReleased(int keyCode) { return s_instance->keyReleasedImpl(keyCode); };
	
	inline static bool IsMouseButtonPressed(int button) { return s_instance->IsMouseButtonPressedImpl(button); }
	inline static bool IsMouseButtonReleased(int button) { return s_instance->IsMouseButtonReleasedImpl(button); }

	inline static std::pair<float, float> GetMousePosition() { return s_instance->GetMousePositionImpl(); };
	inline static float GetMouseX() { return s_instance->GetMouseX(); };
	inline static float GetMouseY() { return s_instance->GetMouseY(); };
protected:
	bool keyPressedImpl(int keyCode);
	bool keyReleasedImpl(int keyCode);
	bool IsMouseButtonPressedImpl(int button);
	bool IsMouseButtonReleasedImpl(int button);
	std::pair<float, float> GetMousePositionImpl();
	float GetMouseXImpl();
	float GetMouseYImpl();
private:
	static Input* s_instance;
};

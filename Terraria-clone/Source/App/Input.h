#pragma once
#include "App.h"

class Input
{
public:
	inline static bool IskeyPressed(int keyCode) { return s_instance->IskeyPressedImpl(keyCode); }
	inline static bool OnkeyPressed(int keyCode) { return s_instance->OnkeyPressedImpl(keyCode); }
	inline static bool IskeyReleased(int keyCode) { return s_instance->IskeyReleasedImpl(keyCode); }
	inline static bool OnkeyReleased(int keyCode) { return s_instance->OnkeyReleasedImpl(keyCode); }

	inline static bool OnScrollUp()   { return s_instance->OnScrollUpImpl(); }
	inline static bool OnScrollDown() { return s_instance->OnScrollDownImpl(); }
	
	inline static bool IsMouseButtonPressed(int button) { return s_instance->IsMouseButtonPressedImpl(button); }
	inline static bool IsMouseButtonReleased(int button) { return s_instance->IsMouseButtonReleasedImpl(button); }

	inline static std::pair<float, float> GetMousePosition() { return s_instance->GetMousePositionImpl(); };
	inline static float GetMouseX() { return s_instance->GetMouseX(); };
	inline static float GetMouseY() { return s_instance->GetMouseY(); };
protected:
	bool IskeyPressedImpl(int keyCode);
	bool OnkeyPressedImpl(int keyCode);
	bool IskeyReleasedImpl(int keyCode);
	bool OnkeyReleasedImpl(int keyCode);

	bool OnScrollUpImpl();
	bool OnScrollDownImpl();

	bool IsMouseButtonPressedImpl(int button);
	bool IsMouseButtonReleasedImpl(int button);

	std::pair<float, float> GetMousePositionImpl();
	float GetMouseXImpl();
	float GetMouseYImpl();
private:
	static Input* s_instance;
	inline static bool lastState = 0;
};

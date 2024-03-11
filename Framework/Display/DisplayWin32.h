#pragma once

#include <wtypes.h>

class Game;

class DisplayWin32
{
public:
	DisplayWin32(LPCWSTR name);
	DisplayWin32(const DisplayWin32&) = delete;
	DisplayWin32& operator=(const DisplayWin32&) = delete;
	~DisplayWin32();

	void Create(UINT width, UINT height);
	HWND getHWnd();

private:
	HWND hWnd;

	LPCWSTR appName = L"DisplayWin32";
	HINSTANCE hInstance;
};


#pragma once

#include <wtypes.h>


class DisplayWin32
{
public:
	DisplayWin32(LPCWSTR name = L"Application",
				 int height		= 800,
			     int width		= 800);
	void CreateWin();

public:
	HINSTANCE hInstance;
	LPCWSTR applicationName;

	int clientHeight;
	int clientWidth;

	WNDCLASSEX wc;
	HWND hWnd;

private:
	void InitWC();
	void InitHWnd();
};


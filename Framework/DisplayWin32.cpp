#include "DisplayWin32.h"

#include <iostream>


DisplayWin32::WinClass DisplayWin32::WinClass::wndClass;

#pragma region DisplayWin32

DisplayWin32::DisplayWin32(UINT width, UINT height, LPCWSTR name)
{
	RECT windowRect = { 0, 0, static_cast<LONG>(width), static_cast<LONG>(height) };
	AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

	auto dwStyle = WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_THICKFRAME;

	auto posX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
	auto posY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;

	hWnd = CreateWindowEx(WS_EX_APPWINDOW,
		WinClass::GetName(), name,
		dwStyle,
		posX, posY,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		nullptr, nullptr, WinClass::GetInstance(), nullptr);

	if (hWnd == nullptr)
	{
		// Error
		std::cout << "DisplayWin32::DisplayWin32(...) hWnd create Error\n";
	}

	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);

	ShowCursor(true);
}

DisplayWin32::~DisplayWin32()
{
	DestroyWindow(hWnd);
}

HWND DisplayWin32::getHWnd()
{
	return hWnd;
}

LRESULT DisplayWin32::WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
	case WM_KEYDOWN:
	{
		// If a key is pressed send it to the input object so it can record that state.
		std::cout << "Key: " << static_cast<unsigned int>(wparam) << std::endl;

		if (static_cast<unsigned int>(wparam) == 27) PostQuitMessage(0);
		return 0;
	}
	default:
	{
		return DefWindowProc(hwnd, umessage, wparam, lparam);
	}
	}
}

#pragma endregion DisplayWin32


#pragma region WinClass

const LPCWSTR DisplayWin32::WinClass::GetName() noexcept
{
	return appName;
}

HINSTANCE DisplayWin32::WinClass::GetInstance() noexcept
{
	return wndClass.hInstance;
}

DisplayWin32::WinClass::WinClass() noexcept
	: hInstance(GetModuleHandle(nullptr))
{
	WNDCLASSEX wc = {};

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetInstance();
	wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = GetName();
	wc.hIconSm = wc.hIcon;

	// Register the window class.
	RegisterClassEx(&wc);
}

DisplayWin32::WinClass::~WinClass()
{
	UnregisterClass(appName, GetInstance());
}

#pragma endregion WinClass

#pragma once

#include <wtypes.h>


class DisplayWin32
{
public:
	DisplayWin32(UINT width, UINT height, LPCWSTR name);
	DisplayWin32(const DisplayWin32&) = delete;
	DisplayWin32& operator=(const DisplayWin32&) = delete;
	~DisplayWin32();

	HWND getHWnd();

private:
	class WinClass
	{
	public:
		static const LPCWSTR GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;

	private:
		WinClass() noexcept;
		~WinClass();
		WinClass(const WinClass&) = delete;
		WinClass& operator=(const WinClass&) = delete;


	private:
		static constexpr const LPCWSTR appName = L"WinClass";
		static WinClass wndClass;
		HINSTANCE hInstance;
	};

private:
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);

private:
	HWND hWnd;
};


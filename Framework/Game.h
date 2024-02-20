#pragma once

#include <windows.h>
#include <WinUser.h>
#include <wrl.h>
#include <iostream>
#include <d3d.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <chrono>
#include <vector>

#include "DisplayWin32.h"
//#include "GameComponent.h"
#include "TriangleComponent.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

class Game
{
public:
	Game();

	void Run();

protected:
	void Initialize();
	void Test();
private:
	void InitDisplay();
	DXGI_SWAP_CHAIN_DESC InitSwapDesc();
	void InitDeviceAndSwapChain();
	void InitBackBuffAndRTV();

	void CompileShaders();
	void CreateInputLayout();

	std::vector<GameComponent> v;
	ID3D11Texture2D* backTex;
	ID3D11RenderTargetView* rtv;
	ID3DBlob* vertexBC;
public:
	DisplayWin32* display;

	Microsoft::WRL::ComPtr<ID3D11Device> device;
	ID3D11DeviceContext* context;
	IDXGISwapChain* swapChain;

	HRESULT res;
};


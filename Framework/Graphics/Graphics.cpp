#include "Graphics.h"

#include <iostream>

Graphics::Graphics(int width, int height, HWND hWnd)
{
	D3D_FEATURE_LEVEL featureLevel[] = { D3D_FEATURE_LEVEL_11_1 };

	DXGI_SWAP_CHAIN_DESC swapDesc = {};
	swapDesc.BufferCount = 2;
	swapDesc.BufferDesc.Width = width;
	swapDesc.BufferDesc.Height = height;
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.OutputWindow = hWnd;
	swapDesc.Windowed = true;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;

	// Creating swapChain, device and context
	auto res = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG,
		featureLevel,
		1,
		D3D11_SDK_VERSION,
		&swapDesc,
		&swapChain,
		&device,
		nullptr,
		&context);

	if (FAILED(res))
	{
		std::cout << "Graphics::Graphics D3D11CreateDeviceAndSwapChain Error\n";
	}

	// Creating backBuffer
	Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuff;
	res = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &backBuff);
	if (FAILED(res))
	{
		std::cout << "Graphics::Graphics GetBuffer Error\n";
	}

	// Creating renderTargetView
	res = device->CreateRenderTargetView(backBuff.Get(), nullptr, &rtv);
	if (FAILED(res))
	{
		std::cout << "Graphics::Graphics CreateRenderTargetView Error\n";
	}

	// Creating rastState
	CD3D11_RASTERIZER_DESC rastDesc = {};
	rastDesc.CullMode = D3D11_CULL_NONE;
	rastDesc.FillMode = D3D11_FILL_SOLID;
	res = device->CreateRasterizerState(&rastDesc, &rastState);
	if (FAILED(res))
	{
		std::cout << "Graphics::Graphics CreateRasterizerState Error\n";
	}
}

ID3D11Device* Graphics::GetDevice()
{
	return device.Get();
}

ID3D11DeviceContext* Graphics::GetContext()
{
	return context.Get();
}

void Graphics::ClearBuffer(float red, float green, float blue) noexcept
{
	// Color background
	const float color[] = { red, green, blue, 1.0f };
	context->ClearRenderTargetView(rtv.Get(), color);
}

void Graphics::Draw(D3D_PRIMITIVE_TOPOLOGY topology)
{
	// Reset state
	context->ClearState();
	context->RSSetState(rastState.Get());

#pragma region Viewport

	D3D11_VIEWPORT viewport = {};
	viewport.Width = static_cast<float>(800);
	viewport.Height = static_cast<float>(800);
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1.0f;
	context->RSSetViewports(1, &viewport);

#pragma endregion Viewport

	context->OMSetRenderTargets(1, rtv.GetAddressOf(), nullptr);
	context->IASetPrimitiveTopology(topology);
}

void Graphics::EndFrame()
{
	context->OMSetRenderTargets(0, nullptr, nullptr);
	// Present final image
	swapChain->Present(1u, 0u);
}
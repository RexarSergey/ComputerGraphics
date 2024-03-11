#pragma once

#include <d3d11.h>
#include <wrl.h>

#pragma comment(lib, "d3d11.lib")

class Graphics
{
public:
	Graphics(int width, int height, HWND hWnd);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics() = default;

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetContext();

	void ClearBuffer(float red, float green, float blue) noexcept;
	void Draw(D3D_PRIMITIVE_TOPOLOGY topology);
	void EndFrame();

private:
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> rtv;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rastState;
};


#pragma once

#include "GameComponent.h"

#include <wrl.h>
#include <vector>
#include <directxmath.h>
#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")


class TriangleComponent :
    public GameComponent
{
public:
    TriangleComponent(Game* game,
        std::vector<DirectX::XMFLOAT4> points,
        std::vector<int>& indeces);


    void Draw();
;

private:
	//friend class Game;

	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;

	Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;

	Microsoft::WRL::ComPtr <ID3D11InputLayout> layout;

	std::vector<UINT> strides{ 32 };
	std::vector<UINT> offsets{ 0 };
};


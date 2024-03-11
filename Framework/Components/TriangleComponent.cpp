#include "TriangleComponent.h"


#include "../Game/Game.h"

TriangleComponent::TriangleComponent(Game* inGame,
	std::vector<DirectX::XMFLOAT4>& inPoints,
	std::vector<int>& inIndeces)
	: GameComponent(inGame), points(inPoints), indeces(inIndeces), indexCount(inIndeces.size())
{
}

void TriangleComponent::Initialize()
{
	#pragma region Vertex Buffer
	
		D3D11_BUFFER_DESC vertexBufDesc = {};
		vertexBufDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufDesc.CPUAccessFlags = 0;
		vertexBufDesc.MiscFlags = 0;
		vertexBufDesc.StructureByteStride = 0;
		vertexBufDesc.ByteWidth = sizeof(DirectX::XMFLOAT4) * std::size(points);
	
		D3D11_SUBRESOURCE_DATA vertexData = {};
		vertexData.pSysMem = &points[0];
		vertexData.SysMemPitch = 0;
		vertexData.SysMemSlicePitch = 0;
	
		game->GetGfx()->GetDevice()->CreateBuffer(&vertexBufDesc, &vertexData, &vertexBuffer);
	
	#pragma endregion Vertex Buffer
	
	#pragma region Vertex Shader
	
		ID3DBlob* vertexBC = nullptr;
		ID3DBlob* errorVertexCode = nullptr;
		HRESULT res = D3DCompileFromFile(L"./Shaders/MyVeryFirstShader.hlsl",
			nullptr /*macros*/,
			nullptr /*include*/,
			"VSMain",
			"vs_5_0",
			D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION | D3DCOMPILE_PACK_MATRIX_ROW_MAJOR,
			0,
			&vertexBC,
			&errorVertexCode);
	
		game->GetGfx()->GetDevice()->CreateVertexShader(
			vertexBC->GetBufferPointer(),
			vertexBC->GetBufferSize(),
			nullptr, &vertexShader);
	
	#pragma endregion Vertex Shader
	
	#pragma region Index Buffer
	
		D3D11_BUFFER_DESC indexBufDesc = {};
		indexBufDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufDesc.CPUAccessFlags = 0;
		indexBufDesc.MiscFlags = 0;
		indexBufDesc.StructureByteStride = 0;
		indexBufDesc.ByteWidth = sizeof(int) * std::size(indeces);
	
		D3D11_SUBRESOURCE_DATA indexData = {};
		indexData.pSysMem = &indeces[0];
		indexData.SysMemPitch = 0;
		indexData.SysMemSlicePitch = 0;
	
		game->GetGfx()->GetDevice()->CreateBuffer(&indexBufDesc, &indexData, &indexBuffer);
	
	#pragma endregion Index Buffer
	
	#pragma region Pixel Shader
	
		/*D3D_SHADER_MACRO Shader_Macros[] = { "TEST",
			"1",
			"TCOLOR",
			"float4(0.0f, 1.0f, 0.0f, 1.0f)",
			nullptr, nullptr };*/
	
		ID3DBlob* pixelBC;
		ID3DBlob* errorPixelCode;
		res = D3DCompileFromFile(L"./Shaders/MyVeryFirstShader.hlsl",
			nullptr /*macros*/,
			nullptr /*include*/,
			"PSMain",
			"ps_5_0",
			D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
			0,
			&pixelBC,
			&errorPixelCode);
	
		game->GetGfx()->GetDevice()->CreatePixelShader(
			pixelBC->GetBufferPointer(),
			pixelBC->GetBufferSize(),
			nullptr, &pixelShader);
	
	#pragma endregion Pixel Shader
	
	#pragma region Layout
	
		D3D11_INPUT_ELEMENT_DESC inputElements[] = {
			D3D11_INPUT_ELEMENT_DESC {
				"POSITION",
				0,
				DXGI_FORMAT_R32G32B32A32_FLOAT,
				0,
				0,
				D3D11_INPUT_PER_VERTEX_DATA,
				0},
			D3D11_INPUT_ELEMENT_DESC {
				"COLOR",
				0,
				DXGI_FORMAT_R32G32B32A32_FLOAT,
				0,
				D3D11_APPEND_ALIGNED_ELEMENT,
				D3D11_INPUT_PER_VERTEX_DATA,
				0}
		};
	
		game->GetGfx()->GetDevice()->CreateInputLayout(
			inputElements,
			2,
			vertexBC->GetBufferPointer(),
			vertexBC->GetBufferSize(),
			&layout);
	
	#pragma endregion Layout
}

void TriangleComponent::Draw()
{
	game->GetGfx()->GetContext()->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &strides[0], &offsets[0]);
	game->GetGfx()->GetContext()->VSSetShader(vertexShader.Get(), nullptr, 0);

	game->GetGfx()->GetContext()->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	game->GetGfx()->GetContext()->PSSetShader(pixelShader.Get(), nullptr, 0);

	game->GetGfx()->GetContext()->IASetInputLayout(layout.Get());

	game->GetGfx()->GetContext()->DrawIndexed(indexCount, 0, 0);
}

#include "PP_GameMode.h"

#include <memory>
#include "../../Framework/Components/TriangleComponent.h"

void PP_GameMode::Initialize()
{
	// Initialize game params
	width = 200;
	height = 200;
	applicationName = L"Game Application";


	// Triangle settings
	std::vector<DirectX::XMFLOAT4> points = {
			DirectX::XMFLOAT4(0.7f, 0.7f, 0.5f, 1.0f),	DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f),
			DirectX::XMFLOAT4(-0.3f, -0.3f, 0.5f, 1.0f),	DirectX::XMFLOAT4(0.5f, 0.0f, 0.0f, 1.0f),
			DirectX::XMFLOAT4(0.7f, -0.3f, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),
	};

	std::vector<DirectX::XMFLOAT4> points1 = {
		DirectX::XMFLOAT4(0.3f, 0.3f, 0.5f, 1.0f),	DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f),
		DirectX::XMFLOAT4(-0.7f, 0.3f, 0.5f, 1.0f),	DirectX::XMFLOAT4(0.0f, 0.0f, 0.5f, 1.0f),
		DirectX::XMFLOAT4(-0.7f, -0.7f, 0.5f, 1.0f),	DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f),
	};

	std::vector<int> indeces = { 0, 1, 2 };


	// Add triangle components
	components.push_back(std::make_unique<TriangleComponent>(this, points, indeces));
	components.push_back(std::make_unique<TriangleComponent>(this, points1, indeces));
}

void PP_GameMode::Run()
{
	Initialize();
	Game::Run();
}

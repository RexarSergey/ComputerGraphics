#include "Game.h"
#include "../Components/TriangleComponent.h"
#include "../InputDevice/InputDevice.h"



Game::Game()
{
	Initialize();

	display = std::make_unique<DisplayWin32>(applicationName);
	display->Create(width, height);

	inputDevice = new InputDevice(this);
	gfx = std::make_unique<Graphics>(width, height, display.get()->getHWnd());



	for (auto& component : components)
	{
		component->Initialize();
	}
}

DisplayWin32* Game::GetDisplay()
{
	return display.get();
}

Graphics* Game::GetGfx()
{
	return gfx.get();
}

Game::~Game()
{
	delete (inputDevice);
}

void Game::Initialize()
{
	// Initialize game params
	width = 800;
	height = 800;
	applicationName = L"Game Application";


	// Triangle settings
	std::vector<DirectX::XMFLOAT4> points = {
			DirectX::XMFLOAT4(0.7f, 0.7f, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),
			DirectX::XMFLOAT4(-0.3f, -0.3f, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),
			DirectX::XMFLOAT4(0.7f, -0.3f, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),
	};

	std::vector<DirectX::XMFLOAT4> points1 = {
		DirectX::XMFLOAT4(0.3f, 0.3f, 0.5f, 1.0f),	DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f),
		DirectX::XMFLOAT4(-0.7f, 0.3f, 0.5f, 1.0f),	DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f),
		DirectX::XMFLOAT4(-0.7f, -0.7f, 0.5f, 1.0f),	DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f),
	};

	std::vector<int> indeces = { 0, 1, 2 };


	// Add triangle components
	components.push_back(std::make_unique<TriangleComponent>(this, points, indeces));
	components.push_back(std::make_unique<TriangleComponent>(this, points1, indeces));
}

void Game::Update()
{
	auto curTime = std::chrono::steady_clock::now();
	float deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(curTime - prevTime).count() / 1000000.0f;
	prevTime = curTime;

	totalTime += deltaTime;
	frameCount++;

	if (totalTime > 1.0f) {
		float fps = frameCount / totalTime;

		totalTime -= 1.0f;

		WCHAR text[256];
		swprintf_s(text, TEXT("FPS: %f"), fps);
		SetWindowText(display->getHWnd(), text);

		frameCount = 0;
	}

	gfx->ClearBuffer(0.1f, 0.1f, 0.1f);
	gfx->Draw(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	for (auto& component : components)
	{
		component->Draw();
	}

	gfx->EndFrame();
}

void Game::Run()
{
	MSG msg = {};
	bool isExitRequested = false;

	prevTime = std::chrono::steady_clock::now();
	totalTime = 0;
	frameCount = 0;
	while (!isExitRequested)
	{
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (static_cast<unsigned int>(msg.wParam) == 27) {
			isExitRequested = true;
			break;
		}

		Update();
	}
}

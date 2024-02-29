#include "Game.h"



Game::Game()
{
	display = std::make_unique<DisplayWin32>(800, 800, L"Game Application");
	gfx = std::make_unique<Graphics>(800, 800, display.get()->getHWnd());
}

Graphics* Game::GetGfx()
{
	return gfx.get();
}

void Game::AddTriangle(std::vector<DirectX::XMFLOAT4>& points, std::vector<int>& indeces)
{
	components.push_back({this, points, indeces});
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

		if (msg.message == WM_QUIT) {
			isExitRequested = true;
			break;
		}

		DoFrame();
	}
}

void Game::DoFrame()
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

	gfx->ClearBuffer(totalTime, 0.1f, 0.1f);
	gfx->Draw(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	for (auto& component : components)
	{
		component.Draw();
	}

	gfx->EndFrame();

}

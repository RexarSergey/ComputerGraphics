#pragma once

#include <wrl.h>
#include <d3d11.h>
#include <vector>
#include <chrono>
#include <memory>
#include <directxmath.h>


#pragma comment(lib, "d3d11.lib")

#include "DisplayWin32.h"
#include "TriangleComponent.h"
#include "Graphics.h"

class Game
{
public:
	Game();
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	~Game() = default;

	Graphics* GetGfx();

	void AddTriangle(std::vector<DirectX::XMFLOAT4>& points, std::vector<int>& indeces);
	void Run();

private:
	void DoFrame();

private:
	std::unique_ptr<DisplayWin32> display;
	std::unique_ptr<Graphics> gfx;

	std::chrono::time_point<std::chrono::steady_clock> prevTime;
	float totalTime;
	unsigned int frameCount;

	std::vector<TriangleComponent> components;
};


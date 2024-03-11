#pragma once

#include <wrl.h>
#include <d3d11.h>
#include <vector>
#include <chrono>
#include <memory>
#include <directxmath.h>


#pragma comment(lib, "d3d11.lib")

#include "../Display/DisplayWin32.h"
#include "../Graphics/Graphics.h"
#include "../Components/GameComponent.h"

class Game
{
public:
	Game();
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	~Game();

	void Initialize();
	void Update();
	void Run();

	DisplayWin32* GetDisplay();
	Graphics* GetGfx();

protected:
	UINT width = 200;
	UINT height = 200;
	LPCWSTR applicationName = L"None";

	std::unique_ptr<DisplayWin32> display;
	std::unique_ptr<Graphics> gfx;

	std::vector< std::unique_ptr<GameComponent> > components;

	std::chrono::time_point<std::chrono::steady_clock> prevTime;
	float totalTime;
	unsigned int frameCount;
};


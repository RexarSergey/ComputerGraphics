#pragma once

#include "Game.h"

class GameComponent
{
public:
	GameComponent();

	/*virtual void Initialize() = 0;
	virtual void DestroyResources() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;*/

	Game* game;
};


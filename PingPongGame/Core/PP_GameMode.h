#pragma once

#include "../../Framework/Game/Game.h"

class PP_GameMode :
	public Game
{
public:
	void Initialize() override;
	void Run() override;
};


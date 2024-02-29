#pragma once


class Game;

class GameComponent
{
public:
	GameComponent(Game* inGame);

	virtual void Draw() = 0;

protected:
	Game* game;
};
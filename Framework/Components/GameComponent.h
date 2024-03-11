#pragma once


class Game;

class GameComponent
{
public:
	GameComponent(Game* inGame);

	virtual void Initialize();
	virtual void Draw();

protected:
	Game* game;
};
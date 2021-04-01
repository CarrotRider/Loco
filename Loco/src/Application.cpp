#include "stdafx.h"

#include "Game.h"

using namespace Loco;

int main(void)
{
	Game* game = new Game();
	bool success = game->Initialize();
	if (success)
	{
		game->Loop();
	}
	game->ShutDown();
	delete game;
	return 0;
}
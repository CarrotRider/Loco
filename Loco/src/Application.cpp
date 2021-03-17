#include "stdafx.h"

#include "Game.h"

using namespace Loco;

int main(void)
{
	Game* game = Game::GetInstance();
	bool success = game->Initialize();
	if (success)
	{
		game->Loop();
	}
	game->ShutDown();
	return 0;
}
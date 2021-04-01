#pragma once

#ifdef LOCO_PLATFORM_WINDOWS

extern Loco::Game* Loco::CreateGame();

int main(int argc, char** argv)
{
	Loco::Game* game = Loco::CreateGame();
	bool success = game->Initialize();
	if (success)
	{
		game->Loop();
	}
	game->ShutDown();
	delete game;
	return 0;
}

#endif // LOCO_PLATFORM_WINDOWS

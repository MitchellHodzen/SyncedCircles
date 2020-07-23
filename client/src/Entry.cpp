#include <iostream>
#include "Game.h"
int main(int argc, char *argv[])
{
	Game game;
	if (game.SetUp(800, 600))//224x288
	{
		game.Run();
	}
	return 0;
}
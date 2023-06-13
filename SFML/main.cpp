#include <iostream>
#include "Game.h"

//using namespace sf;

int main()
{
	std::srand(static_cast<unsigned>(time(NULL)));
	//Window
	Game game;
	//Game loop
	while (game.running() && !game.getEndGame())
	{
		game.update();
		game.render();
	}
	//End of application
	return 0;
}


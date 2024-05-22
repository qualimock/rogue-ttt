#include "Game/Game.hpp"

int main()
{
	{
		Game g_game(sf::VideoMode(720, 480));
		const sf::RenderWindow *window = g_game.window();

		g_game.init();

		while (window->isOpen())
		{
			g_game.update();

			g_game.render();
		}
	}

	return EXIT_SUCCESS;
}

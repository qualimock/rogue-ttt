#include "Game/Game.hpp"

#include "Resources/ResourceManager.hpp"

int main(int argc, char **argv)
{
	{
		ResourceManager::set_executable_path(argv[0]);

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

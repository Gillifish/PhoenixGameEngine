#include "Game.h"

void Game::run()
{
    sf::Window window(sf::VideoMode(800, 600), "My Game");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
}
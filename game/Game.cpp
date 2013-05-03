#include "Game.h"

#include <iostream>
Game::Game()
{
    _window = new sf::RenderWindow(sf::VideoMode(640,640), "Pixel Garden");
}

Game::~Game()
{
    delete _window;
}


void Game::run()
{
    sf::Clock clock;

    while(_window->isOpen())
    {
        sf::Time delta = clock.getElapsedTime();
        sf::Event event;
        while(_window->pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                _window->close();
            }
        }
        update(delta);
        draw(delta);
    }
}

bool Game::update(sf::Time delta)
{
}

void Game::draw(sf::Time delta)
{
    _window->clear(sf::Color::Black);
    _window->display();
}

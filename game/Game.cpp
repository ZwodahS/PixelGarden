#include "Game.h"
#include "garden/Garden.h"
#include <iostream>
Game::Game()
{
    _window = new sf::RenderWindow(sf::VideoMode(640,640), "Pixel Garden");
    initAssets();
    _garden = new Garden(this);
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
    _window->clear(sf::Color(20,20,20,255));
    _garden->draw(_window,delta);
    _window->display();
}

void Game::initAssets()
{
    _assets.pixel.spriteSheet = SpriteSheet(sf::IntRect(0,0,32,32),5,5);
    sf::Image image;
    image.loadFromFile("assets/img/pixels/pixeltexture.png");
    _assets.pixel.pixelTexture = _assets.pixel.spriteSheet.createRegion(image);

}

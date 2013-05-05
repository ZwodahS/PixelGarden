#include "Game.hpp"
#include "garden/Garden.hpp"
#include "consts.hpp"


#include "../zf_sfml/Mouse.hpp"
#include "../zf_sfml/TextureRegion.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>


Game::Game()
{
    _window = new sf::RenderWindow(sf::VideoMode(displayconsts::DISPLAY_WIDTH,displayconsts::DISPLAY_HEIGHT), "Pixel Garden");
    initAssets();
}

Game::~Game()
{
    delete _window;
}


void Game::run()
{
    sf::Clock clock;
    zf::Mouse mouse;
    GameScreen gs = GameScreen(this,&mouse);
    gs.initNewGame();
    _currentScreen = &gs; 
    bool quit = false;
    while(_window->isOpen())
    {
        sf::Time delta = clock.restart();
        mouse.update(delta);
        sf::Event event;
        while(_window->pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                _window->close();
                quit = true;
            }
        }
        if(!quit)
        {
            update(delta);
            draw(delta);
        }
    }
    _currentScreen = NULL;
}

bool Game::update(sf::Time delta)
{
}

void Game::draw(sf::Time delta)
{
    _window->clear(sf::Color(20,20,20,255));
    if(_currentScreen != 0)
    {
        _currentScreen->draw(_window,delta);   
    }
    _window->display();
}


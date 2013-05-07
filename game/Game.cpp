#include "Game.hpp"
#include "garden/Garden.hpp"
#include "consts.hpp"

#include "../zf_sfml/Mouse.hpp"
#include "../zf_sfml/TextureRegion.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <algorithm>

#define COLOR_MIN 100
#define COLOR_LEFT 155

Game::Game()
{
    _window = new sf::RenderWindow(sf::VideoMode(displayconsts::DISPLAY_WIDTH,displayconsts::DISPLAY_HEIGHT), "Pixel Garden");
    initAssets();
    this->_mouse = new zf::Mouse();
    this->_keyInput   = new InputControl();
    _pgsSequence = std::vector<int>(58);
    for(int i = 0 ; i < _pgsSequence.size() ; i++)
    {
        _pgsSequence[i] = i;
    }
    _pgsColor = std::vector<TextureRegion*>(0);
    for(int i = 0 ; i < _pgsSequence.size() ; i++)
    {
        _pgsColor.push_back(0);
    }
    for(int i = 0 ; i < _pgsSequence.size() ; i++)
    {
        int r = i  % 7 ;
        switch(r)
        {
            case 0:
                _pgsColor[_pgsSequence[i]]=&_assets.pixel.pgs.red;
                break;
            case 1:
                _pgsColor[_pgsSequence[i]]=&_assets.pixel.pgs.blue;
                break;
            case 2:
                _pgsColor[_pgsSequence[i]]=&_assets.pixel.pgs.green;
                break;
            case 3:
                _pgsColor[_pgsSequence[i]]=&_assets.pixel.pgs.orange;
                break;
            case 4:
                _pgsColor[_pgsSequence[i]]=&_assets.pixel.pgs.purple;
                break;
            case 5:
                _pgsColor[_pgsSequence[i]]=&_assets.pixel.pgs.yellow;
                break;
            case 6:
                _pgsColor[_pgsSequence[i]]=&_assets.pixel.pgs.cyan;
                break;
            default : // just in case ?
                _pgsColor[i]=&_assets.pixel.pgs.gray;
        }
    }
    random_shuffle(_pgsSequence.begin(),_pgsSequence.end());
}

Game::~Game()
{
    delete _window;
    delete _mouse;
    delete _keyInput;
}


void Game::run()
{
    sf::Clock clock;
    GameScreen gs = GameScreen(this);
    gs.initNewGame();
    _currentScreen = &gs; 
    bool quit = false;

    while(_window->isOpen())
    {
        sf::Time delta = clock.restart();
        _mouse->update(delta);
        _keyInput->update(delta);
        sf::Event event;
        while(_window->pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                _window->close();
                quit = true;
            }
            else if(event.type == sf::Event::MouseWheelMoved)
            {
                _mouse->_wheelDelta = event.mouseWheel.delta;
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
    if(_currentScreen != 0)
    {
        _currentScreen->update(_window, delta);
    }
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

sf::Sprite Game::createSprite(GrowthSegment gs)
{
    if(gs == GROW_SOURCE_NORTH)
    {
        return _assets.pixel.segments.sourceNorth.createSprite();
    }
    else if(gs == GROW_SOURCE_SOUTH)
    {
        return _assets.pixel.segments.sourceSouth.createSprite();
    }
    else if(gs == GROW_SOURCE_EAST)
    {
        return _assets.pixel.segments.sourceEast.createSprite();
    }
    else if(gs == GROW_SOURCE_WEST)
    {
        return _assets.pixel.segments.sourceWest.createSprite();
    }
    else if(gs == GROW_LAST_NORTH)
    {
        return _assets.pixel.segments.lastNorth.createSprite();
    }
    else if(gs == GROW_LAST_SOUTH)
    {
        return _assets.pixel.segments.lastSouth.createSprite();
    }
    else if(gs == GROW_LAST_EAST)
    {
        return _assets.pixel.segments.lastEast.createSprite();
    }
    else if(gs == GROW_LAST_WEST)
    {
        return _assets.pixel.segments.lastWest.createSprite();
    }
    else 
    {
        // shouldn't happen but just put it here.
        return _assets.pixel.segments.sourceNorth.createSprite();
    }
}

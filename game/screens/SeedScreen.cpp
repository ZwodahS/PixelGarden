#include "SeedScreen.hpp"
#include "../Game.hpp"
#include "../consts.hpp"
#include <iostream>

#define MAX_COL 8


SeedScreen::SeedScreen(Game* game,GameData* data)
    :Screen(game)
{
    this->_data = data;
    _drawSeeds = std::vector<SeedSlot*>(0);
    // for each seed in the game, create a sprite for it.
    int i = 0;
    int r = 0;
    int c = 0;
    for(std::vector<Seed*>::iterator it = data->seedManager->getIterator() ; it != data->seedManager->end() ;it++)
    {
        SeedSlot* slot = new SeedSlot(_game,*it,_data->seedManager->getCount(*it));
        slot->_position = sf::Vector2i(c*64,r*64);
        i++;
        c++;
        if(c == MAX_COL)
        {
            r++;
            c=0;
        }
        slot->updateValues();
        _drawSeeds.push_back(slot);
    }
    _view = sf::View(sf::FloatRect(0,0,0.8f*displayconsts::DISPLAY_WIDTH, 0.8f * displayconsts::DISPLAY_HEIGHT));
    _view.setViewport(sf::FloatRect(0.1f,0.1f,0.8f,0.8f));
}

SeedScreen::~SeedScreen()
{
    for(int i = 0 ; i < _drawSeeds.size() ; i++)
    {
        delete _drawSeeds[i];
    }
}

void SeedScreen::draw(sf::RenderWindow* window, sf::Time delta)
{
    const sf::View currentView = window->getView();
    window->setView(_view);
    sf::Vector2i pixelPos = _game->_mouse->getPosition(*window);
    sf::Vector2f position = window->mapPixelToCoords(pixelPos);
    for(int i = 0 ; i < _drawSeeds.size() ; i++)
    {
        if(_drawSeeds[i]->contains(position))
        {
            _drawSeeds[i]->draw(window,delta,true);
        }
        else
        {
            _drawSeeds[i]->draw(window,delta);
        }
    }
    window->setView(currentView);
}

void SeedScreen::update(sf::RenderWindow* window, sf::Time delta)
{
    const sf::View currentView = window->getView();
    if(_game->_mouse->_wheelDelta != 0)
    {
        moveView(_game->_mouse->_wheelDelta);
    }
    window->setView(_view);
    if(_game->_mouse->_left.thisReleased) // if the left mouse is released.
    {
        // set the selected seed to be the seed. perhaps hide the screen ?
        Seed* seed = 0;
        sf::Vector2i pixelCoor = _game->_mouse->getPosition(*window);
        sf::Vector2f mousePos = window->mapPixelToCoords(pixelCoor);
        for(int i = 0 ; i < _drawSeeds.size() ; i++)
        {
            if(_drawSeeds[i]->contains(mousePos))
            {
                seed = _drawSeeds[i]->_seed;
                break;
            }
        }
        if(seed!=0)
        {
            _data->selectedSeed = seed;
        }
    }
    window->setView(currentView);
}

void SeedScreen::moveView(int mouseDelta)
{
    _view.move(0,_game->_mouse->_wheelDelta*1.0f/2);
}

SeedSlot::SeedSlot(Game* game, Seed* seed, int count)
{
    this->_game = game;
    this->_seed = seed;
    this->_count = count;
    this->_position = sf::Vector2i(0,0);
    this->_iconSprite = _game->_assets.pixel.seed.createSprite();
    this->_countText = sf::Text(" ",_game->_assets.fonts.upheav,20);
    this->_containBound = sf::Rect<float>(0,0,48,48);
    this->_border = _game->_assets.pixel.seedSlot.createSprite();
}

SeedSlot::~SeedSlot()
{
}

void SeedSlot::updateValues()
{
    _containBound.left = _position.x + 8;
    _containBound.top = _position.y + 8;
    _border.setPosition(_position.x+8,_position.y+8);
    _iconSprite.setPosition(_position.x+8,_position.y+8);
    _countText.setPosition(_position.x+40,_position.y+32);
    _countText.setString(zf::toString(_count));
    if(_count > 0)
    {
        _countText.setColor(sf::Color::Green);
    }
    else
    {
        _countText.setColor(sf::Color::Red);
    }
    PixelColor color = _seed->_color;
    color.normalizeTo(255);
    _iconSprite.setColor(sf::Color(color.r,color.g,color.b));
}
void SeedSlot::draw(sf::RenderWindow* window, sf::Time delta, bool selected)
{
    if(selected)
    {
        _border.setColor(sf::Color::Yellow);
    }
    else
    {
        _border.setColor(sf::Color::White);
    }
    window->draw(_border);
    window->draw(_iconSprite);
    window->draw(_countText);   
}

bool SeedSlot::contains(sf::Vector2f position)
{
    return _containBound.contains(position);    
}


#include "SeedScreen.hpp"
#include "../Game.hpp"
#include <iostream>

SeedScreen::SeedScreen(Game* game,GameData* data)
    :Screen(game)
{
    this->_data = data;
    _drawSeeds = std::vector<SeedSlot*>(0);
    // for each seed in the game, create a sprite for it.
    int i = 0;
    for(std::vector<Seed*>::iterator it = data->seedManager->getIterator() ; it != data->seedManager->end() ;it++)
    {
        SeedSlot* slot = new SeedSlot(_game,*it,_data->seedManager->getCount(*it));
        slot->_position = sf::Vector2i(i*64,0);
        i++;
        slot->updateValues();
        _drawSeeds.push_back(slot);
    }
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
}

void SeedScreen::update(sf::RenderWindow* window, sf::Time delta)
{
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
}

SeedSlot::SeedSlot(Game* game, Seed* seed, int count)
{
    this->_game = game;
    this->_seed = seed;
    this->_count = count;
    this->_position = sf::Vector2i(0,0);
    this->_iconSprite = _game->_assets.pixel.pixelTexture.createSprite();
    this->_countText = sf::Text(" ",_game->_assets.fonts.upheav,20);
    this->_containBound = sf::Rect<float>(0,0,48,48);
    this->_border = sf::RectangleShape(sf::Vector2f(48,48));
}

SeedSlot::~SeedSlot()
{
}

void SeedSlot::updateValues()
{
    _containBound.left = _position.x + 8;
    _containBound.top = _position.y + 8;
    _border.setPosition(_position.x+8,_position.y+8);
    _iconSprite.setPosition(_position.x+16,_position.y+16);
    _countText.setPosition(_position.x+32,_position.y+32);
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
        _border.setFillColor(sf::Color::Yellow);
    }
    else
    {
        _border.setFillColor(sf::Color::White);
    }
    window->draw(_border);
    window->draw(_iconSprite);
    window->draw(_countText);   
}

bool SeedSlot::contains(sf::Vector2f position)
{
    return _containBound.contains(position);    
}

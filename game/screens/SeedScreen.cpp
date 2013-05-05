#include "SeedScreen.hpp"
#include "../Game.hpp"
#include <iostream>

SeedScreen::SeedScreen(Game* game,GameData* data)
    :Screen(game)
{
    this->_data = data;
    _drawSeeds = std::vector<SeedSlot*>(0);
    // for each seed in the game, create a sprite for it.
    for(std::vector<Seed*>::iterator it = data->seedManager->getIterator() ; it != data->seedManager->end() ;it++)
    {
        _drawSeeds.push_back(new SeedSlot(_game,*it,_data->seedManager->getCount(*it)));
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
    for(int i = 0 ; i < _drawSeeds.size() ; i++)
    {
        _drawSeeds[i]->draw(window,delta);
    }
}

void SeedScreen::update(sf::Time delta)
{

}

SeedSlot::SeedSlot(Game* game, Seed* seed, int count)
{
    this->_game = game;
    this->_seed = seed;
    this->_count = count;
    this->_position = sf::Vector2i(0,0);
    this->_iconSprite = _game->_assets.pixel.pixelTexture.createSprite();
    this->_countText.setFont(_game->_assets.fonts.upheav);
    this->_countText.setCharacterSize(16);
}

SeedSlot::~SeedSlot()
{
}

void SeedSlot::updateValues()
{
    _iconSprite.setPosition(_position.x,_position.y);
    _countText.setPosition(_position.x+16,_position.y+16);
    _iconSprite.setColor(sf::Color(_seed->_color.r,_seed->_color.g,_seed->_color.b));
}
void SeedSlot::draw(sf::RenderWindow* window, sf::Time delta)
{
    window->draw(_iconSprite);
    window->draw(_countText);   
}

#include "GardenSelector.hpp"

GardenSelector::GardenSelector(Game* game,int width, int height, int maxOffset, int minOffset, float movementPerSec = 2)
{
    this->_width = width;
    this->_height = height;
    this->_maxOffset = maxOffset;
    this->_minOffset = minOffset;
    this->_offset = 0;
    this->_multiplier = 1;
    this->_movement = movementPerSec;
    
    this->topLeft = game->_assets.pixel.NW.createSprite();
    this->topRight = game->_assets.pixel.NE.createSprite();
    this->bottomLeft = game->_assets.pixel.SW.createSprite();
    this->bottomRight = game->_assets.pixel.SE.createSprite();

}

void GardenSelector::draw(sf::RenderWindow* window, sf::Time delta, int x, int y)
{
    _offset += _multiplier * (delta.asSeconds() * _movement);
    if(_multiplier == -1 && _offset <= _minOffset )
    {
        _multiplier = 1;
    }
    else if(_multiplier == 1 && _offset >= _maxOffset)
    {
        _multiplier = -1;
    }
    topLeft.setPosition(x-_offset, y-_offset);
    topRight.setPosition(x+_offset+_width-5,y-_offset);
    bottomLeft.setPosition(x-_offset,y+_offset+_height-5);
    bottomRight.setPosition(x+_offset+_width-5,y+_offset+_height-5);
    window->draw(topLeft);
    window->draw(topRight);
    window->draw(bottomLeft);
    window->draw(bottomRight);
}

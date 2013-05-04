#ifndef _GAME_GARDEN_SELECTOR_H_
#define _GAME_GARDEN_SELECTOR_H_

#include "../../zf_common/Grid.hpp"
#include "../Game.hpp"
#include <SFML/Graphics.hpp>
class GardenSelector
{
    public:
        GardenSelector(Game* game,int width, int height,int maxOffset,int minOffset,float movementPerSecs);
        // x y is the top left position of the rectangle to enclose.
        void draw(sf::RenderWindow* window,sf::Time delta,int x , int y);
    
    private:
        int _width;
        int _height;
        int _maxOffset;
        int _minOffset;
        float _offset;
        float _movement;

        int _multiplier;
        

        sf::Sprite topLeft;
        sf::Sprite topRight;
        sf::Sprite bottomLeft;
        sf::Sprite bottomRight;
};
#endif

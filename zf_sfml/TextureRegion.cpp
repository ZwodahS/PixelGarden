#include "TextureRegion.h"
#include <iostream>
sf::Sprite TextureRegion::createSprite()
{
    sf::Sprite sprite = sf::Sprite(*texture, srcClip);
    return sprite;
}

#ifndef _GAME_ASSETS_H_
#define _GAME_ASSETS_H_
#include "../zf_sfml/SpriteSheet.hpp"


struct PixelAssets
{
    SpriteSheet spriteSheet;
    TextureRegion pixelTexture;
    TextureRegion NE;
    TextureRegion NW;
    TextureRegion SE;
    TextureRegion SW;
};

struct FontAssets
{
    sf::Font upheav;
};

struct Assets
{
    PixelAssets pixel;
    FontAssets fonts;
};
#endif

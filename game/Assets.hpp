#ifndef _GAME_ASSETS_H_
#define _GAME_ASSETS_H_
#include "../zf_sfml/SpriteSheet.hpp"

struct SegmentAssets
{
    TextureRegion sourceNorth;
    TextureRegion sourceSouth;
    TextureRegion sourceEast;
    TextureRegion sourceWest;
    TextureRegion lastNorth;
    TextureRegion lastSouth;
    TextureRegion lastEast;
    TextureRegion lastWest;
};

struct PixelAssets
{
    SpriteSheet spriteSheet;
    TextureRegion pixelTexture;
    TextureRegion NE;
    TextureRegion NW;
    TextureRegion SE;
    TextureRegion SW;
    TextureRegion seed;
    TextureRegion seedSlot;
    
    SegmentAssets segments;
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

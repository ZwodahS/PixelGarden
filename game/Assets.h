#ifndef _GAME_ASSETS_H_
#define _GAME_ASSETS_H_
#include "../zf_sfml/SpriteSheet.h"


struct PixelAssets
{
    SpriteSheet spriteSheet;
    TextureRegion pixelTexture;
};

struct Assets
{
    PixelAssets pixel;
};
#endif

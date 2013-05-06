#include "Game.hpp"
void Game::initAssets()
{
    // let the sprite sheet be 64 by 64.
    _assets.pixel.spriteSheet = SpriteSheet(sf::IntRect(0,0,64,64),5,5);

    sf::Image group; // to store the 64by64 sprite
    sf::Image image; // any sub image to put into it.
    

    // some 32x32 textures
    group.create(64,64,sf::Color(0,0,0,0));
    image.loadFromFile("assets/img/pixels/pixeltexture.png");
    group.copy(image,0,0,sf::IntRect(0,0,0,0),true);
    image.loadFromFile("assets/img/pixels/seed.png");
    group.copy(image,32,0,sf::IntRect(0,0,0,0),true);

    TextureRegion region = _assets.pixel.spriteSheet.createRegion(group);
    sf::IntRect srcClip = region.srcClip;

    _assets.pixel.pixelTexture = TextureRegion(region.texture,sf::IntRect(srcClip.left,srcClip.top,32,32));
    _assets.pixel.seed = TextureRegion(region.texture,sf::IntRect(srcClip.left+32,srcClip.top,32,32));

    // some very small textures
    group.create(64,64,sf::Color(0,0,0,0));
    image.loadFromFile("assets/img/selection/NW.png");
    group.copy(image,0,0,sf::IntRect(0,0,0,0),true);
    image.loadFromFile("assets/img/selection/NE.png");
    group.copy(image,5,0,sf::IntRect(0,0,0,0),true);
    image.loadFromFile("assets/img/selection/SW.png");
    group.copy(image,0,5,sf::IntRect(0,0,0,0),true);
    image.loadFromFile("assets/img/selection/SE.png");
    group.copy(image,5,5,sf::IntRect(0,0,0,0),true);

    region = _assets.pixel.spriteSheet.createRegion(group);
    srcClip = region.srcClip;

    _assets.pixel.NW = TextureRegion(region.texture,sf::IntRect(srcClip.left,srcClip.top,5,5));
    _assets.pixel.NE = TextureRegion(region.texture,sf::IntRect(srcClip.left+5,srcClip.top,5,5));
    _assets.pixel.SW = TextureRegion(region.texture,sf::IntRect(srcClip.left,srcClip.top+5,5,5));
    _assets.pixel.SE = TextureRegion(region.texture,sf::IntRect(srcClip.left+5,srcClip.top+5,5,5));


    // a 48x48 seedslot texture
    group.create(64,64,sf::Color(0,0,0,0));
    image.loadFromFile("assets/img/pixels/seedslot.png");
    group.copy(image,0,0,sf::IntRect(0,0,0,0),true);

    region = _assets.pixel.spriteSheet.createRegion(group);
    srcClip = region.srcClip;

    _assets.pixel.seedSlot = TextureRegion(region.texture,sf::IntRect(srcClip.left,srcClip.top,48,48));

    // load fonts
    _assets.fonts.upheav.loadFromFile("assets/fonts/upheavtt.ttf");
}

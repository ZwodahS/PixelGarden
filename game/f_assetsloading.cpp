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


    // growth segments
    group.create(64,64,sf::Color(0,0,0,0));
    image.loadFromFile("assets/img/segments/last_east.png");
    group.copy(image,0,0,sf::IntRect(0,0,0,0),true);
    image.loadFromFile("assets/img/segments/last_south.png");
    group.copy(image,16,0,sf::IntRect(0,0,0,0),true);
    image.loadFromFile("assets/img/segments/last_west.png");
    group.copy(image,32,0,sf::IntRect(0,0,0,0),true);
    image.loadFromFile("assets/img/segments/last_north.png");
    group.copy(image,48,0,sf::IntRect(0,0,0,0),true);
    image.loadFromFile("assets/img/segments/source_east.png");
    group.copy(image,0,16,sf::IntRect(0,0,0,0),true);
    image.loadFromFile("assets/img/segments/source_south.png");
    group.copy(image,16,16,sf::IntRect(0,0,0,0),true);
    image.loadFromFile("assets/img/segments/source_west.png");
    group.copy(image,32,16,sf::IntRect(0,0,0,0),true);
    image.loadFromFile("assets/img/segments/source_north.png");
    group.copy(image,48,16,sf::IntRect(0,0,0,0),true);

    region = _assets.pixel.spriteSheet.createRegion(group);
    srcClip = region.srcClip;

    _assets.pixel.segments.lastEast    = TextureRegion(region.texture,sf::IntRect(srcClip.left,srcClip.top,16,16));
    _assets.pixel.segments.lastSouth   = TextureRegion(region.texture,sf::IntRect(srcClip.left+16,srcClip.top,16,16));
    _assets.pixel.segments.lastWest    = TextureRegion(region.texture,sf::IntRect(srcClip.left+32,srcClip.top,16,16));
    _assets.pixel.segments.lastNorth   = TextureRegion(region.texture,sf::IntRect(srcClip.left+48,srcClip.top,16,16));
    _assets.pixel.segments.sourceEast  = TextureRegion(region.texture,sf::IntRect(srcClip.left,srcClip.top+16,16,16));
    _assets.pixel.segments.sourceSouth = TextureRegion(region.texture,sf::IntRect(srcClip.left+16,srcClip.top+16,16,16));
    _assets.pixel.segments.sourceWest  = TextureRegion(region.texture,sf::IntRect(srcClip.left+32,srcClip.top+16,16,16));
    _assets.pixel.segments.sourceNorth = TextureRegion(region.texture,sf::IntRect(srcClip.left+48,srcClip.top+16,16,16));

    // PGS assets
    group.create(64,64,sf::Color(0,0,0,0));
    image.loadFromFile("assets/img/pgs/blue.png");
    group.copy(image,0,0,sf::IntRect(0,0,0,0),true);
    image.loadFromFile("assets/img/pgs/cyan.png");
    group.copy(image,16,0,sf::IntRect(0,0,0,0),true);
    image.loadFromFile("assets/img/pgs/dark.png");
    group.copy(image,32,0,sf::IntRect(0,0,0,0),true);
    image.loadFromFile("assets/img/pgs/gray.png");
    group.copy(image,48,0,sf::IntRect(0,0,0,0),true);
    image.loadFromFile("assets/img/pgs/green.png");
    group.copy(image,0,16,sf::IntRect(0,0,0,0),true);
    image.loadFromFile("assets/img/pgs/orange.png");
    group.copy(image,16,16,sf::IntRect(0,0,0,0),true);
    image.loadFromFile("assets/img/pgs/purple.png");
    group.copy(image,32,16,sf::IntRect(0,0,0,0),true);
    image.loadFromFile("assets/img/pgs/red.png");
    group.copy(image,48,16,sf::IntRect(0,0,0,0),true);
    image.loadFromFile("assets/img/pgs/yellow.png");
    group.copy(image,0,32,sf::IntRect(0,0,0,0),true);
    
    region = _assets.pixel.spriteSheet.createRegion(group);
    srcClip = region.srcClip;

    _assets.pixel.pgs.blue   = TextureRegion(region.texture,sf::IntRect(srcClip.left + 0  ,srcClip.top + 0  , 16 , 16));
    _assets.pixel.pgs.cyan   = TextureRegion(region.texture,sf::IntRect(srcClip.left + 16 ,srcClip.top + 0  , 16 , 16));
    _assets.pixel.pgs.dark   = TextureRegion(region.texture,sf::IntRect(srcClip.left + 32 ,srcClip.top + 0  , 16 , 16));
    _assets.pixel.pgs.gray   = TextureRegion(region.texture,sf::IntRect(srcClip.left + 48 ,srcClip.top + 0  , 16 , 16));
    _assets.pixel.pgs.green  = TextureRegion(region.texture,sf::IntRect(srcClip.left + 0  ,srcClip.top + 16 , 16 , 16));
    _assets.pixel.pgs.orange = TextureRegion(region.texture,sf::IntRect(srcClip.left + 16 ,srcClip.top + 16 , 16 , 16));
    _assets.pixel.pgs.purple = TextureRegion(region.texture,sf::IntRect(srcClip.left + 32 ,srcClip.top + 16 , 16 , 16));
    _assets.pixel.pgs.red    = TextureRegion(region.texture,sf::IntRect(srcClip.left + 48 ,srcClip.top + 16 , 16 , 16));
    _assets.pixel.pgs.yellow = TextureRegion(region.texture,sf::IntRect(srcClip.left + 0  ,srcClip.top + 32 , 16 , 16));
    // load fonts
    _assets.fonts.upheav.loadFromFile("assets/fonts/upheavtt.ttf");

}

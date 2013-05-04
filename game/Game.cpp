#include "Game.hpp"
#include "garden/Garden.hpp"
#include "consts.hpp"
#include "../zf_sfml/Mouse.hpp"
#include "../zf_sfml/TextureRegion.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>


Game::Game()
{
    _window = new sf::RenderWindow(sf::VideoMode(displayconsts::DISPLAY_WIDTH,displayconsts::DISPLAY_HEIGHT), "Pixel Garden");
    initAssets();
}

Game::~Game()
{
    delete _window;
}


void Game::run()
{
    sf::Clock clock;
    zf::Mouse mouse;
    _currentScreen = new GameScreen(this,&mouse);
    while(_window->isOpen())
    {
        sf::Time delta = clock.restart();
        mouse.update(delta);
        sf::Event event;
        while(_window->pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                _window->close();
            }
        }
        update(delta);
        draw(delta);
    }
}

bool Game::update(sf::Time delta)
{
}

void Game::draw(sf::Time delta)
{
    _window->clear(sf::Color(255,20,20,255));
    if(_currentScreen != 0)
    {
        _currentScreen->draw(_window,delta);   
    }
    _window->display();
}

void Game::initAssets()
{
    _assets.pixel.spriteSheet = SpriteSheet(sf::IntRect(0,0,32,32),5,5);
    sf::Image image;
    image.loadFromFile("assets/img/pixels/pixeltexture.png");
    _assets.pixel.pixelTexture = _assets.pixel.spriteSheet.createRegion(image);

    // do some hacking :D 
    // I have 4 selection NE NW SE SW , each being 5 pixel by 5 pixel. 
    // I can create a image of size 32 by 32 , and put it inside before putting into the texture.

    sf::Image groupSelectionImage;
    groupSelectionImage.create(32,32,sf::Color(0,0,0,0));
    image.loadFromFile("assets/img/selection/NW.png");
    groupSelectionImage.copy(image,0,0,sf::IntRect(0,0,0,0),true);
    image.loadFromFile("assets/img/selection/NE.png");
    groupSelectionImage.copy(image,5,0,sf::IntRect(0,0,0,0),true);
    image.loadFromFile("assets/img/selection/SW.png");
    groupSelectionImage.copy(image,0,5,sf::IntRect(0,0,0,0),true);
    image.loadFromFile("assets/img/selection/SE.png");
    groupSelectionImage.copy(image,5,5,sf::IntRect(0,0,0,0),true);

    TextureRegion region = _assets.pixel.spriteSheet.createRegion(groupSelectionImage);
    sf::IntRect srcClip = region.srcClip;
    _assets.pixel.NW = TextureRegion(region.texture,sf::IntRect(srcClip.left,srcClip.top,5,5));
    _assets.pixel.NE = TextureRegion(region.texture,sf::IntRect(srcClip.left+5,srcClip.top,5,5));
    _assets.pixel.SW = TextureRegion(region.texture,sf::IntRect(srcClip.left,srcClip.top+5,5,5));
    _assets.pixel.SE = TextureRegion(region.texture,sf::IntRect(srcClip.left+5,srcClip.top+5,5,5));

}

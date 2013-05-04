#include "GameScreen.hpp"
#include "../consts.hpp"
#include "../Game.hpp"
#include "../../zf_sfml/Mouse.hpp"

GameScreen::GameScreen(Game* game,zf::Mouse* mouse )
    :Screen(game)
{
    this->_mouse = mouse;    
    this->_garden = new Garden(_game);
    this->_view = sf::View(sf::FloatRect(0,0,displayconsts::DISPLAY_WIDTH,displayconsts::DISPLAY_HEIGHT));
    _view.setViewport(sf::FloatRect(0,0,1,1));

}

GameScreen::~GameScreen()
{
}

void GameScreen::draw(sf::RenderWindow* window, sf::Time delta)
{
    window->setView(_view);
    _garden->draw(window,delta,_mouse);
}


void GameScreen::update(sf::Time delta)
{

}

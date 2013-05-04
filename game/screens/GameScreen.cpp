#include "GameScreen.hpp"
#include "../consts.hpp"
#include "../Game.hpp"
#include "../../zf_sfml/Mouse.hpp"

GameScreen::GameScreen(Game* game,zf::Mouse* mouse )
    :Screen(game)
{
    this->_mouse = mouse;    
    this->_view = sf::View(sf::FloatRect(0,0,displayconsts::DISPLAY_WIDTH,displayconsts::DISPLAY_HEIGHT));
    _view.setViewport(sf::FloatRect(0,0,1,1));
}

GameScreen::~GameScreen()
{
    delete _garden;
    delete _seedManager;
    delete _geneManager;
}

void GameScreen::draw(sf::RenderWindow* window, sf::Time delta)
{
    window->setView(_view);
    _garden->draw(window,delta,_mouse);
}


void GameScreen::update(sf::Time delta)
{

}

void GameScreen::initNewGame()
{
    this->_geneManager = new GeneManager();
    this->_geneManager->initBasicRules();
    this->_seedManager = new SeedManager(_geneManager);
    this->_garden = new Garden(_game);
}

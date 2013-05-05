#include "GameScreen.hpp"
#include "SeedScreen.hpp"
#include "../consts.hpp"
#include "../Game.hpp"
#include "../../zf_sfml/Mouse.hpp"

GameScreen::GameScreen(Game* game,zf::Mouse* mouse )
    :Screen(game)
{
    this->_mouse = mouse;    
    this->_gardenView = sf::View(sf::FloatRect(0,0,displayconsts::DISPLAY_WIDTH,displayconsts::DISPLAY_HEIGHT));
    _gardenView.setViewport(sf::FloatRect(0,0,1,1));
    this->_seedView = sf::View(sf::FloatRect(0,0,0.8f * displayconsts::DISPLAY_WIDTH, 0.8f * displayconsts::DISPLAY_HEIGHT));
    _seedView.setViewport(sf::FloatRect(0.1f,0.1f,0.8f,0.8f));
    
    this->_data = 0;
    this->_seedScreen = 0;
}

GameScreen::~GameScreen()
{
    if(_data != 0)
    {
        delete _data;
    }
}

void GameScreen::draw(sf::RenderWindow* window, sf::Time delta)
{
    window->setView(_gardenView);
    if(_seedScreen == 0)
    {
        _data->garden->draw(window,delta,_mouse);
    }
    else
    {
        _data->garden->draw(window,delta);
    }
    window->setView(_seedView);
    if(_seedScreen != 0)
    {
        _seedScreen->draw(window,delta);
    }

}


void GameScreen::update(sf::Time delta)
{

}

void GameScreen::initNewGame()
{
    GeneManager* geneManager = new GeneManager();
    geneManager->initBasicRules();
    SeedManager* seedManager = new SeedManager(geneManager);
    Garden* garden = new Garden(_game);
    _data = new GameData(seedManager,geneManager,garden);
    showSeedScreen();
}

void GameScreen::showSeedScreen()
{
    _seedScreen = new SeedScreen(_game,_data);
}

#include "GameScreen.hpp"
#include "SeedScreen.hpp"
#include "../consts.hpp"
#include "../Game.hpp"
#include "../../zf_sfml/Mouse.hpp"

GameScreen::GameScreen(Game* game)
    :Screen(game)
{
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
    if(_seedScreen != 0)
    {
        delete _seedScreen;
    }
}

void GameScreen::draw(sf::RenderWindow* window, sf::Time delta)
{
    window->setView(_gardenView);
    if(_seedScreen == 0)
    {
        _data->garden->draw(window,delta,_game->_mouse);
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
    // inventory opening will prevent other inputs from being trigger.
    if(_game->_keyInput->open_inv.thisPressed)
    {
        toggleSeedScreen();
    }
    else 
    {
        // if the seed screen is open, let it do its own input handling.
        if(_seedScreen != 0 )
        {
            _seedScreen->update(delta);
        }
        else
        {
            
        }
    }
}

void GameScreen::initNewGame()
{
    GeneManager* geneManager = new GeneManager();
    geneManager->initBasicRules();
    SeedManager* seedManager = new SeedManager(geneManager);
    Garden* garden = new Garden(_game);
    _data = new GameData(seedManager,geneManager,garden);
}

void GameScreen::showSeedScreen()
{
    _seedScreen = new SeedScreen(_game,_data);
}

void GameScreen::hideSeedScreen()
{
    delete _seedScreen;
    _seedScreen = 0;
}

void GameScreen::toggleSeedScreen()
{
    if(_seedScreen != 0)
    {
        hideSeedScreen();
    }
    else
    {
        showSeedScreen();
    }
}

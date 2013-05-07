#include "GameScreen.hpp"
#include "SeedScreen.hpp"
#include "../consts.hpp"
#include "../Game.hpp"
#include "../PGS.hpp"
#include "../../zf_sfml/Mouse.hpp"

#define HUD_LEFT 650
#define FIRST_OFF 180
#define SECOND_OFF 220
#define THIRD_OFF 260

#define GROWTH_SEG_ROW_ONE 200

#define HELP_TEXT_HUD 430
#define HELP_TEXT_SPACING 20
#define PGS_X_OFFSET 665
#define PGS_Y_OFFSET 260
GameScreen::GameScreen(Game* game)
    :Screen(game)
{
    this->pgs = 0;
    this->_gardenView = sf::View(sf::FloatRect(0,0,displayconsts::DISPLAY_WIDTH,displayconsts::DISPLAY_HEIGHT));
    this->_gardenView.setViewport(sf::FloatRect(0,0,1,1));
    this->_hudView = sf::View(sf::FloatRect(0,0,displayconsts::DISPLAY_WIDTH, displayconsts::DISPLAY_HEIGHT));
    this->_hudView.setViewport(sf::FloatRect(0,0,1,1));
    this->_data = 0;
    this->_seedScreen = 0;
    
    this->_hud_currentDisplayedSeed = 0;
    this->_hud_seedName = sf::Text("No Seed Selected",_game->_assets.fonts.upheav,16);
    this->_hud_seedName.setPosition(HUD_LEFT,20);
    this->_hud_seedName.setColor(sf::Color::White);

    this->_hud_growthSegText = std::vector<sf::Text*>(0);
    for(int i = 0 ; i < 4 ; i++)
    {
        _hud_growthSegText.push_back(new sf::Text(" ",_game->_assets.fonts.upheav,16));
    }
    this->_hud_growthSegText[0]->setString("Segments");
    this->_hud_growthSegText[0]->setPosition(HUD_LEFT,50);
    this->_hud_growthSegText[1]->setPosition(HUD_LEFT+FIRST_OFF,50);
    this->_hud_growthSegText[1]->setColor(sf::Color::Blue);
    this->_hud_growthSegText[2]->setPosition(HUD_LEFT+SECOND_OFF,50);
    this->_hud_growthSegText[2]->setColor(sf::Color::Green);
    this->_hud_growthSegText[3]->setPosition(HUD_LEFT+THIRD_OFF,50);

    this->_hud_growthTurnText = std::vector<sf::Text*>(0);
    for(int i = 0 ; i < 4 ; i++)
    {
        _hud_growthTurnText.push_back(new sf::Text(" ",_game->_assets.fonts.upheav,16));
    }
    this->_hud_growthTurnText[0]->setString("Growth Duration");
    this->_hud_growthTurnText[0]->setPosition(HUD_LEFT,70);
    this->_hud_growthTurnText[1]->setPosition(HUD_LEFT+FIRST_OFF,70);
    this->_hud_growthTurnText[1]->setColor(sf::Color::Blue);
    this->_hud_growthTurnText[2]->setPosition(HUD_LEFT+SECOND_OFF,70);
    this->_hud_growthTurnText[2]->setColor(sf::Color::Green);
    this->_hud_growthTurnText[3]->setPosition(HUD_LEFT+THIRD_OFF,70);

    this->_hud_maturedDurationsText = std::vector<sf::Text*>(0);
    for(int i = 0 ; i < 4; i ++)
    {
        _hud_maturedDurationsText.push_back(new sf::Text(" ",_game->_assets.fonts.upheav,16));
    }
    this->_hud_maturedDurationsText[0]->setString("Maturity Duration");
    this->_hud_maturedDurationsText[0]->setPosition(HUD_LEFT,90);
    this->_hud_maturedDurationsText[1]->setPosition(HUD_LEFT+FIRST_OFF,90);
    this->_hud_maturedDurationsText[1]->setColor(sf::Color::Blue);
    this->_hud_maturedDurationsText[2]->setPosition(HUD_LEFT+SECOND_OFF,90);
    this->_hud_maturedDurationsText[2]->setColor(sf::Color::Green);
    this->_hud_maturedDurationsText[3]->setPosition(HUD_LEFT+THIRD_OFF,90);

    this->_hud_decayTurnText = std::vector<sf::Text*>(0);
    for(int i = 0 ; i <4 ; i++)
    {
        _hud_decayTurnText.push_back(new sf::Text(" ",_game->_assets.fonts.upheav,16));
    }
    this->_hud_decayTurnText[0]->setString("Decay Duration");
    this->_hud_decayTurnText[0]->setPosition(HUD_LEFT,110);
    this->_hud_decayTurnText[1]->setPosition(HUD_LEFT+FIRST_OFF,110);
    this->_hud_decayTurnText[1]->setColor(sf::Color::Blue);
    this->_hud_decayTurnText[2]->setPosition(HUD_LEFT+SECOND_OFF,110);
    this->_hud_decayTurnText[2]->setColor(sf::Color::Green);
    this->_hud_decayTurnText[3]->setPosition(HUD_LEFT+THIRD_OFF,110);

    this->_hud_genesText = std::vector<sf::Text*>(0);
    for(int i = 0 ; i < 4 ; i ++)
    {
        _hud_genesText.push_back(new sf::Text(" ",_game->_assets.fonts.upheav,16));
    }
    this->_hud_genesText[0]->setString("Maximum Genes");
    this->_hud_genesText[0]->setPosition(HUD_LEFT,130);
    this->_hud_genesText[1]->setPosition(HUD_LEFT+FIRST_OFF,130);
    this->_hud_genesText[1]->setColor(sf::Color::Blue);
    this->_hud_genesText[2]->setPosition(HUD_LEFT+SECOND_OFF,130);
    this->_hud_genesText[2]->setColor(sf::Color::Green);
    this->_hud_genesText[3]->setPosition(HUD_LEFT+THIRD_OFF,130);

    this->_hud_seedMaturedText = std::vector<sf::Text*>(0);
    for(int i = 0 ; i <4 ; i ++)
    {
        _hud_seedMaturedText.push_back(new sf::Text(" ",_game->_assets.fonts.upheav,16));
    }
    this->_hud_seedMaturedText[0]->setString("Maturity Seed(%)");
    this->_hud_seedMaturedText[0]->setPosition(HUD_LEFT,150);
    this->_hud_seedMaturedText[1]->setPosition(HUD_LEFT+FIRST_OFF,150);
    this->_hud_seedMaturedText[1]->setColor(sf::Color::Blue);
    this->_hud_seedMaturedText[2]->setPosition(HUD_LEFT+SECOND_OFF,150);
    this->_hud_seedMaturedText[2]->setColor(sf::Color::Green);
    this->_hud_seedMaturedText[3]->setPosition(HUD_LEFT+THIRD_OFF,150);

    this->_hud_seedDecayText = std::vector<sf::Text*>(0);
    for(int i = 0 ; i < 4 ; i ++)
    {
        _hud_seedDecayText.push_back(new sf::Text(" ",_game->_assets.fonts.upheav,16));
    }
    this->_hud_seedDecayText[0]->setString("Decay Seed(%)");
    this->_hud_seedDecayText[0]->setPosition(HUD_LEFT,170);
    this->_hud_seedDecayText[1]->setPosition(HUD_LEFT+FIRST_OFF,170);
    this->_hud_seedDecayText[1]->setColor(sf::Color::Blue);
    this->_hud_seedDecayText[2]->setPosition(HUD_LEFT+SECOND_OFF,170);
    this->_hud_seedDecayText[2]->setColor(sf::Color::Green);
    this->_hud_seedDecayText[3]->setPosition(HUD_LEFT+THIRD_OFF,170);

    this->_hud_color = std::vector<sf::Text*>(0);
    for(int i = 0 ; i < 4 ; i++)
    {
        _hud_color.push_back(new sf::Text(" ",_game->_assets.fonts.upheav,16));
    }
    this->_hud_color[0]->setString("Color(R,G,B)");
    this->_hud_color[0]->setPosition(HUD_LEFT,170);
    this->_hud_color[1]->setPosition(HUD_LEFT+FIRST_OFF,170);
    this->_hud_color[1]->setColor(sf::Color::Red);
    this->_hud_color[2]->setPosition(HUD_LEFT+SECOND_OFF,170);
    this->_hud_color[2]->setColor(sf::Color::Green);
    this->_hud_color[3]->setPosition(HUD_LEFT+THIRD_OFF,170);
    this->_hud_color[3]->setColor(sf::Color::Blue);

    this->_hud_geneTitle = sf::Text("Gene List",_game->_assets.fonts.upheav,16);
    this->_hud_geneId = std::vector<sf::Text*>(0);

    this->_hud_pgs = sf::Text("Pixel Gene Structure",_game->_assets.fonts.upheav,16);
    this->_hud_pgs.setPosition(PGS_X_OFFSET,PGS_Y_OFFSET - 30);

    this->_hud_growthSegments = std::vector<sf::Sprite>(0);
// HELP TEXT    
    this->_hud_helpTexts = std::vector<sf::Text*>(0);
    sf::Text* baseText = new sf::Text("Blue is base stats",_game->_assets.fonts.upheav,16);
    baseText->setColor(sf::Color::Blue);
    sf::Text* bonus = new sf::Text("Green is bonus stats from",_game->_assets.fonts.upheav,16);
    bonus->setColor(sf::Color::Green);
    sf::Text* bonus2 = new sf::Text("  expressed Genes",_game->_assets.fonts.upheav,16);
    bonus2->setColor(sf::Color::Green);
    sf::Text* final = new sf::Text("White is final stats",_game->_assets.fonts.upheav,16);
    final->setColor(sf::Color::Red);
    sf::Text* invText = new sf::Text("<I> to open the list of seeds",_game->_assets.fonts.upheav,16);
    sf::Text* spaceText = new sf::Text("<Space> to advance the garden",_game->_assets.fonts.upheav,16);
    sf::Text* space2    = new sf::Text(" by 1 turn",_game->_assets.fonts.upheav,16);

    sf::Text* mutation = new sf::Text("Combine 2 or more seed by letting",_game->_assets.fonts.upheav,16);
    sf::Text* mutation2 = new sf::Text(" them grow into the same pixel.",_game->_assets.fonts.upheav,16);

    sf::Text* rest = new sf::Text("The rest is up to you to find out...",_game->_assets.fonts.upheav,16);
    this->_hud_helpTexts.push_back(baseText);
    this->_hud_helpTexts.push_back(bonus);
    this->_hud_helpTexts.push_back(bonus2);
    this->_hud_helpTexts.push_back(final);
    this->_hud_helpTexts.push_back(invText);
    this->_hud_helpTexts.push_back(spaceText);
    this->_hud_helpTexts.push_back(space2);
    this->_hud_helpTexts.push_back(mutation);
    this->_hud_helpTexts.push_back(mutation2);
    this->_hud_helpTexts.push_back(rest);
    for(int i = 0 ; i < _hud_helpTexts.size() ; i++)
    {
        _hud_helpTexts[i]->setPosition(HUD_LEFT,HELP_TEXT_HUD+(i*HELP_TEXT_SPACING));
    }
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
    for(int i = 0 ; i < _hud_growthSegText.size(); i++)
    {
        delete _hud_growthSegText[i];
    }
    for(int i = 0 ; i < _hud_growthTurnText.size(); i++)
    {
        delete _hud_growthTurnText[i];
    }
    for(int i = 0 ; i < _hud_maturedDurationsText.size(); i++)
    {
        delete _hud_maturedDurationsText[i];
    }
    for(int i = 0 ; i < _hud_decayTurnText.size(); i++)
    {
        delete _hud_decayTurnText[i];
    }
    for(int i = 0 ; i < _hud_genesText.size(); i++)
    {
        delete _hud_genesText[i];
    }
    for(int i = 0 ; i < _hud_seedMaturedText.size(); i++)
    {
        delete _hud_seedMaturedText[i];
    }
    for(int i = 0 ; i < _hud_seedDecayText.size(); i++)
    {
        delete _hud_seedDecayText[i];
    }
    for(int i = 0 ; i < _hud_geneId.size(); i++)
    {
        delete _hud_geneId[i];
    }
    for(int i = 0 ; i < _hud_helpTexts.size(); i++)
    {
        delete _hud_helpTexts[i];
    }
    for(int i = 0 ; i < _hud_color.size() ; i++)
    {
        delete _hud_color[i];
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
    if(_seedScreen != 0)
    {
        _seedScreen->draw(window,delta);
    }
    if(_data != 0 && _hud_currentDisplayedSeed != _data->selectedSeed)
    {
        if(_data->selectedSeed != 0)
        {
            _hud_currentDisplayedSeed = _data->selectedSeed;
            this->_hud_seedName.setString("Seed Id : #"+zf::toString(_data->selectedSeed->_id));
            
            this->_hud_growthSegText[1]->setString(zf::toString(_hud_currentDisplayedSeed->_baseAttributes.growthSegments));
            this->_hud_growthSegText[2]->setString(zf::toStringSigned(_hud_currentDisplayedSeed->_bonusAttributes.growthSegments));
            this->_hud_growthSegText[3]->setString(zf::toString(_hud_currentDisplayedSeed->_effectiveAttributes.growthSegments));

            this->_hud_growthTurnText[1]->setString(zf::toString(_hud_currentDisplayedSeed->_baseAttributes.growthTurns));
            this->_hud_growthTurnText[2]->setString(zf::toStringSigned(_hud_currentDisplayedSeed->_bonusAttributes.growthTurns));
            this->_hud_growthTurnText[3]->setString(zf::toString(_hud_currentDisplayedSeed->_effectiveAttributes.growthTurns));

            this->_hud_maturedDurationsText[1]->setString(zf::toString(_hud_currentDisplayedSeed->_baseAttributes.maturedDuration));
            this->_hud_maturedDurationsText[2]->setString(zf::toStringSigned(_hud_currentDisplayedSeed->_bonusAttributes.maturedDuration));
            this->_hud_maturedDurationsText[3]->setString(zf::toString(_hud_currentDisplayedSeed->_effectiveAttributes.maturedDuration));

            this->_hud_decayTurnText[1]->setString(zf::toString(_hud_currentDisplayedSeed->_baseAttributes.decayTurns));
            this->_hud_decayTurnText[2]->setString(zf::toStringSigned(_hud_currentDisplayedSeed->_bonusAttributes.decayTurns));
            this->_hud_decayTurnText[3]->setString(zf::toString(_hud_currentDisplayedSeed->_effectiveAttributes.decayTurns));

            this->_hud_genesText[1]->setString(zf::toString(_hud_currentDisplayedSeed->_baseAttributes.maxExpressedTraits));
            this->_hud_genesText[2]->setString(zf::toStringSigned(_hud_currentDisplayedSeed->_bonusAttributes.maxExpressedTraits));
            this->_hud_genesText[3]->setString(zf::toString(_hud_currentDisplayedSeed->_effectiveAttributes.maxExpressedTraits));

            this->_hud_seedMaturedText[1]->setString(zf::toString(_hud_currentDisplayedSeed->_baseAttributes.maturedSeed.chance));
            this->_hud_seedMaturedText[2]->setString(zf::toStringSigned(_hud_currentDisplayedSeed->_bonusAttributes.maturedSeed.chance));
            this->_hud_seedMaturedText[3]->setString(zf::toString(_hud_currentDisplayedSeed->_effectiveAttributes.maturedSeed.chance));

            this->_hud_seedDecayText[1]->setString(zf::toString(_hud_currentDisplayedSeed->_baseAttributes.decaySeed.chance));
            this->_hud_seedDecayText[2]->setString(zf::toStringSigned(_hud_currentDisplayedSeed->_bonusAttributes.decaySeed.chance));
            this->_hud_seedDecayText[3]->setString(zf::toString(_hud_currentDisplayedSeed->_effectiveAttributes.decaySeed.chance));
            
            this->_hud_color[1]->setString(zf::toString(_hud_currentDisplayedSeed->_color.r));
            this->_hud_color[2]->setString(zf::toString(_hud_currentDisplayedSeed->_color.g));
            this->_hud_color[3]->setString(zf::toString(_hud_currentDisplayedSeed->_color.b));
            this->_hud_growthSegments = std::vector<sf::Sprite>(0);
            for(int i = 0 ; i < _hud_currentDisplayedSeed->_segments.size(); i++)
            {
                _hud_growthSegments.push_back(_game->createSprite(_hud_currentDisplayedSeed->_segments[i]));
                _hud_growthSegments[i].setPosition(HUD_LEFT + (i * 18), GROWTH_SEG_ROW_ONE);
            }
            if(pgs != 0)
            {
                delete pgs;
            }
            pgs = new PGS(_game,_hud_currentDisplayedSeed, sf::Vector2f(PGS_X_OFFSET,PGS_Y_OFFSET));
        }
        else
        {
            this->_hud_seedName.setString("No Seed Selected");
        }
    }
    drawHud(window,delta);
}


void GameScreen::update(sf::RenderWindow* window, sf::Time delta)
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
            _seedScreen->update(window, delta);
        }
        else
        {
            window->setView(_gardenView);
            if(_game->_mouse->_left.thisReleased)
            {
                if(_data->selectedSeed != 0)
                {
                    sf::Vector2f mousePos = _game->_mouse->getWorldPosition(*window);
                    Grid selectedGrid = Grid::toGrid(mousePos.x,mousePos.y,displayconsts::PIXEL_SIZE,displayconsts::PIXEL_SPACING);
                    _data->garden->plantSeed(_data->selectedSeed, selectedGrid);
                    _data->seedManager->seedPlanted(_data->selectedSeed);
                }
            }
            else if(_game->_keyInput->processOneTurn.thisReleased)
            {
                _data->garden->doOneTurn();
            }
        }
    }
}

void GameScreen::drawHud(sf::RenderWindow* window, sf::Time delta)
{
    window->setView(_hudView);
    window->draw(_hud_seedName);
    if(_hud_currentDisplayedSeed != 0)
    {
        for(int i = 0 ; i < _hud_color.size() ; i++)
        {
            window->draw(*_hud_color[i]);
        }
        //for(int i = 0 ; i < _hud_seedDecayText.size() ; i++)
        //{
        //    window->draw(*_hud_seedDecayText[i]);
        //}
        //for(int i = 0 ; i < _hud_seedMaturedText.size() ; i++)
        //{
        //    window->draw(*_hud_seedMaturedText[i]);
        //}
        for(int i = 0 ; i < _hud_genesText.size() ; i++)
        {
            window->draw(*_hud_genesText[i]);
        }
        for(int i = 0 ; i < _hud_decayTurnText.size() ; i++)
        {
            window->draw(*_hud_decayTurnText[i]);
        }
        for(int i = 0 ; i < _hud_maturedDurationsText.size() ; i++)
        {
            window->draw(*_hud_maturedDurationsText[i]);
        }
        for(int i = 0 ; i < _hud_growthTurnText.size() ; i++)
        {
            window->draw(*_hud_growthTurnText[i]);
        }
        for(int i = 0 ; i < _hud_growthSegText.size() ; i++)
        {
            window->draw(*_hud_growthSegText[i]);
        }
        for(int i = 0 ; i < _hud_growthSegments.size() ; i++)
        {
            window->draw(_hud_growthSegments[i]);
        }
        window->draw(_hud_pgs);
        pgs->draw(window,delta);
    } 

    for(int i = 0 ; i < _hud_helpTexts.size() ; i++)
    {
        window->draw(*_hud_helpTexts[i]);
    }
}

void GameScreen::initNewGame()
{
    GeneManager* geneManager = new GeneManager();
    geneManager->initBasicRules();
    SeedManager* seedManager = new SeedManager(geneManager);
    Garden* garden = new Garden(_game,seedManager);
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



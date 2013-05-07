#ifndef _GAME_SCREENS_GAMESCREEN_H_
#define _GAME_SCREENS_GAMESCREEN_H_

#include "Screen.hpp"

#include "../GeneManager.hpp"
#include "../SeedManager.hpp"
#include "../g_seeds.hpp"
#include "../g_garden.hpp"
#include "../GameData.hpp"
#include "../../zf_sfml/Mouse.hpp"

#include <SFML/Graphics.hpp>

class Game;
class SeedScreen;
class GameScreen : public Screen
{
    public:
        GameScreen(Game* game);
        ~GameScreen();

        virtual void draw(sf::RenderWindow* window, sf::Time delta);
        virtual void update(sf::RenderWindow* window, sf::Time delta);

        GameData* _data;        
        void initNewGame();
        void showSeedScreen();
        void hideSeedScreen();
        void toggleSeedScreen();
    private:
        SeedScreen* _seedScreen;
        sf::View _gardenView;
        sf::View _seedView;
        sf::View _hudView;
        
        Seed* _hud_currentDisplayedSeed;
        sf::Text _hud_seedName;
        std::vector<sf::Text*> _hud_growthSegText;
        std::vector<sf::Text*> _hud_growthTurnText;
        std::vector<sf::Text*> _hud_maturedDurationsText;
        std::vector<sf::Text*> _hud_decayTurnText;
        std::vector<sf::Text*> _hud_genesText;
        std::vector<sf::Text*> _hud_seedMaturedText;
        std::vector<sf::Text*> _hud_seedDecayText;
        std::vector<sf::Text*> _hud_color;
        sf::Text _hud_geneTitle;
        std::vector<sf::Text*> _hud_geneId;
    
        std::vector<sf::Sprite> _hud_growthSegments;

        void drawHud(sf::RenderWindow* window, sf::Time delta);


        std::vector<sf::Text*> _hud_helpTexts;
};

#endif


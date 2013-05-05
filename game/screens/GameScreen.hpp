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
        virtual void update(sf::Time delta);

        GameData* _data;        
        void initNewGame();
        void showSeedScreen();
    private:
        SeedScreen* _seedScreen;
        sf::View _gardenView;
        sf::View _seedView;
};

#endif


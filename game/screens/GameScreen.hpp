#ifndef _GAME_SCREENS_GAMESCREEN_H_
#define _GAME_SCREENS_GAMESCREEN_H_

#include "Screen.hpp"

#include "../GeneManager.hpp"
#include "../SeedManager.hpp"
#include "../g_seeds.hpp"
#include "../g_garden.hpp"

#include "../../zf_sfml/Mouse.hpp"

#include <SFML/Graphics.hpp>

class Game;
class GameScreen : public Screen
{
    public:
        GameScreen(Game* game,zf::Mouse* mouse);
        ~GameScreen();

        virtual void draw(sf::RenderWindow* window, sf::Time delta);
        virtual void update(sf::Time delta);

        GeneManager* _geneManager;
        SeedManager* _seedManager;
        
        void initNewGame();
    private:
        zf::Mouse* _mouse;

        Garden* _garden;

        sf::View _view;
};

#endif


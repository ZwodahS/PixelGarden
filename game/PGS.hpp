#ifndef _GAME_SCREEN_PGS_H_
#define _GAME_SCREEN_PGS_H_
// PGS = Pixel Gene Structure
#include "g_seeds.hpp"
#include "Game.hpp"

#include <SFML/Graphics.hpp>
class PGS 
{
    public:
        PGS(Game* game,Seed* seed,sf::Vector2f drawOffset);
        ~PGS();

        void draw(sf::RenderWindow* window, sf::Time delta);
    private:
        Seed* _seed;
        Game* _game;

        std::vector<sf::RectangleShape> gblocks;
};
#endif

#ifndef _GAME_GAME_H_
#define _GAME_GAME_H_
#include "Assets.h"
#include <SFML/Graphics.hpp>

class Garden;
class Game
{
    public:
        Game();
        ~Game();
        void run(); 

        sf::RenderWindow* _window; 

        Assets _assets;

        Garden* _garden;
    private:

        bool update(sf::Time delta);
        void draw(sf::Time delta);
        
    

        void initAssets();
};


#endif


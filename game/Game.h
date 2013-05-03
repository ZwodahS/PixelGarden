#ifndef _GAME_GAME_H_
#define _GAME_GAME_H_

#include <SFML/Graphics.hpp>
class Game
{
    public:
        Game();
        ~Game();
        void run(); 

        sf::RenderWindow* _window; 
    private:

        bool update(sf::Time delta);
        void draw(sf::Time delta);
        

};


#endif


#ifndef _GAME_GAME_H_
#define _GAME_GAME_H_
#include "g_screens.hpp"
#include "seeds/GrowthSegment.hpp"
#include "GameData.hpp"
#include "Assets.hpp"
#include "f_debug.hpp"
#include "InputControl.hpp"
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
    

        zf::Mouse* _mouse;
        InputControl* _keyInput;

        sf::Sprite createSprite(GrowthSegment gs);

    private:
        Screen* _currentScreen;
        bool update(sf::Time delta);
        void draw(sf::Time delta);
        
            

        void initAssets();
};


#endif


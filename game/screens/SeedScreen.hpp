#ifndef _GAME_SCREENS_SEEDSCREEN_H_
#define _GAME_SCREENS_SEEDSCREEN_H_

#include "Screen.hpp"
#include "../GameData.hpp"

#include "../../zf_sfml/Mouse.hpp"

#include <SFML/Graphics.hpp>
#include <vector>
class SeedSlot;
class SeedScreen : public Screen
{
    public:
        SeedScreen(Game* game,GameData* data);
        ~SeedScreen();

        virtual void draw(sf::RenderWindow* window, sf::Time delta);
        virtual void update(sf::Time delta);


    private:
        std::vector<SeedSlot*> _drawSeeds;
        GameData* _data;
};

// this is an internal class of seed screen , so no point declaring outside of here.

class SeedSlot  // defines a slot in the seed screen, to draw the seed and the number of seeds of that type
{
    public:
        SeedSlot(Game* game, Seed* seed, int count);
        ~SeedSlot();
        Game* _game;
        Seed* _seed;
        int _count;
        sf::Vector2i _position;
        void updateValues();
        void draw(sf::RenderWindow* window, sf::Time delta,bool selected = false);

        bool containsIn(sf::Vector2f position); 
    private:
        sf::Rect<float> _containBound;
        sf::Sprite _iconSprite;
        sf::Text   _countText;
        sf::RectangleShape  _border;
};

#endif

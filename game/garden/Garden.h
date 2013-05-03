#ifndef _GAME_GARDEN_GARDEN_H_
#define _GAME_GARDEN_GARDEN_H_

#include <SFML/Graphics.hpp>

#include <vector>
class Pixel;
class GardenEvent;
class Game;
class Garden
{
    public:
        Garden(Game* game);
        ~Garden();

        bool inRange(int row , int col);
        Pixel* pixelAt(int row, int col);

        /*
         * A turn in the garden goes as a follow.
         * 1) All Seeds will grow one turn. At the same time, update their color composition.
         * 2) All Pixel will check if they are matured.
         * 3) Mi
         */

        std::vector<GardenEvent*> doOneTurn();
        void update(sf::Time &delta);
        void draw(sf::RenderWindow* window,sf::Time &delta); // assuming the view has been set before drawing.

    protected:
        std::vector<std::vector<Pixel*> > _pixels;
    
        Game* _game;

};
#endif

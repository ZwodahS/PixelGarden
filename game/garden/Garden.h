#ifndef _GAME_GARDEN_GARDEN_H_
#define _GAME_GARDEN_GARDEN_H_

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
    protected:
        std::vector<std::vector<Pixel*> > _pixels;
    
        Game* _game;

};
#endif

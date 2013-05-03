#ifndef _GAME_SCREEN_H_
#define _GAME_SCREEN_H_

class Screen
{
    public:
        Screen(Game* game);
        ~Screen();
        
        draw(sf::RenderWindow* window, sf::Time delta);
        update(sf::Time delta);
    private:


}
#endif

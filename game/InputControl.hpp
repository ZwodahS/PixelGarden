#ifndef _GAME_INPUTCONTROL_H_
#define _GAME_INPUTCONTROL_H_
#include <SFML/Window.hpp>
#include "../zf_common/InputState.hpp"
class InputControl
{
    public:

        InputState open_inv;
        InputState processOneTurn;
        InputControl();
        ~InputControl();

        void update();

    private:
        sf::Keyboard::Key _openSeedScreen;
        sf::Keyboard::Key _oneTurn;
};
#endif

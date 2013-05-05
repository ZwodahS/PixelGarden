#ifndef _ZF_SFML_MOUSE_H_
#define _ZF_SFML_MOUSE_H_

#include "../zf_common/InputState.hpp"

#include <SFML/Graphics.hpp>
namespace zf
{
    // There is no need to keep track of the position , since you can get it directly.
    struct Mouse
    {
        InputState _left;
        InputState _right;
        InputState _middle;

        void update(sf::Time delta);
        sf::Vector2i getPosition();
        sf::Vector2i getPosition(sf::Window &window);
        sf::Vector2f getWorldPosition(sf::RenderWindow &window);
        Mouse();
        ~Mouse();
    };
}
#endif

#include "InputControl.hpp"
#include "../zf_common/f_inputs.hpp"
InputControl::InputControl()
{
    this->_openSeedScreen = sf::Keyboard::I;
    this->_oneTurn = sf::Keyboard::Space;
}
InputControl::~InputControl()
{
}
void InputControl::update()
{
    zf_inputs::processKey(open_inv, sf::Keyboard::isKeyPressed(_openSeedScreen));
    zf_inputs::processKey(processOneTurn, sf::Keyboard::isKeyPressed(_oneTurn));    
}

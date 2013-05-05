#include "Mouse.hpp"
#include "../zf_common/f_inputs.hpp"

zf::Mouse::Mouse()
{
}

zf::Mouse::~Mouse()
{
}

void zf::Mouse::update(sf::Time delta)
{
    zf_inputs::processKey(_left, sf::Mouse::isButtonPressed(sf::Mouse::Left));
    zf_inputs::processKey(_right, sf::Mouse::isButtonPressed(sf::Mouse::Right));
    zf_inputs::processKey(_middle, sf::Mouse::isButtonPressed(sf::Mouse::Middle));
}

sf::Vector2i zf::Mouse::getPosition()
{
    return sf::Mouse::getPosition();
}

sf::Vector2i zf::Mouse::getPosition(sf::Window &window)
{
    return sf::Mouse::getPosition(window);
}

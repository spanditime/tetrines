#ifndef GUI_AUXILIARY_AUXILIARY_HPP
#define GUI_AUXILIARY_AUXILIARY_HPP

#include <SFML/Graphics/Image.hpp>

namespace aux{
    sf::Image smooth(const sf::Image &target);
    float evaluateLength(float x,float y);
}

#endif // !GUI_AUXILIARY_AUXILIARY_HPP
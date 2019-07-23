#ifndef STYLE_HPP
#define STYLE_HPP

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace Style{
    extern const sf::Color background_button_color;
    extern const sf::Color fill_button_color;
    extern const sf::Color background_color;

    sf::FloatRect resizeHandler16_9(float w,float h);
}

#endif // !STYLE_HPP
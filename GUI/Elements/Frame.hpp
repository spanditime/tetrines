#ifndef GUI_ELEMENTS_FRAME_HPP
#define GUI_ELEMENTS_FRAME_HPP

#include <SFML/Graphics/Color.hpp>

#include "GUI/GuiElement.hpp"


class Frame : public GuiElement{
public:
    Frame();
    
    void setBackgroundColor(sf::Color color);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update(float collapsed_time);

    bool canHaveFocus() const;

    sf::Color background_color;
};

#endif // !GUI_ELEMENTS_FRAME_HPP
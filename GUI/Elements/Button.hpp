#ifndef GUI_ELEMENTS_BUTTON_HPP
#define GUI_ELEMENTS_BUTTON_HPP

#include <SFML/Graphics/Color.hpp>
#include <string>

#include "GUI/GuiElement.hpp"


class Button : public GuiElement{
public:
    Button();
    
    static void default_button_action();

    void setAction(void(*action)() = default_button_action);
    void setBackgroundColor(sf::Color color);
    void setFillColor(sf::Color color);
    void setText(std::string str);
    void setCircleMoveSpeed(float speed=3.f);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update(float collapsed_time);

    bool handleMouse();
    void onHover();
    void onMouseLeave();
    void mouseMoved(float x, float y);
    bool mousePressed(float x, float y,sf::Mouse::Button b);
    bool mouseReleased(float x, float y,sf::Mouse::Button b);

    bool canHaveFocus() const;
    void onFocus();
    void lostFocus();
    void onReturn();

    sf::Color background_color, fill_color;
    sf::Vector2f circle;
    sf::Vector2f circle_m;
    float circle_m_speed;
    float circle_size;
    bool entered;
    void (*button_action)();
};

#endif // !GUI_ELEMENTS_BUTTON_HPP
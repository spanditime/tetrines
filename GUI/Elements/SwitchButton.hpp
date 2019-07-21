#ifndef GUI_ELEMENTS_SWITCHBUTTON_HPP
#define GUI_ELEMENTS_SWITCHBUTTON_HPP

#include <SFML/Graphics/Color.hpp>
#include <string>

#include "GUI/GuiElement.hpp"


class SwitchButton : public GuiElement{
public:
    SwitchButton();

    void setOnColor(sf::Color color=sf::Color::Green);
    void setOffColor(sf::Color color=sf::Color::Red);
    void setFillColor(sf::Color color);
    void setText(std::string str);
    void displayStateInText(bool b=true);
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
    bool leftArrow();
    bool rightArrow();

    sf::Color on_color;
    sf::Color off_color;
    sf::Color fill_color;
    sf::Vector2f circle;
    sf::Vector2f circle_m;
    float circle_m_speed;
    float circle_size;
    bool entered, state;
    float state_m;
};

#endif // !GUI_ELEMENTS_SWITCHBUTTON_HPP
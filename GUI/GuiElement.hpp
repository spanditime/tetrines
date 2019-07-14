#ifndef GUI_GUIELEMENT_HPP
#define GUI_GUIELEMENT_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Mouse.hpp>

class GUI;

class GuiElement{
public:
    void setPosX(float value, bool in_percent = false);
    float getPosX() const;
    bool getPosXp() const;
    void setPosY(float value, bool in_percent = false);
    float getPosY() const;
    bool getPosYp() const;
    void setWidth(float value, bool in_percent = false);
    float getWidth() const;
    bool getWidthp() const;
    void setHeight(float value, bool in_percent = false);
    float getHeight() const;
    bool getHeightp() const;
    bool isFocused();

private:
    friend class GUI;
    void _draw(const sf::FloatRect& p,sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void draw(const sf::FloatRect& p,sf::RenderTarget& target, sf::RenderStates states) const = 0;
    virtual void update(float collapsed_time)=0;
    
    bool mouseHovered();
    
    virtual void onHover();
    virtual void onMouseLeave();
    virtual void mouseMoved(const sf::FloatRect& r,float x, float y);
    virtual void mousePressed(const sf::FloatRect& r,float x, float y,sf::Mouse::Button b);
    virtual bool mouseReleased(const sf::FloatRect& r,float x, float y,sf::Mouse::Button b);

    virtual bool canHaveFocus() const;
    virtual void onFocus();
    virtual void lostFocus();
    virtual void onReturn();
    virtual bool leftArrow();
    virtual bool rightArrow();
    virtual void plus();
    virtual void minus();
    virtual void mouseWheelScrolled(float d);

    bool focused;
    bool hover;
    bool mouse_pressed;

    GUI *parrent;

    sf::FloatRect getRect(const sf::FloatRect& p) const;

    sf::FloatRect rect;
    sf::Rect<bool> in_perc;
};

#endif // !GUI_GUIELEMENT_HPP
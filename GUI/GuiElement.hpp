#ifndef GUI_GUIELEMENT_HPP
#define GUI_GUIELEMENT_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>

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
    bool mouseHovered();
    bool isFocused();
    bool isMousePressed();

private:
    friend class GUI;
    void _draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
    virtual void update(float collapsed_time)=0;
    
protected:
    sf::FloatRect getRect() const;
    
private:
    virtual bool autoHandling() const;
    virtual void handleEvent(sf::Event e);
    virtual void onHover();
    virtual void onMouseLeave();
    virtual void mouseMoved(float x, float y);
    virtual bool mousePressed(float x, float y,sf::Mouse::Button b);
    virtual bool mouseReleased(float x, float y,sf::Mouse::Button b);

    virtual bool canHaveFocus() const;
    virtual void onFocus();
    virtual void lostFocus();
    virtual void onReturn();
    virtual bool leftArrow();
    virtual bool rightArrow();
    virtual void plus();
    virtual void minus();
    virtual void mouseWheelScrolled(float d);

    bool focused = false;
    bool hover = false;
    bool mouse_pressed = false;

    GUI *parrent = nullptr;

    sf::FloatRect evaluateRect(const sf::FloatRect& p);

    sf::FloatRect rect;
    sf::FloatRect eval;
    sf::Rect<bool> in_perc;
};

#endif // !GUI_GUIELEMENT_HPP
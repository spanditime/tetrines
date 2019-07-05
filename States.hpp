#ifndef STATES_HPP
#define STATES_HPP

#include <SFML/Graphics/Drawable.hpp>
#include "Event/EventListener.hpp"

enum class State{
    Menu = 0,
    Settings = 1,
    Game = 2,
    Pause = 3
};

class GameState : public sf::Drawable, public EventListener{
protected:
    void setState(State s) const;
    void setPreviousState() const;
    State getState() const;
    State getPreviousState() const;
    float getWindowWidth() const;
    float getWindowHeight() const;
private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const=0;
    virtual void handleEvent(sf::Event event);
};

#endif // !STATES_HPP
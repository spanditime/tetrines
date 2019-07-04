#ifndef EVENTLISTENER_HPP
#define EVENTLISTENER_HPP

#include <SFML/Window/Event.hpp>

class EventListener{
public:
    EventListener();
private:
    friend class EventDispatcher;
    virtual void handleEvent(sf::Event event) = 0;
};

#endif // !EVENTLISTENER_HPP
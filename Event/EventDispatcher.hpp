#ifndef EVENTDISPATCHER_HPP
#define EVENTDISPATCHER_HPP

#include "EventListener.hpp"

class EventDispatcher{
// singleton pattern
private:
    EventDispatcher();
    ~EventDispatcher();
    static EventDispatcher *_instance;

public:
    static EventDispatcher *getInstance();
// !singleton pattern

private:
    friend class EventListener;
    void addListener(EventListener *l);

    friend class Game;
    void dispatch(sf::Event event);
};

#endif // !EVENTDISPATCHER_HPP
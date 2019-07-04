#include "EventDispatcher.hpp"
#include <vector>

EventDispatcher *EventDispatcher::_instance = nullptr;

EventDispatcher::EventDispatcher(){

}

EventDispatcher::~EventDispatcher(){

}

EventDispatcher *EventDispatcher::getInstance(){
    if(EventDispatcher::_instance == nullptr)
        EventDispatcher::_instance = new EventDispatcher();
    return EventDispatcher::_instance;
}

std::vector<EventListener*> listeners;

void EventDispatcher::addListener(EventListener *l){
    listeners.push_back(l);
}

void EventDispatcher::dispatch(sf::Event event){
    for(auto listener : listeners){
        listener->handleEvent(event);
    }
}
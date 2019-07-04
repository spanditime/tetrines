#include "EventListener.hpp"
#include "EventDispatcher.hpp"

EventListener::EventListener(){
    EventDispatcher::getInstance()->addListener(this);
}
#include "States.hpp"
#include "Game.hpp"

void GameState::setState(State s) const{
    Game::getInstance()->setState(s);
}

void GameState::setPreviousState() const{
    Game::getInstance()->setPreviousState();
}

State GameState::getState() const{
    return Game::getInstance()->getState();
}

State GameState::getPreviousState() const{
    return Game::getInstance()->getPreviousState();
}
#include "Tetris.hpp"


Tetris *Tetris::_instance = nullptr;

Tetris::Tetris(){

}

Tetris::~Tetris(){

}

Tetris *Tetris::getInstance(){
    if(Tetris::_instance == nullptr)
        Tetris::_instance = new Tetris();
    return Tetris::_instance;
}

void Tetris::update(float collapsed_time){
    if(getState()!=State::Game)
        return ;
    
}

void Tetris::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    if(getState()!=State::Game)
        return ;
    
}

void Tetris::handleEvent(sf::Event event){
    if(getState()!=State::Game)
        return ;
    switch(event.type){
        case sf::Event::EventType::KeyPressed:
            break;
    }
}
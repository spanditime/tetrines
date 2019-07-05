#include "Game.hpp"
#include "Tetris.hpp"

#include <fstream>


Game *Game::_instance = nullptr;

Game::Game()
    :window(sf::VideoMode(600,800),"TETRINES",sf::Style::Default)
    ,gamestate(State::Game)
    ,prevgamestate(State::Menu)
    ,background_color(sf::Color::Green)
{
    std::ifstream file;
    file.open("icon.png");
    if(file){
        sf::Image icon;
        if(icon.loadFromFile("icon.png"))
            window.setIcon(32,32,icon.getPixelsPtr());
        file.close();
    }
    window.setKeyRepeatEnabled(false);
}

Game::~Game(){

}

Game *Game::getInstance(){
    if(Game::_instance == nullptr)
        Game::_instance = new Game();
    return Game::_instance;
}

void Game::gameloop(){
    clock.restart();
    running = true;
    while(running){
        update();
        window.clear(background_color);
        window.draw(*this);
        running = false;
    }
}

void Game::restart(){

}

void Game::update(){
    float collapsed_time = clock.getElapsedTime().asSeconds();
    clock.restart();
    switch(gamestate){
        case State::Menu:

            break;
        case State::Game:
            
            break;
        case State::Pause:
            
            break;
        case State::Settings:

            break;
    }
}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    switch(gamestate){
        case State::Menu:

            break;
        case State::Game:
            
            break;
        case State::Pause:
            
            break;
        case State::Settings:

            break;
    }
}

void Game::setState(State s){
    prevgamestate = gamestate;
    gamestate = s;
}

void Game::setPreviousState(){
    State b = gamestate;
    gamestate = prevgamestate;
    prevgamestate = b; 
}

State Game::getState(){
    return gamestate;
}

State Game::getPreviousState(){
    return prevgamestate;
}


#include "Game.hpp"
#include "Game/Tetris.hpp"
#include "Game/Menu.hpp"
#include "Event/EventDispatcher.hpp"

#include <fstream>

#define WINHEIGHT 800
#define WINWIDTH 600

Game *Game::_instance = nullptr;

Game::Game()
    :window(sf::VideoMode(WINWIDTH,WINHEIGHT),"TETRINES",sf::Style::Default)
    ,gamestate(State::Menu)
    ,prevgamestate(State::Menu)
    ,background_color(sf::Color::Green)
{
    window_width = WINWIDTH;
    window_height = WINHEIGHT;
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
    running = true;
    sf::Event e;
    clock.restart();
    while(running){
        while(window.pollEvent(e)){
            if(e.type == sf::Event::EventType::Closed){
                window.close();
                running = false;
                break;
            } else{
                if(e.type == sf::Event::EventType::Resized){
                    sf::View v;
                    v.setCenter(e.size.width/2,e.size.height/2);
                    v.setSize(e.size.width,e.size.height);
                    window.setView(v);
                }
                EventDispatcher::getInstance()->dispatch(e);
            }
        }
        update();
        window.clear(background_color);
        window.draw(*Game::getInstance());
        window.display();
        //running = false;
    }
}

void Game::restart(){

}

void Game::update(){
    float collapsed_time = clock.getElapsedTime().asSeconds();
    clock.restart();
    switch(gamestate){
        case State::Menu:
            Menu::getInstance()->update(collapsed_time);
            break;
        case State::Game:
            Tetris::getInstance()->update(collapsed_time);
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
            target.draw(*Menu::getInstance());
            break;
        case State::Game:
            target.draw(*Tetris::getInstance());
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

float Game::getWindowWidth(){
    return window_width;
}

float Game::getWindowHeight(){
    return window_height;
}

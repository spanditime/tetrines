#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include "States.hpp"

class Game : public sf::Drawable{
// Concrette class pattern
private:
    Game();
    ~Game();
    static Game *_instance;

public:
    static Game *getInstance();
// !Concrette class pattern

public:
    void gameloop();
    void restart();
    void update();


private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    
    //
    friend class GameState; 
    void setState(State s);
    void setPreviousState();
    State getState();
    State getPreviousState();
    float getWindowWidth();
    float getWindowHeight();


    bool running;
    sf::Clock clock;
    State gamestate;
    State prevgamestate;
    

    sf::RenderWindow window;
    float window_width,window_height;
    sf::Color background_color;
};

#endif // !GAME_HPP
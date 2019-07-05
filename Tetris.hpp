#ifndef TETRIS_HPP
#define TETRIS_HPP

#include "States.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include "Event/EventListener.hpp"

class Tetris : public sf::Drawable,public EventListener,public GameState{
// singleton pattern
private:
    Tetris();
    ~Tetris();
    static Tetris *_instance;

public:
    static Tetris *getInstance();
// !singleton pattern

    void update(float collapsed_time);

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    void handleEvent(sf::Event event);
    
};

#endif // !TETRIS_HPP
#ifndef MENU_HPP
#define MENU_HPP

#include "GUI/Gui.hpp"
#include "GUI/Elements/Button.hpp"
#include "States.hpp"

class Menu : public GameState{
// singleton pattern
private:
    Menu();
    ~Menu();
    static Menu *_instance;

public:
    static Menu *getInstance();
// !singleton pattern
    
    void update(float collapsed_time);

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    GUI gui;
    Button button;
};

#endif // !MENU_HPP
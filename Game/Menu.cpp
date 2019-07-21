#include "Menu.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

Menu *Menu::_instance = nullptr;

Menu::Menu()
    :gui(getWindowWidth(),getWindowHeight())
{
    button.setPosX(10);
    button.setPosY(10);
    button.setWidth(200);
    button.setHeight(50);
    button.setBackgroundColor(sf::Color::Blue);
    button.setFillColor(sf::Color::Red);
    gui.addElement(&button);
}

Menu::~Menu(){

}

Menu *Menu::getInstance(){
    if(Menu::_instance == nullptr)
        Menu::_instance = new Menu();
    return Menu::_instance;
}

void Menu::update(float collapsed_time){
    gui.update(collapsed_time);
}

void Menu::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    target.draw(gui);
}

#ifndef GUI_GUI_HPP
#define GUI_GUI_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <vector>

#include "Event/EventListener.hpp"
#include "GuiElement.hpp"

class GUI : public sf::Drawable , public EventListener {
public:
    GUI(float w,float h);
    GUI(float w,float h,sf::FloatRect (*resize_handler)(float w,float h));

    void update(float collapsed_time);
    
    void addElement(GuiElement* e);
    void deleteElement(GuiElement* e);

private:    
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void handleEvent(sf::Event e);

    sf::FloatRect field;
    sf::FloatRect (*resize_handler)(float w,float h);

    std::vector<GuiElement*> childs;
    GuiElement* focused;
};

#endif // !GUI_GUI_HPP
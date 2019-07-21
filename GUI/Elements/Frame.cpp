#include "Frame.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

Frame::Frame(){

}

void Frame::setBackgroundColor(sf::Color color){
    background_color = color;
}

void Frame::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    sf::FloatRect r = getRect();
    sf::RectangleShape rect;
    rect.setFillColor(background_color);
    rect.setPosition(sf::Vector2f(r.left,r.top));
    rect.setSize(sf::Vector2f(r.width,r.height));
    target.draw(rect);
}

void Frame::update(float collapsed_time){

}

bool Frame::canHaveFocus() const{
    return false;
}
#include "Button.hpp"

#include <cmath>
#include <SFML/Graphics.hpp>

#include "GUI/Auxiliary/Auxiliary.hpp"

void Button::default_button_action(){}

Button::Button(){
    button_action = default_button_action;
    circle_size = 0;
    circle = {0.5f,0.5f};
    circle_m = {0.5f,0.5f};
    circle_m_speed = 3.f;
    entered = false;
}

void Button::setAction(void(*action)()){
    if(action != nullptr)
        button_action = action;
    else if(button_action == nullptr)
        button_action = default_button_action;
}

void Button::setBackgroundColor(sf::Color color){
    background_color = color;
}

void Button::setFillColor(sf::Color color){
    fill_color = color;
}

void Button::setText(std::string str){
    
}

void Button::setCircleMoveSpeed(float speed){
    if(speed>0.1f)
        circle_m_speed = speed;
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    sf::FloatRect r = getRect();
    sf::RectangleShape rect;
    rect.setPosition(sf::Vector2f(r.left,r.top));
    rect.setSize(sf::Vector2f(r.width,r.height));
    rect.setFillColor(background_color);
    sf::RenderTexture t;
    if(circle_size>0&&circle.x>=0&&circle.x<=1&&circle.y>=0&&circle.y<=1){
        t.create((int)(r.width+0.5f),(int)(r.height+0.5f));
        float R=aux::evaluateLength(r.width,r.height)/2.f*circle_size;
        sf::CircleShape shape(R,60L);
        shape.setPosition(r.width*circle.x-R,r.height*(1-circle.y)-R);
        shape.setFillColor(fill_color);
        t.clear(background_color);
        t.draw(shape);
        rect.setTexture(&t.getTexture());
        target.draw(rect);
    }else 
        target.draw(rect);
}

void Button::update(float collapsed_time){
    circle.x += (circle_m.x-circle.x)*collapsed_time*circle_m_speed;
    circle.y += (circle_m.y-circle.y)*collapsed_time*circle_m_speed;
    if((isMousePressed()||entered)&&circle_size>=0.5f&&circle_size<2.f){
        circle_size = std::sqrt((circle_size-0.5f)/1.5f);
        circle_size += (collapsed_time*2.f);
        circle_size *= circle_size * 1.5f;
        circle_size += 0.5f;
        if(circle_size>=2.f){
            button_action();
            entered = false;
        }
    }else if((isFocused()||mouseHovered()||isMousePressed()||entered)&&circle_size<0.5f){
        circle_size = std::sqrt(circle_size*2)+collapsed_time*2;
        if(circle_size>=1.f){
            circle_size = 0.5f;
        }else{
            circle_size *= circle_size / 2.f;
        }
    }else if((!(isMousePressed()||entered))&&circle_size>0.5f){
        circle_size = std::sqrt((circle_size-0.5f)/1.5f);
        circle_size -= (collapsed_time*4.f);
        if(circle_size<=0)
            circle_size = 0.5f;
        else{
            circle_size *= circle_size * 1.5f;
            circle_size += 0.5f;
        }
    } else if((!(isFocused()||mouseHovered()||isMousePressed()||entered))&&circle_size>0.0f){
        circle_size = std::sqrt(circle_size*2)-collapsed_time*4;
        if(circle_size<=0.f){
            circle_size = 0.0f;
            circle_m.x = 0.5f;
            circle_m.y = 0.5f;
        }else{
            circle_size *= circle_size / 2.f;
        }
    }
}

void Button::onHover(){

}

void Button::onMouseLeave(){
    if(isFocused()){
        circle_m.x = 0.5f;
        circle_m.y = 0.5f;
    }
}

void Button::mouseMoved(float x, float y){
    sf::FloatRect r = getRect();
    circle_m.x = (x - r.left) / r.width;
    circle_m.y = (y - r.top) / r.height;
}

bool Button::mousePressed(float x, float y,sf::Mouse::Button b){
    sf::FloatRect r = getRect();
    circle_m.x = (x - r.left) / r.width;
    circle_m.y = (y - r.top) / r.height;
    if(b == sf::Mouse::Left){
        entered = true;
        return true;
    }
    return false;
}

bool Button::mouseReleased(float x, float y,sf::Mouse::Button b){
    sf::FloatRect r = getRect();
    if(r.left>=x&&r.left+r.width<=x&&r.top>=y&&r.top+r.height<=y){
        circle_m.x = (x - r.left) / r.width;
        circle_m.y = (y - r.top) / r.height;
    }
    if(b == sf::Mouse::Left || !entered)
        return false;
    return true;
}

bool Button::canHaveFocus() const{
    return true;
}

void Button::onFocus(){
    if(!mouseHovered()){
        circle_m.x = 0.5f;
        circle_m.y = 0.5f;
    }
}

void Button::lostFocus(){

}

void Button::onReturn(){
    entered = true;
}
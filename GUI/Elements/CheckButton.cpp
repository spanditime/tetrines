#include "CheckButton.hpp"

#include <cmath>
#include <SFML/Graphics.hpp>

#include "GUI/Auxiliary/Auxiliary.hpp"

CheckButton::CheckButton(){
    circle_size = 0;
    circle = {0.5f,0.5f};
    circle_m = {0.5f,0.5f};
    circle_m_speed = 3.f;
    entered = false;
    state = false;
}

void CheckButton::setOnColor(sf::Color color){
    on_color = color;
}

void CheckButton::setOffColor(sf::Color color){
    off_color = color;
}

void CheckButton::setFillColor(sf::Color color){
    fill_color = color;
}

void CheckButton::setText(std::string str){
    
}

void CheckButton::setCircleMoveSpeed(float speed){
    if(speed>0.1f)
        circle_m_speed = speed;
}

void CheckButton::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    sf::FloatRect r = getRect();
    sf::RectangleShape rect;
    rect.setPosition(sf::Vector2f(r.left,r.top));
    rect.setSize(sf::Vector2f(r.width,r.height));
    sf::Vertex vertices[8];
    vertices[0] = sf::Vertex(sf::Vector2f(0.f,r.height),on_color);
    vertices[1] = sf::Vertex(sf::Vector2f(0.f,0.f),on_color);
    vertices[6] = sf::Vertex(sf::Vector2f(r.width,r.height),off_color);
    vertices[7] = sf::Vertex(sf::Vector2f(r.width,0.f),off_color);
    if(!entered != !state){
        vertices[2] = sf::Vertex(sf::Vector2f(r.width/2.f,r.height),on_color);
        vertices[3] = sf::Vertex(sf::Vector2f(r.width/2.f,0.f),on_color);
        vertices[4] = sf::Vertex(sf::Vector2f(r.width-r.width/10.f,r.height),off_color);
        vertices[5] = sf::Vertex(sf::Vector2f(r.width-r.width/10.f,0.f),off_color);
    }else{
        vertices[2] = sf::Vertex(sf::Vector2f(r.width/10.f,r.height),on_color);
        vertices[3] = sf::Vertex(sf::Vector2f(r.width/10.f,0.f),on_color);
        vertices[4] = sf::Vertex(sf::Vector2f(r.width/2.f,r.height),off_color);
        vertices[5] = sf::Vertex(sf::Vector2f(r.width/2.f,0.f),off_color);
    }
    sf::RenderTexture t;
    t.create((int)(r.width+0.5f),(int)(r.height+0.5f));
    t.draw(vertices,8,sf::TriangleStrip);
    if(circle_size>0&&circle.x>=0&&circle.x<=1&&circle.y>=0&&circle.y<=1){
        float R=aux::evaluateLength(r.width,r.height)/2.f*circle_size;
        sf::CircleShape shape(R,60L);
        shape.setPosition(r.width*circle.x-R,r.height*(circle.y)-R);
        shape.setFillColor(fill_color);
        t.draw(shape);
    }
    t.display();
    rect.setTexture(&t.getTexture());
    target.draw(rect);
}

void CheckButton::update(float collapsed_time){
    if(isFocused() && !mouseHovered() && !entered){
        if(state)
            circle_m.x = 0.75f;
        else
            circle_m.x = 0.25f;
        circle_m.y = 0.5f;
    }

    circle.x += (circle_m.x-circle.x)*collapsed_time*circle_m_speed;
    circle.y += (circle_m.y-circle.y)*collapsed_time*circle_m_speed;
    if((isMousePressed()||entered)&&circle_size>=0.5f&&circle_size<2.f){
        circle_size = std::sqrt((circle_size-0.5f)/1.5f);
        circle_size += (collapsed_time*2.f);
        circle_size *= circle_size * 1.5f;
        circle_size += 0.5f;
        if(circle_size>=2.f){
            if(!mouseHovered()){
                if(state)
                    circle.x = 0.75f;
                else
                    circle.x = 0.25f;
                circle.y = 0.5f;
            }
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

void CheckButton::onHover(){

}

void CheckButton::onMouseLeave(){
    if(isFocused()){
        if(state)
            circle_m.x = 0.75f;
        else
            circle_m.x = 0.25f;
        circle_m.y = 0.5f;
    }
}

void CheckButton::mouseMoved(float x, float y){
    sf::FloatRect r = getRect();
    circle_m.x = (x - r.left) / r.width;
    circle_m.y = (y - r.top) / r.height;
}

bool CheckButton::mousePressed(float x, float y,sf::Mouse::Button b){
    sf::FloatRect r = getRect();
    circle_m.x = (x - r.left) / r.width;
    circle_m.y = (y - r.top) / r.height;
    if(b == sf::Mouse::Left){
        entered = true;
        state = !state;
        return true;
    }
    return false;
}

bool CheckButton::mouseReleased(float x, float y,sf::Mouse::Button b){
    sf::FloatRect r = getRect();
    if(r.left>=x&&r.left+r.width<=x&&r.top>=y&&r.top+r.height<=y){
        circle_m.x = (x - r.left) / r.width;
        circle_m.y = (y - r.top) / r.height;
    }
    if(b == sf::Mouse::Left || !entered)
        return false;
    return true;
}

bool CheckButton::canHaveFocus() const{
    return true;
}

void CheckButton::onFocus(){
    if(!mouseHovered()){
        if(state)
            circle_m.x = 0.75f;
        else
            circle_m.x = 0.25f;
        circle_m.y = 0.5f;
    }
}

void CheckButton::lostFocus(){

}

void CheckButton::onReturn(){
    if(!entered){
        entered = true;
        state = !state;
    }
}

bool CheckButton::leftArrow(){
    if(entered)
        return true;
    if(state){
        entered = true;
        state = false;
        return true;
    }
    return false;
}

bool CheckButton::rightArrow(){
    if(entered)
        return true;
    if(!state){
        entered = true;
        state = true;
        return true;
    }
    return false;
}
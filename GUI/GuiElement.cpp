#include "GuiElement.hpp"


void GuiElement::setPosX(float value, bool in_percent){
    rect.left = value;
    in_perc.left = in_percent;
}

float GuiElement::getPosX() const{
    return rect.left;
}
bool GuiElement::getPosXp() const{
    return in_perc.left;
}

void GuiElement::setPosY(float value, bool in_percent){
    rect.top = value;
    in_perc.top = in_percent;
}

float GuiElement::getPosY() const{
    return rect.top;
}
bool GuiElement::getPosYp() const{
    return in_perc.top;
}

void GuiElement::setWidth(float value, bool in_percent){
    rect.width = value;
    in_perc.width = in_percent;
}

float GuiElement::getWidth() const{
    return rect.width;
}
bool GuiElement::getWidthp() const{
    return in_perc.width;
}

void GuiElement::setHeight(float value, bool in_percent){
    rect.height = value;
    in_perc.height = in_percent;
}

float GuiElement::getHeight() const{
    return rect.height;
}
bool GuiElement::getHeightp() const{
    return in_perc.height;
}

void GuiElement::_draw(const sf::FloatRect& p,sf::RenderTarget& target, sf::RenderStates states) const{
    draw(getRect(p),target,states);
}


sf::FloatRect GuiElement::getRect(const sf::FloatRect& p) const{
    sf::FloatRect out = rect;
    if(in_perc.left){
        out.left = (p.left/100.f)*rect.left;
    }
    if(in_perc.top){
        out.top = (p.top/100.f)*rect.top;
    }
    if(in_perc.width){
        out.width = (p.width/100.f)*rect.width;
    }
    if(in_perc.height){
        out.height = (p.height/100.f)*rect.height;
    }
    return out;
}

bool GuiElement::mouseHovered(){
    return hover;
}

void GuiElement::onHover(){}
void GuiElement::onMouseLeave(){}
void GuiElement::mouseMoved(const sf::FloatRect& r,float x, float y){}
void GuiElement::mousePressed(const sf::FloatRect& r,float x, float y,sf::Mouse::Button b){}
bool GuiElement::mouseReleased(const sf::FloatRect& r,float x, float y,sf::Mouse::Button b){return false;}
bool GuiElement::canHaveFocus() const{return false;}
void GuiElement::onFocus(){}
void GuiElement::lostFocus(){}
void GuiElement::onReturn(){}
bool GuiElement::leftArrow(){return false;}
bool GuiElement::rightArrow(){return false;}
void GuiElement::plus(){}
void GuiElement::minus(){}
void GuiElement::mouseWheelScrolled(float d){}
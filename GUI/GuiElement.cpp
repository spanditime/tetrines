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

void GuiElement::_draw(sf::RenderTarget& target, sf::RenderStates states) const{
    draw(target,states);
}


sf::FloatRect GuiElement::evaluateRect(const sf::FloatRect& p){
    eval = rect;
    if(in_perc.left){
        eval.left = (rect.left/100.f)*p.width;
    }
    if(in_perc.top){
        eval.top = (rect.top/100.f)*p.height;
    }
    if(in_perc.width){
        eval.width = (rect.width/100.f)*p.width;
    }
    if(in_perc.height){
        eval.height = (rect.height/100.f)*p.height;
    }
    return eval;
}

bool GuiElement::mouseHovered(){
    return hover;
}

bool GuiElement::isFocused(){
    return focused;
}

bool GuiElement::isMousePressed(){
    return mouse_pressed;
}

sf::FloatRect GuiElement::getRect() const{
    return eval;
}
bool GuiElement::autoHandling() const{return false;}
void GuiElement::handleEvent(sf::Event e){}
void GuiElement::onHover(){}
void GuiElement::onMouseLeave(){}
void GuiElement::mouseMoved(float x, float y){}
bool GuiElement::mousePressed(float x, float y,sf::Mouse::Button b){return false;}
bool GuiElement::mouseReleased(float x, float y,sf::Mouse::Button b){return false;}
bool GuiElement::canHaveFocus() const{return false;}
void GuiElement::onFocus(){}
void GuiElement::lostFocus(){}
void GuiElement::onReturn(){}
bool GuiElement::leftArrow(){return false;}
bool GuiElement::rightArrow(){return false;}
void GuiElement::plus(){}
void GuiElement::minus(){}
void GuiElement::mouseWheelScrolled(float d){}
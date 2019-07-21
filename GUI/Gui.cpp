#include "Gui.hpp"

sf::FloatRect defaultResizeHandlerForGUI(float w,float h){
    return sf::FloatRect(0,0,w,h);
}

GUI::GUI(float w,float h){
    resize_handler = defaultResizeHandlerForGUI;
    field = resize_handler(w,h);
    focused = nullptr;
}

GUI::GUI(float w,float h,sf::FloatRect (*resize_handler)(float w,float h)){
    resize_handler = resize_handler;
    field = resize_handler(w,h);
}

void GUI::update(float collapsed_time){
    for(auto element : childs){
        element->update(collapsed_time);
    }
}

void GUI::addElement(GuiElement* e){
    if(e == nullptr)
        return;
    std::vector<GuiElement*>::iterator it = std::find(childs.begin(), childs.end(), e);
    if(it != childs.end())
        return;
    if(e->parrent != nullptr){
        e->parrent->deleteElement(e);
    }
    e->parrent = this;
    e->evaluateRect(field);
    childs.push_back(e);
}

void GUI::deleteElement(GuiElement* e){
    if(e == nullptr)
        return;
    std::vector<GuiElement*>::iterator it = std::find(childs.begin(), childs.end(), e);
    if(it != childs.end()){
        if(e == focused){
            focused->focused = false;
            focused->lostFocus();
            focused = nullptr;
        }   
        childs.erase(it);
        e->parrent = nullptr;
    }
}

void GUI::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    for(auto element : childs){
        element->_draw(target,states);
    }
}

void GUI::handleEvent(sf::Event e){
    if(e.type != sf::Event::EventType::Resized)
        for(auto element : childs){
            if(element->autoHandling()){
                element->handleEvent(e);
            }
        }
    bool res=false;
    switch(e.type){
    case sf::Event::EventType::Resized:
        field = resize_handler(e.size.width,e.size.height);
        for(auto element : childs){
            element->evaluateRect(field);
        }
        break;
    case sf::Event::EventType::MouseMoved:
        for(auto element : childs){
            sf::FloatRect r = element->getRect();
            r.left = e.mouseMove.x - r.left;
            r.top = e.mouseMove.y - r.top;
            if(r.left<=r.width&&r.left>=0&&r.top<=r.height&&r.top>=0&&element->handleMouse()){
                if(!element->hover){
                    element->hover = true;
                    element->onHover();
                }
                element->mouseMoved(e.mouseMove.x,e.mouseMove.y);
                if(focused != nullptr && focused != element){
                    focused->focused = false;
                    focused->lostFocus();
                    focused = nullptr;
                }
            } else if(element->hover){
                element->hover = false;
                element->onMouseLeave();
            }
        }
        break;
    case sf::Event::EventType::MouseButtonPressed:
        res=false;
        for(auto element : childs){
            if(res |= element->hover){
                element->mouse_pressed = element->mousePressed(e.mouseButton.x,e.mouseButton.y,e.mouseButton.button);
                if(element != focused && focused != nullptr){
                    focused->focused = false;
                    focused->lostFocus();
                    focused = nullptr;
                }else
                    break;
            }
        }
        if(!res && focused != nullptr){
            focused->focused = false;
            focused->lostFocus();
            focused = nullptr;
        }
        break;
    case sf::Event::EventType::MouseButtonReleased:
        for(auto element : childs){
            if(element->mouse_pressed){
                element->mouse_pressed = element->mouseReleased(e.mouseButton.x,e.mouseButton.y,e.mouseButton.button);
                break;
            }
        }
        break;
    case sf::Event::EventType::MouseWheelScrolled:
        for(auto element : childs){
            if(element->hover && !element->mouse_pressed){
                element->mouseWheelScrolled(e.mouseWheelScroll.delta);
            }
        }
        break;
    case sf::Event::EventType::MouseLeft:
        for(auto element : childs){
            if(element->hover){
                element->hover = false;
            }
        }
        break;
    case sf::Event::EventType::LostFocus:
        if(focused != nullptr){
            focused->focused = false;
            focused->lostFocus();
            focused = nullptr;
        }
        break;
    case sf::Event::EventType::KeyPressed:
        std::vector<GuiElement*>::iterator it;
        if(focused != nullptr){
            it = std::find(childs.begin(),childs.end(),focused);
        } else {
            it = childs.end();
        }

        if(it != childs.end()){
            switch(e.key.code){
            case sf::Keyboard::Key::Left:
                if((*it)->leftArrow())
                    break;
            case sf::Keyboard::Key::Up:
            case sf::Keyboard::Key::PageUp:
                while(it != childs.begin()){
                    it--;
                    if((*it)->canHaveFocus()){
                        if(focused->hover){
                            focused->hover = false;
                            focused->onMouseLeave();
                        }
                        focused->focused = false;
                        focused->lostFocus();
                        focused = (*it);
                        focused->focused = true;
                        focused->onFocus();
                        break;
                    }
                }
                break;
            case sf::Keyboard::Key::Home:
                for(auto f = childs.begin();f != it;f++){
                    if((*f)->canHaveFocus()){
                        if(focused != nullptr){
                            if(focused->hover){
                                focused->hover = false;
                                focused->onMouseLeave();
                            }
                            focused->focused = false;
                            focused->lostFocus();
                            focused = nullptr;
                        }
                        focused = *f;
                        focused->focused = true;
                        focused->onFocus();
                        break;
                    }
                }
                break;

            case sf::Keyboard::Key::Right:
                if((*it)->rightArrow())
                    break;
            case sf::Keyboard::Key::Down:
            case sf::Keyboard::Key::PageDown:
                it++;
                while(it != childs.end()){
                    if((*it)->canHaveFocus()){
                        if(focused->hover){
                            focused->hover = false;
                            focused->onMouseLeave();
                        }
                        focused->focused = false;
                        focused->lostFocus();
                        focused = (*it);
                        focused->focused = true;
                        focused->onFocus();
                        break;
                    }
                    it++;
                }
                break;
            case sf::Keyboard::Key::End:
                for(auto f = childs.end();;){
                    f--;
                    if(f == it)
                        break;
                    if((*f)->canHaveFocus()){
                        if(focused != nullptr){
                            if(focused->hover){
                                focused->hover = false;
                                focused->onMouseLeave();
                            }
                            focused->focused = false;
                            focused->lostFocus();
                            focused = nullptr;
                        }
                        focused = *f;
                        focused->focused = true;
                        focused->onFocus();
                        break;
                    }
                }
                break;

            case sf::Keyboard::Key::Return:
                focused->onReturn();
                break;
            
            case sf::Keyboard::Key::Add:
                focused->plus();
                break;
            case sf::Keyboard::Key::Subtract:
                focused->minus();
                break;
            }
        } else {
            res = false;
            switch(e.key.code){
            case sf::Keyboard::Key::Down:
            case sf::Keyboard::Key::PageDown:
            case sf::Keyboard::Key::Right:
                for(auto element : childs){
                    if(element->hover&&element->canHaveFocus()){
                        element->focused = true;
                        focused = element;
                        element->onFocus();
                        if(e.key.code == sf::Keyboard::Key::Left)
                            element->leftArrow();
                        res = true;
                        break;
                    }
                }
                if(res)
                    break;
            case sf::Keyboard::Key::Home:
                it = childs.begin();
                while(it != childs.end()){
                    if((*it)->canHaveFocus()){
                        for(auto element : childs){
                            if(element->hover){
                                element->hover = false;
                                element->onMouseLeave();
                            }
                        }
                        (*it)->focused = true;
                        (*it)->onFocus();
                        focused = (*it);
                        break;
                    }
                    it++;
                }
                break;

            case sf::Keyboard::Key::Up:
            case sf::Keyboard::Key::PageUp:
            case sf::Keyboard::Key::Left:
                for(auto element : childs){
                    if(element->hover&&element->canHaveFocus()){
                        element->focused = true;
                        focused = element;
                        element->onFocus();
                        if(e.key.code == sf::Keyboard::Key::Right)
                            element->rightArrow();
                        res = true;
                        break;
                    }
                }
                if(res)
                    break;
            case sf::Keyboard::Key::End:
                it = childs.end();
                while(it != childs.begin()){
                    it--;
                    if((*it)->canHaveFocus()){
                        for(auto element : childs){
                            if(element->hover){
                                element->hover = false;
                                element->onMouseLeave();
                            }
                        }
                        (*it)->focused = true;
                        (*it)->onFocus();
                        focused = (*it);
                        break;
                    }
                }
                break;
            }
        }
        break;
    }
}
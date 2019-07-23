#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace Style{

    const sf::Color background_button_color=sf::Color();
    const sf::Color fill_button_color=sf::Color();
    const sf::Color background_color=sf::Color();

    sf::FloatRect resizeHandler16_9(float w,float h){
        float ratio = 16.f/9.f;
        sf::FloatRect r;
        if(ratio<=(w/h)){
            r.height = h;
            r.top = 0.f;
            r.width = h * ratio;
            r.left = (w - r.width)/2.f;
        }else{
            r.width = w;
            r.left = 0.f;
            r.height = w / ratio;
            r.top = (h - r.height)/2.f;
        }
        return r;
    }
}   
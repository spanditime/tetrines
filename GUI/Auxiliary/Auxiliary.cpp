#include "Auxiliary.hpp"

#include <cmath>

sf::Image aux::smooth(const sf::Image &target){
    sf::Image img;
    const sf::Uint8 *src;
    sf::Uint8 *dst;
    src = target.getPixelsPtr();
    unsigned int width=target.getSize().x,height=target.getSize().y;
    dst = new sf::Uint8[width*height*4];

    for(unsigned int y = 0;y<height;y++)
        for(unsigned int x = 0;x<width;x++){
            unsigned int summ[4];
            for(int i=0;i<4;i++)
                summ[i] = 0; 
            for(int dx=(x==0)?(0):(-1);dx<=(x==width-1)?(0):(1);dx++)
                for(int dy=(y==0)?(0):(-1);dy<=(y==height-1)?(0):(1);dy++)
                    for(int i=0;i<4;i++)
                        summ[i] += src[(y+dy)*width*4+(x+dx)*4+i];
            if((x==0&&(y==0||y==height-1))||(y==0&&(x==0||x==width-1))){
                for(int i=0;i<4;i++)
                    summ[i] /=4;
            } else if(x==0||y==0||x==width-1||y==height-1){
                for(int i=0;i<4;i++)
                    summ[i] /=6;
            } else {
                for(int i=0;i<4;i++)
                    summ[i] /=9;
            }
            for(int i=0;i<4;i++){
                dst[y*width*4+x*4+i] = summ[i];
            }
        }
    img.create(target.getSize().x,target.getSize().y,dst);
    return img;
}

float aux::evaluateLength(float x,float y){
    return std::sqrt(x*x+y*y);
}
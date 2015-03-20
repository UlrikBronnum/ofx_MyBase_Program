#ifndef OFX_COLOR_H_INCLUDED
#define OFX_COLOR_H_INCLUDED

#include "ofMain.h"

class ofx_Color
{
    public:
        //----------------- Constructor/Deconstructor -----------------------
        ofx_Color(){}

        ofx_Color(unsigned char red,unsigned char green, unsigned char blue){
            r = red;
            g = green;
            b = blue;
        }

        ofx_Color(unsigned char color){
            r = color;
            g = color;
            b = color;
        }

        void set_color(unsigned char red,unsigned char green, unsigned char blue){
            r = red;
            g = green;
            b = blue;
        }

        void set_color(unsigned char color){
            r = color;
            g = color;
            b = color;
        }

        ofx_Color inverse_color(){
            ofx_Color tmp;
            tmp.set_color(255 - r, 255 - g , 255 - b);
            return tmp;
        }

        unsigned char r,g,b;

};

#endif // OFX_COLOR_H_INCLUDED



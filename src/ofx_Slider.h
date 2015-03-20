#ifndef OFX_SLIDER_H
#define OFX_SLIDER_H

#include "ofx_Color.h"
#include "ofx_Placement.h"

#include "ofMain.h"

class ofx_Slider : public ofx_Placement
{
    public:
        ofx_Slider(): ofx_Placement(){}
        virtual ~ofx_Slider(){}

        //------------------------- Setup -----------------------------------
        void setup (int width,int height, float u_limit , float l_limit, string slider_title);
        void setup (int width,int height, float u_limit , float l_limit);
        void setup (int width,int height, string slider_title);
        void setup (int width,int height);
        //------------------------- Draws -----------------------------------
        virtual void draw (int x , int y , ofx_Color color);
        virtual void draw (int x , int y , unsigned char color);
        //------------------------ Mouse Interaction ------------------------
        virtual bool mouse_drag (int x , int y);
        //------------------------ Value Calculations ------------------------
        virtual float Slider_Procentage (){
            float val = 0.0f;
            if(Vertical()){
                val = 1 - (slider_value/float(object_height - (Nob_Small_Side () + 5) ) ) ;
            }else{
                val = (slider_value/float(object_width - (Nob_Small_Side () + 5) ) ) ;
            }

            if(val > 0.99){
                val = 1.0f;
            }else if(val < 0.01){
                val = 0.0f;
            }
            return val;
        }
        virtual float Slider_Value (){return (upper_limit - lower_limit) * Slider_Procentage () + lower_limit;}

        int Nob_Small_Side (){
            if(Vertical() ){
                return object_height/25;
            }else{
                return object_width/25;
            }
        }
        int Nob_Large_Side (){
            if(!Vertical() ){
                return object_height/1.2;
            }else{
                return object_width/1.2;
            }
        }

        string Title(){
            return title;
        }

    protected:

        bool Vertical(){
            if(object_height > object_width){
                return true;
            }else{
                return false;
            }
        }

        string title;

        float upper_limit;
        float lower_limit;

        bool show_limit;

        float slider_value;

    private:
};

#endif // OFX_SLIDER_H

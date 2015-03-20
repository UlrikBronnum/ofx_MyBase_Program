#ifndef OFX_SMENU_H
#define OFX_SMENU_H

#include "ofx_Color.h"
#include "ofx_Placement.h"
#include "ofx_Slider.h"

#include "ofMain.h"

class ofx_SMenu : public ofx_Placement
{
    public:
        ofx_SMenu(){}
        virtual ~ofx_SMenu(){}

        //------------------------- Setup -----------------------------------
        void setup (int slider_width,int slider_height)
        {
            object_width = slider_width;
            object_height = slider_height;
            send_data = false;
        }

        //------------------------- Add Slider ------------------------------
        void add_slider(string slider_label,float upper_limit, float lower_limit){
            ofx_Slider* tmp = new ofx_Slider();
            tmp->setup(object_width,object_height,upper_limit, lower_limit,slider_label);
            _Menu_Sliders.push_back(tmp);
        }

        //------------------------- Add Slider ------------------------------
        void reset_slider(){
            _Menu_Sliders.clear();
        }
        //------------------------- Draws -----------------------------------
        void draw (int x , int y , ofx_Color color);
        void draw (int x , int y , unsigned char color);

        //------------------------ Mouse Interaction ------------------------
        bool mouse_drag (int x , int y);


        string Filter_Settings(){
            stringstream tmp ;
            string strtmp = "";

            if(send_data){
                for(int i = 0; i < _Menu_Sliders.size() ; i ++){
                    tmp << _Menu_Sliders[i]->Title() << "=" << _Menu_Sliders[i]->Slider_Value() ;
                    if(i < _Menu_Sliders.size()-1) tmp << "-";
                }
                tmp >> strtmp;
            }
            send_data = false;
            return strtmp;
        }


        vector<ofx_Slider*> _Menu_Sliders;

    protected:

        bool send_data;



    private:
};

#endif // OFX_SMENU_H

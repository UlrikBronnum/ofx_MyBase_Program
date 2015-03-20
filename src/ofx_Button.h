#ifndef OFX_BUTTON_H
#define OFX_BUTTON_H

#include "ofx_Color.h"
#include "ofx_Placement.h"

#include "ofMain.h"

class ofx_Button : public ofx_Placement
{
    public:
        //----------------- Constructor/Deconstructor -----------------------
        ofx_Button() : ofx_Placement(){}
        virtual ~ofx_Button(){}

        //------------------------- Setup -----------------------------------
        void setup (int width,int height,string new_label,bool is_switch);

        //------------------------- Draws -----------------------------------
        void draw (int x , int y , ofx_Color color);
        void draw (int x , int y , unsigned char color);

        //------------------------ Mouse Interaction ------------------------
        bool mouse_click (int x , int y);
        void mouse_hover (int x , int y);

        //--------------------------- Get / Set -----------------------------
        bool Button_State(){return button_state;}

        void Button_State(bool state){button_state = state;}

        string Return_Label(){return label;}

        void Set_Label(string new_label){
            label = new_label;
        }

        //-------------------------------------------------------------------


    protected:


        string label;

        bool is_switch;

        bool button_state;

        bool mouse_hover_over_button;


};

#endif // OFX_BUTTON_H

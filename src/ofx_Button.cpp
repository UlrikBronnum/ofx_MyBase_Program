#include "ofx_Button.h"


//-------------------------------------------------------------------
//------------------------- Setup -----------------------------------
//-------------------------------------------------------------------
void ofx_Button::setup (int button_width,int button_height,string new_label,bool button_is_switch){

    object_width = button_width;
    object_height = button_height;

    label = new_label;

    is_switch = button_is_switch;
    button_state = false;
    mouse_hover_over_button = false;
}

//-------------------------------------------------------------------
//------------------------- Draws -----------------------------------
//-------------------------------------------------------------------
void ofx_Button::draw (int x , int y, ofx_Color color){
    object_x = x;
    object_y = y;

    ofSetColor(255 - color.r , 255 - color.g , 255 - color.b);
    ofRect( x , y , object_width , object_height );

    if(button_state){
        ofSetColor(color.r - color.r/5,color.g - color.g/5, color.b - color.b/5);
    }else if(mouse_hover_over_button){
        ofSetColor(color.r - color.r/10,color.g - color.g/10, color.b - color.b/10);
    }else{
        ofSetColor(color.r,color.g,color.b);
    }
    ofRect( x + 1, y + 1, object_width - 2, object_height - 2);

    ofSetColor(255 - color.r,255 - color.g,255 - color.b);
    int char_count = object_width / 9;
	stringstream button_label;
	if(label.size() > char_count){
        button_label  << label.substr(0,char_count) << ".." << endl;
	}else{
        button_label  << label.substr(0,char_count) << endl;
	}

	ofDrawBitmapString(button_label.str(),object_x + object_height/2 - 2,  object_y + object_height/2+5);
}
//-------------------------------------------------------------------
void ofx_Button::draw (int x , int y, unsigned char color){

    object_x = x;
    object_y = y;

    ofSetColor(255 - color);
    ofRect( x , y , object_width , object_height );

    if(button_state){
        ofSetColor(color - color/5);
    }else if(mouse_hover_over_button){
        ofSetColor(color - color/10);
    }else{
        ofSetColor(color);
    }

    ofRect( x + 1, y + 1, object_width - 2, object_height - 2);

    ofSetColor(255 - color);
	int char_count = object_width / 9;
	stringstream button_label;
	if(label.size() > char_count){
        button_label  << label.substr(0,char_count) << "..." << endl;
	}else{
        button_label  << label.substr(0,char_count) << endl;
	}

	ofDrawBitmapString(button_label.str(),object_x + object_height/2 - 2,  object_y + object_height/2+5);

}
//-------------------------------------------------------------------
//------------------------ Mouse Interaction ------------------------
//-------------------------------------------------------------------
bool ofx_Button::mouse_click (int x , int y){
    if(Mouse_Over_Button( x , y)){
        if(is_switch){
            if(button_state){
                button_state = false;
            }else{
                button_state = true;
            }
        }else {
            button_state = true;
        }
        return true;
    }
    return false;
}

//-------------------------------------------------------------------
void ofx_Button::mouse_hover (int x , int y){
    if(Mouse_Over_Button( x , y)){
        mouse_hover_over_button = true;
    }else{
        mouse_hover_over_button = false;
    }

    if(!is_switch){
        button_state = false;
    }
}

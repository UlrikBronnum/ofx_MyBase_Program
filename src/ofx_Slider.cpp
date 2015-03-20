#include "ofx_Slider.h"


//-------------------------------------------------------------------
//------------------------- Setup -----------------------------------
//-------------------------------------------------------------------
void ofx_Slider::setup (int width,int height, float u_limit , float l_limit, string slider_title){
    object_width = width;
    object_height = height;

    upper_limit = u_limit;
    lower_limit = l_limit;

    title = slider_title;

    show_limit = true;
}
void ofx_Slider::setup (int width,int height, float u_limit , float l_limit){
    object_width = width;
    object_height = height;

    upper_limit = u_limit;
    lower_limit = l_limit;

    show_limit = true;

}
void ofx_Slider::setup (int width,int height , string slider_title){
    object_width = width;
    object_height = height;
    title = slider_title;

    show_limit = false;
}

void ofx_Slider::setup (int width,int height){
    object_width = width;
    object_height = height;

    show_limit = false;
}

//-------------------------------------------------------------------
//------------------------- Draws -----------------------------------
//-------------------------------------------------------------------
void ofx_Slider::draw (int x , int y , ofx_Color color){

    ofSetColor(255);

    object_x = x;
    object_y = y;

    // Draw background rectangle
    ofSetColor(color.r,color.g,color.b);
    ofRect( x , y , object_width, object_height);

    int n_x = 0; int n_y = 0;  int n_w = 0;  int n_h = 0;

    // Vertical slider draw
    if(Vertical()){
        // Draw slider line
        n_x = x + object_width/2;
        n_y = y + Nob_Small_Side () / 2;
        n_w = x + object_width/2;
        n_h = y + object_height - Nob_Small_Side () + 2;
        ofSetColor(0);
        ofLine( n_x, n_y, n_w, n_h );
        // Draw slider nob rectangle
        n_w =  object_width/1.2;
        n_h =  Nob_Small_Side ();
        n_x =  x + object_width/2 - n_w/2;
        n_y =  y + 2;
        ofSetColor(color.r - color.r/2,color.g - color.g/2,color.b - color.b/2);
        ofRect( n_x , n_y  + slider_value, n_w , n_h);

        // Draw related strings
        ofSetColor(color.r,color.g,color.b);
        stringstream button_string;
        if(title != ""){
            // Title
            n_x = x - 6 * title.size()/2;
            n_y = y - n_h/2;
            button_string  << title << endl;
            ofDrawBitmapString(button_string.str(), n_x , n_y);
            button_string.str("");
            // Upper limit
            n_x = x + object_width + 4;
            n_y = y + object_height - Nob_Small_Side () + 4;
            button_string  << setprecision(4) << upper_limit << endl;
            ofDrawBitmapString(button_string.str(),n_x , n_y);
            button_string.str("");
            // Lower limit
            n_x = x + object_width + 4;
            n_y = y + (Nob_Small_Side () + 4);
            button_string  << setprecision(4) << lower_limit << endl;
            ofDrawBitmapString(button_string.str(), n_x , n_y);
        }

    // Horizontal slider draw
    }else{
        // Draw slider line
        n_x = x + Nob_Small_Side ();
        n_y = y + object_height/2;
        n_w = x + object_width - Nob_Small_Side ();
        n_h = y + object_height/2;
        ofSetColor(0);
        ofLine( n_x, n_y, n_w, n_h );
        // Draw slider nob rectangle
        n_w =  Nob_Small_Side ();
        n_h =  object_height/1.2;
        n_x =  x + 2;
        n_y =  y + object_height/2 - n_h/2;
        ofSetColor(color.r - color.r/2,color.g - color.g/2,color.b - color.b/2);
        ofRect( n_x  + slider_value, n_y , n_w , n_h);

        // Draw related strings
        ofSetColor(color.r,color.g,color.b);
        stringstream button_string;
        if(title != ""){
            // Title
            n_x = x + object_width/2 -  8 * title.size()/2;
            n_y = y - n_h/2;
            button_string  << title << endl;
            ofDrawBitmapString(button_string.str(), n_x , n_y);
            button_string.str("");
            // Upper limit
            n_x = x + object_width - 16;
            n_y = y + object_height + object_height/1.3;
            button_string  << setprecision(4) << upper_limit << endl;
            ofDrawBitmapString(button_string.str(),n_x , n_y);
            button_string.str("");
            // Lower limit
            n_x = x + Nob_Small_Side () - 4;
            n_y = y + object_height + object_height/1.3;
            button_string  << setprecision(4) << lower_limit << endl;
            ofDrawBitmapString(button_string.str(), n_x , n_y);
        }
    }
    ofSetColor(255);
}
void ofx_Slider::draw (int x , int y , unsigned char color){
    ofSetColor(255);
    object_x = x;
    object_y = y;

    // Draw background rectangle
    ofSetColor(color);
    ofRect( x , y , object_width, object_height);

    int n_x = 0; int n_y = 0;  int n_w = 0;  int n_h = 0;

    // Vertical slider draw
    if(Vertical()){
        // Draw slider line
        n_x = x + object_width/2;
        n_y = y + Nob_Small_Side () / 2;
        n_w = x + object_width/2;
        n_h = y + object_height - Nob_Small_Side () + 2;
        ofSetColor(0);
        ofLine( n_x, n_y, n_w, n_h );
        // Draw slider nob rectangle
        n_w =  object_width/1.2;
        n_h =  Nob_Small_Side ();
        n_x =  x + object_width/2 - n_w/2;
        n_y =  y + 2;
        ofSetColor(color - color/2);
        ofRect( n_x , n_y  + slider_value, n_w , n_h);

        // Draw related strings
        ofSetColor(color);
        stringstream button_string;
        if(title != ""){
            // Title
            n_x = x - 6 * title.size()/2;
            n_y = y - n_h/2;
            button_string  << title << endl;
            ofDrawBitmapString(button_string.str(), n_x , n_y);
            button_string.str("");
            // Upper limit
            n_x = x + object_width + 4;
            n_y = y + object_height - Nob_Small_Side () + 4;
            button_string  << setprecision(4) << upper_limit << endl;
            ofDrawBitmapString(button_string.str(),n_x , n_y);
            button_string.str("");
            // Lower limit
            n_x = x + object_width + 4;
            n_y = y + (Nob_Small_Side () + 4);
            button_string  << setprecision(4) << lower_limit << endl;
            ofDrawBitmapString(button_string.str(), n_x , n_y);
        }

    // Horizontal slider draw
    }else{
        // Draw slider line
        n_x = x + Nob_Small_Side ();
        n_y = y + object_height/2;
        n_w = x + object_width - Nob_Small_Side ();
        n_h = y + object_height/2;
        ofSetColor(0);
        ofLine( n_x, n_y, n_w, n_h );
        // Draw slider nob rectangle
        n_w =  Nob_Small_Side ();
        n_h =  object_height/1.2;
        n_x =  x + 2;
        n_y =  y + object_height/2 - n_h/2;
        ofSetColor(color - color/2);
        ofRect( n_x  + slider_value, n_y , n_w , n_h);

        // Draw related strings
        ofSetColor(color);
        stringstream button_string;
        if(title != ""){
            // Title
            n_x = x + object_width/2 -  8 * title.size()/2;
            n_y = y - n_h/2;
            button_string  << title << endl;
            ofDrawBitmapString(button_string.str(), n_x , n_y);
            button_string.str("");
            // Upper limit
            n_x = x + object_width - 16;
            n_y = y + object_height + object_height/1.3;
            button_string  << setprecision(4) << upper_limit << endl;
            ofDrawBitmapString(button_string.str(),n_x , n_y);
            button_string.str("");
            // Lower limit
            n_x = x + Nob_Small_Side () - 4;
            n_y = y + object_height + object_height/1.3;
            button_string  << setprecision(4) << lower_limit << endl;
            ofDrawBitmapString(button_string.str(), n_x , n_y);
        }
    }
    ofSetColor(255);
}
//-------------------------------------------------------------------
//------------------------ Mouse Interaction ------------------------
//-------------------------------------------------------------------
bool ofx_Slider::mouse_drag (int x , int y){

    // Vertical slider
    if(Vertical()){
        if(Mouse_Over_Button(x,y)){
            if(object_y + object_height - (Nob_Small_Side () + Nob_Small_Side ()/3)  > y ){
                slider_value = y - object_y  ;
                return true;
            }
        }
    // Horizontal slider
    }else{
        if(Mouse_Over_Button(x,y)){
            if(object_x + object_width - (Nob_Small_Side () + Nob_Small_Side ()/3) > x ){
                slider_value = x - object_x ;
                return true;
            }
        }
    }

    return false;
}

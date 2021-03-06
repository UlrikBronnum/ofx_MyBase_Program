#include "ofx_Menu.h"

//
//------------------------- Draws -----------------------------------
void ofx_Menu::draw (int x , int y , ofx_Color color, int window_w, int window_h){
    object_x = x;
    object_y = y;
    object_width = original_width;

    if(vertical){
        if( window_h < y + Height() ){
            menu_slider.setup(20,window_h - y );
            if(x < window_w/2){
                object_x = x + 20;
                menu_slider.draw(x,y,color);
            }else{
                object_x = x;
                menu_slider.draw(object_x + object_width,y,color);
            }
            object_width = original_width + 20;
            for(int i = 0 ; i < _Menu_Buttons.size() ; i ++){
                _Menu_Buttons[i]->draw(object_x ,object_y + object_height * i - (1 - menu_slider.Slider_Procentage() ) * (Height() - (window_h - object_y)) ,color);
            }

        }else{
            object_width = original_width;
            for(int i = 0 ; i < _Menu_Buttons.size() ; i ++){
                _Menu_Buttons[i]->draw(object_x,object_y + object_height * i,color);
            }
        }
    }else{
        if( window_w < x + Width() ){
            menu_slider.setup(window_w - x,20);
            if(y > window_h/2){
                menu_slider.draw(x,y + object_height ,color);
            }else{
                menu_slider.draw(x,y ,color);
                object_y = y + 20;
            }

            for(int i = 0 ; i < _Menu_Buttons.size() ; i ++){
                _Menu_Buttons[i]->draw(object_x + object_width * i - (menu_slider.Slider_Procentage() ) * (Width() - (window_w - object_x) ) ,object_y ,color);
            }
        }else{
            for(int i = 0 ; i < _Menu_Buttons.size() ; i ++){
                _Menu_Buttons[i]->draw(object_x + object_width * i ,object_y ,color);
            }
        }
    }
}
void ofx_Menu::draw (int x , int y , unsigned char color, int window_w, int window_h){
    object_x = x;
    object_y = y;
    object_width = original_width;

    if(vertical){
        if( window_h < y + Height() ){
            menu_slider.setup(20,window_h - y );
            if(x < window_w/2){
                object_x = x + 20;
                menu_slider.draw(x,y,color);
            }else{
                object_x = x;
                menu_slider.draw(object_x + original_width,y,color);
            }
            object_width = original_width + 20;
            for(int i = 0 ; i < _Menu_Buttons.size() ; i ++){
                _Menu_Buttons[i]->draw(object_x ,object_y + object_height * i - (1 - menu_slider.Slider_Procentage() ) * (Height() - (window_h - object_y)) ,color);
            }

        }else{
            object_width = original_width;
            for(int i = 0 ; i < _Menu_Buttons.size() ; i ++){
                _Menu_Buttons[i]->draw(object_x,object_y + object_height * i,color);
            }
        }
    }else{
        if( window_w < x + Width() ){
            menu_slider.setup(window_w - x,20);
            if(y > window_h/2){
                menu_slider.draw(x,y + object_height ,color);
            }else{
                menu_slider.draw(x,y ,color);
                object_y = y + 20;
            }

            for(int i = 0 ; i < _Menu_Buttons.size() ; i ++){
                _Menu_Buttons[i]->draw(object_x + object_width * i - (menu_slider.Slider_Procentage() ) * (Width() - (window_w - object_x) ) ,object_y ,color);
            }
        }else{
            for(int i = 0 ; i < _Menu_Buttons.size() ; i ++){
                _Menu_Buttons[i]->draw(object_x + object_width * i ,object_y ,color);
            }
        }
    }
}


//------------------------ Mouse Interaction ------------------------
bool ofx_Menu::mouse_click (int x , int y){
    int new_press = -1;
    if(!menu_slider.Mouse_Over_Button(x , y)){
        if(x > object_x && x < object_x + Width() &&
           y > object_y && y < object_y + Height() )
        {
            for(int i = 0 ; i < _Menu_Buttons.size() ; i ++){
                if(_Menu_Buttons[i]->mouse_click(x,y)){
                    new_press = i;
                }else{
                    _Menu_Buttons[i]->Button_State(false);
                }
            }
            if(new_press == menu_state){
                Reset_Menu();
                return false;
            }else {
                menu_state = new_press;
                return true;
            }
        }
    }else{
        return true;
    }
    return false;
}
void ofx_Menu::mouse_hover (int x , int y){
    for(int i = 0 ; i < _Menu_Buttons.size() ; i ++){
        _Menu_Buttons[i]->mouse_hover(x,y);
    }
}
bool ofx_Menu::mouse_drag (int x , int y){
    menu_slider.mouse_drag(x,y);
}


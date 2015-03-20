#include "ofx_SMenu.h"

//------------------------- Draws -----------------------------------
void ofx_SMenu::draw (int x , int y , ofx_Color color){
    for(int i = 0; i < _Menu_Sliders.size() ; i++){
        _Menu_Sliders[i]->draw(x,y + object_height * 3 * i,color);

    }
}
void ofx_SMenu::draw (int x , int y , unsigned char color){
    for(int i = 0; i < _Menu_Sliders.size() ; i++){
        _Menu_Sliders[i]->draw(x,y + object_height * 3 * i,color);
    }
}

//------------------------ Mouse Interaction ------------------------
bool ofx_SMenu::mouse_drag (int x , int y){
    for(int i = 0; i < _Menu_Sliders.size() ; i++){
        if(_Menu_Sliders[i]->mouse_drag(x,y)){
            send_data = true;
            return true;
        }
    }
    return false;
}

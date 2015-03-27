#include "ofx_MenuSub.h"


//------------------------- Setup -----------------------------------
void ofx_MenuSub::setup (int button_width,int button_height, vector<string> sub_titles)
{
    object_width = button_width;
    object_height = button_height;


    Menu_Main.setup(object_width,object_height,true,true);

    for(int i = 0; i < sub_titles.size() ; i++){
        Menu_Main.add_button(sub_titles[i],true);
        ofx_Menu* tmp = new ofx_Menu();
        tmp->setup(object_width,object_height,true,false);
        Menu_Subs.push_back(tmp);
    }
}

void ofx_MenuSub::setup (int button_width,int button_height,int sub_button_width,int sub_button_height){
    object_width = sub_button_width;
    object_height = sub_button_height;


    Menu_Main.setup( button_width, button_height,true,true);

}
void ofx_MenuSub::add_sub_menu (vector<string> sub_titles , bool is_a_switch,int index){
    if(index > -1 && index < Menu_Subs.size()){
        for(int i = 0; i < sub_titles.size() ; i++){
            Menu_Subs[index]->add_button(sub_titles[i],is_a_switch);
        }
    }
}
void ofx_MenuSub::add_sub_menu (vector<string> sub_titles , bool is_a_switch,int index, int button_width,int button_height){
    if(index > -1 && index < Menu_Subs.size()){
        for(int i = 0; i < sub_titles.size() ; i++){
            Menu_Subs[index]->add_button(sub_titles[i],is_a_switch,button_width,button_height);
        }
    }
}
void ofx_MenuSub::reset_sub_menu (vector<string> sub_titles, int index){
    Menu_Subs[index]->Reset_Menu(sub_titles);
}
int ofx_MenuSub::add_button (string  button_title ){
    Menu_Main.add_button(button_title,true);
    Menu_Main.Menu_State(-1);
    ofx_Menu* tmp = new ofx_Menu();
    tmp->setup(object_width,object_height,true,true);
    Menu_Subs.push_back(tmp);
    return Menu_Subs.size();
}

//------------------------- Draws -----------------------------------
void ofx_MenuSub::draw (int x , int y , ofx_Color color, int window_w, int window_h){
    int state = Menu_Main.Menu_State();
    if(state != -1 && state < Menu_Subs.size() ){
        if(window_w - object_width/2 < x + object_width){
            Menu_Subs[state]->draw(x - object_width,y + object_height * state ,color,window_w,window_h);
        }else{
            Menu_Subs[state]->draw(x + object_width,y + object_height * state ,color,window_w,window_h);
        }
    }
    Menu_Main.draw(x,y,color,window_w,window_h);

}
void ofx_MenuSub::draw (int x , int y , unsigned char color, int window_w, int window_h){
    int state = Menu_Main.Menu_State();
    if(state != -1 && state < Menu_Subs.size() ){
        if(window_w - object_width/2 < x + object_width){
            Menu_Subs[state]->draw(x - object_width,y + object_height * state ,color,window_w,window_h);
        }else{
            Menu_Subs[state]->draw(x + object_width,y + object_height * state ,color,window_w,window_h);
        }
    }
    Menu_Main.draw(x,y,color,window_w,window_h);
}

//------------------------ Mouse Interaction ------------------------
bool ofx_MenuSub::mouse_click (int x , int y){
    int state = Menu_Main.Menu_State();

    if(state != -1 && state < Menu_Subs.size() ){
        if(Menu_Subs[state]->Button_Count() != 0){
            if(Menu_Subs[state]->mouse_click(x,y) ){
                int s_state = Menu_Subs[state]->Menu_State();
                return true;
            }else{
                if(Menu_Main.mouse_click(x,y)){return true;}
            }
        }else{
            if(Menu_Main.mouse_click(x,y)){return true;}
        }
    }else{
        if(Menu_Main.mouse_click(x,y)){return true;}
    }

    return false;
}
void ofx_MenuSub::mouse_hover (int x , int y){
    int state = Menu_Main.Menu_State();
    if(state != -1 && state < Menu_Subs.size() ){
        Menu_Subs[state]->mouse_hover(x,y);
    }
    Menu_Main.mouse_hover(x,y);
}
bool ofx_MenuSub::mouse_drag (int x , int y){
    int state = Menu_Main.Menu_State();
    if(state != -1 && state < Menu_Subs.size() ){
        Menu_Subs[state]->mouse_drag(x,y);
    }
    Menu_Main.mouse_drag(x,y);
}

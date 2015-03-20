#include "ofx_App.h"

//------------------------- Draws -----------------------------------
void ofx_App::draw (ofx_Color color, int window_w, int window_h){
    Program_Menu.draw(0,0,color,window_w,window_h);
    if(program_state != -1 && program_state < _Program_Menu_Content.size()  ){
        if(menu_state == -1){
            _Program_Menu_Content[program_state]->draw(object_width*program_state,object_height,color,window_w,window_h);
        }else if(sub_state == -1 && _Program_Menu_Content[program_state]->Sub_Button_Count() != 0){
            _Program_Menu_Content[program_state]->draw(object_width*program_state,object_height,color,window_w,window_h);
        }
    }
}
void ofx_App::draw (unsigned char color, int window_w, int window_h){
    Program_Menu.draw(0,0,color,window_w,window_h);
    if(program_state != -1 && program_state < _Program_Menu_Content.size()){
        if(menu_state == -1){
            _Program_Menu_Content[program_state]->draw(object_width*program_state,object_height,color,window_w,window_h);
        }else if(menu_state != -1 && sub_state == -1 && _Program_Menu_Content[program_state]->Sub_Button_Count() != 0){
            _Program_Menu_Content[program_state]->draw(object_width*program_state,object_height,color,window_w,window_h);
        }
    }
}
//------------------------ Mouse Interaction ------------------------
bool ofx_App::mouse_click (int x , int y){

    bool change = false;
    if(program_string != ""){
        program_state = -1;
        menu_state = -1;
        sub_state = -1;
        program_string = "";
    }else if(program_state != -1){
        if(menu_state != -1 && _Program_Menu_Content[program_state]->Sub_Button_Count() == 0){
            program_state = -1;
            menu_state = -1;
            sub_state = -1;
            program_string = "";
            _Program_Menu_Content[program_state]->Reset_Menu();
            Program_Menu.Reset_Menu();
        }
    }

    if(program_state != -1 && program_state < _Program_Menu_Content.size()){

        _Program_Menu_Content[program_state]->mouse_click(x,y);

        int sub_s = _Program_Menu_Content[program_state]->Menu_Sub_State();
        int menu_s = _Program_Menu_Content[program_state]->Menu_Main_State();

        if(sub_state != sub_s ){ change = true; } sub_state = sub_s;

        if(menu_state != menu_s ){ change = true; } menu_state = menu_s;


    }
    if(change){
        if(program_state != -1){
            if(sub_state == -1 && menu_state == -1 ){
                Program_Menu.Reset_Menu();
                _Program_Menu_Content[program_state]->Reset_Menu();
                Program_Menu.mouse_click(x,y);
                program_state = Program_Menu.Menu_State();
            }else if(sub_state != -1 && program_state != -1){
                program_string = _Program_Menu_Content[program_state]->Button_String();
                Program_Menu.Reset_Menu();
                _Program_Menu_Content[program_state]->Reset_Menu();
            }else if(menu_state != -1 && _Program_Menu_Content[program_state]->Sub_Button_Count() == 0){
                program_string = _Program_Menu_Content[program_state]->Button_String();
                _Program_Menu_Content[program_state]->Reset_Menu();
                Program_Menu.Reset_Menu();
            }
        }
    }
    else{
        Program_Menu.mouse_click(x,y);
        int new_state = Program_Menu.Menu_State();
        if(program_state != new_state){
            change = true;
        }

        if(new_state == -1 && change){
            if (program_state != -1 ){
                Program_Menu.Reset_Menu();
                _Program_Menu_Content[program_state]->Reset_Menu();
                program_state = -1;
                menu_state = -1;
                sub_state = -1;
            }
        }else if (new_state == -1) {
            if (program_state != -1 ){
                Program_Menu.Reset_Menu();
                _Program_Menu_Content[program_state]->Reset_Menu();
                program_state = -1;
                menu_state = -1;
                sub_state = -1;
            }
        }else{
            program_state = new_state;
        }
    }
    return change;
}
void ofx_App::mouse_hover (int x , int y){
    Program_Menu.mouse_hover(x,y);
    if(program_state != -1 && program_state < _Program_Menu_Content.size()){
        _Program_Menu_Content[program_state]->mouse_hover(x,y);
    }
}
void ofx_App::mouse_drag (int x , int y){
    Program_Menu.mouse_drag(x,y);
}

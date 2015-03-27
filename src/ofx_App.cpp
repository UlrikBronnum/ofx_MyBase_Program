#include "ofx_App.h"

//------------------------- Draws -----------------------------------
void ofx_App::draw (ofx_Color color, int window_w, int window_h){

    if(program_state != -1 && program_state < _Program_Menu_Content.size()  ){
        if(show_subs){
            _Program_Menu_Content[program_state]->draw(object_width*program_state,object_height,color,window_w,window_h);
        }
    }
    Program_Menu.draw(0,0,color,window_w,window_h);
    ofSetColor(200);
    ofRect(Program_Menu.Width() + 1,1,window_w,23);
    ofSetColor(55);
    stringstream program_label;
    program_label  << program_version  << endl;
    ofDrawBitmapString(program_label.str(),window_w - window_w/8,18);
}
void ofx_App::draw (unsigned char color, int window_w, int window_h){

    if(program_state != -1 && program_state < _Program_Menu_Content.size()){
        if(show_subs){
            _Program_Menu_Content[program_state]->draw(object_width*program_state,object_height,color,window_w,window_h);
        }
    }
    Program_Menu.draw(0,0,color,window_w,window_h);
    ofSetColor(200);
    ofRect(Program_Menu.Width()+ 1,1,window_w,23);
    ofSetColor(55);
    stringstream program_label;
    program_label  << program_version  << endl;
    ofDrawBitmapString(program_label.str(),window_w - window_w/8,18);
}

//------------------------ Mouse Interaction ------------------------
bool ofx_App::mouse_click (int x , int y){

    bool change = false;


    if(program_state == -1){
        if(Program_Menu.mouse_click(x,y)){
            program_state = Program_Menu.Menu_State();
            program_string = Program_Menu.Button_String(program_state);
            change = true;
            show_subs = true;
            cout << "p -1 : true" << endl;
        }else{
            menu_state = -1;
            sub_state = -1;
            change = false;
            show_subs = false;
            cout << "p -1 : false" << endl;
        }
    }else{
        if(Program_Menu.mouse_click(x,y)){
            int new_program_state = Program_Menu.Menu_State();

            if(program_state != new_program_state ){
                _Program_Menu_Content[program_state]->Reset_Menu();
                menu_state = -1;
                sub_state = -1;
            }

            program_state = new_program_state;
            program_string = Program_Menu.Button_String(program_state);
            change = true;
            show_subs = true;
            cout << "p != -1 : true" << endl;
        }else{
            if(_Program_Menu_Content[program_state]->mouse_click(x,y)){
                if(menu_state == -1){
                    int new_menu_state = _Program_Menu_Content[program_state]->Menu_Main_State();
                    if(menu_state != new_menu_state ){
                        menu_state = new_menu_state;
                        program_string = _Program_Menu_Content[program_state]->Button_String();
                        change = true;
                        cout << "p != -1 : true -- m == -1 : true" << endl;
                    }else{
                        if(program_state != -1){_Program_Menu_Content[program_state]->Reset_Menu();  }
                        Program_Menu.Reset_Menu();
                        program_state = -1;
                        menu_state = -1;
                        sub_state = -1;
                        change = false;
                        cout << "p != -1 : true -- m == -1 : false" << endl;
                    }
                }else{
                    int new_menu_state = _Program_Menu_Content[program_state]->Menu_Main_State();
                    if(menu_state != new_menu_state ){
                        menu_state = new_menu_state;
                        program_string = _Program_Menu_Content[program_state]->Button_String();
                        change = true;
                        cout << "p != -1 : true -- m == -1 : true" << endl;
                    }

                    if(_Program_Menu_Content[program_state]->Sub_Button_Count() != 0){
                        int new_sub_state = _Program_Menu_Content[program_state]->Menu_Sub_State();
                        if(sub_state != new_sub_state ){
                            program_string = _Program_Menu_Content[program_state]->Button_String();
                            sub_state = new_sub_state;
                        }
                        change = true;
                        show_subs = true;
                    }

                }
            }else{
                if(program_state != -1){_Program_Menu_Content[program_state]->Reset_Menu();  }
                Program_Menu.Reset_Menu();
                program_state = -1;
                menu_state = -1;
                sub_state = -1;
                change = false;
            }
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
    if(program_state != -1 && program_state < _Program_Menu_Content.size()){
        _Program_Menu_Content[program_state]->mouse_drag(x,y);
    }
}

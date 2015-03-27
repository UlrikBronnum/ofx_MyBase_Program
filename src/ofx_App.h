#ifndef OFX_APP_H
#define OFX_APP_H

#include "ofMain.h"

#include "ofx_Button.h"
#include "ofx_Slider.h"
#include "ofx_Menu.h"
#include "ofx_SMenu.h"
#include "ofx_Loader.h"
#include "ofx_MenuSub.h"
#include "ofx_Placement.h"

#define program_version "version_1.0"

class ofx_App : public ofx_Loader , public ofx_Placement
{
    public:
        ofx_App() : ofx_Loader () , ofx_Placement () {}
        virtual ~ofx_App() {
            Delete_App_Content();
        }


        //------------------------- Setup -----------------------------------
        virtual void setup (){ }
        virtual void setup (ofx_MenuSub* menu){ }
        //------------------------- Draws -----------------------------------
        virtual void draw ( ofx_Color color, int window_w, int window_h);
        virtual void draw ( unsigned char color, int window_w, int window_h);

        //------------------------ Mouse Interaction ------------------------
        virtual bool mouse_click (int x , int y);
        virtual void mouse_hover (int x , int y);
        virtual void mouse_drag (int x , int y);

        //--------------------------- Get / Set -----------------------------

        int Program_State(){
            return  program_state;
        }

        int Menu_State(){
            return  menu_state;
        }

        int Sub_State(){
            return  sub_state;
        }


        string Program_String(){
            return  program_string;
        }

        string Get_Button_Label(){
            if(program_state != -1 && menu_state == -1 && sub_state == -1){
                return Program_Menu.Button_String(program_state);
            }else if(program_state != -1 && menu_state != -1 || sub_state != -1) {
                return _Program_Menu_Content[menu_state]->Button_String();
            }else {
                return "";
            }
        }
        string Get_Button_Labels_Sub(bool get_main,int pro_index,int main_index , int sub_index){
            string tmp;
            if(pro_index != -1 ){
                if(get_main){
                    tmp = _Program_Menu_Content[pro_index]->Get_Button_Label(true,main_index , sub_index);
                }else{
                    tmp = _Program_Menu_Content[pro_index]->Get_Button_Label(false,main_index , sub_index);
                }
            }
            return tmp;
        }
        void Set_Sub_Menu(ofx_MenuSub* newMenu){
            _Program_Menu_Content[2] = newMenu;
        }
        void Reset_Menu(){
            Program_Menu.Reset_Menu();
            if(program_state != -1){_Program_Menu_Content[program_state]->Reset_Menu();  }
            program_state = -1;
            menu_state = -1;
            sub_state = -1;
            program_string = "";
        }

        void Delete_App_Content(){
            for(int i = 0; i < _Program_Menu_Content.size() ; i++){
                delete _Program_Menu_Content[i];
            }
            _Program_Menu_Content.clear();
        }

    protected:


        ofx_Menu               Program_Menu;
        vector<ofx_MenuSub*>   _Program_Menu_Content;

        int                    program_state, menu_state, sub_state ;
        string                 program_string;

        bool                   show_subs;


        void create_program_menu(vector<string> titles){

            Program_Menu.setup(object_width,object_height,false,true);
            for(int i = 0; i < titles.size() ; i++){
                Program_Menu.add_button(titles[i],true);
                ofx_MenuSub* tmp = new ofx_MenuSub();
                tmp->setup(object_width*1.75,object_height,object_width*1.75,object_height);
                _Program_Menu_Content.push_back(tmp);
            }
        }
        void create_sub_menu(string title, vector<string> sub_titles , int index ){
            int button_index = _Program_Menu_Content[index]->add_button(title);
            _Program_Menu_Content[index]->add_sub_menu(sub_titles,false,button_index);
        }


    private:
};

#endif // OFX_APP_H

#ifndef OFX_MENU_H
#define OFX_MENU_H

#include "ofMain.h"

#include "ofx_Color.h"
#include "ofx_Placement.h"
#include "ofx_Button.h"
#include "ofx_Slider.h"



class ofx_Menu : public ofx_Placement
{
    public:
        //----------------- Constructor/Deconstructor -----------------------
        ofx_Menu() : ofx_Placement(){}
        virtual ~ofx_Menu(){
            Delete_Menu ();
        }

        //------------------------- Setup -----------------------------------
        void setup (int button_width,int button_height, bool vertical_menu , bool sub_menus_to_display)
        {
            object_width = button_width;
            object_height = button_height;
            original_width = button_width;
            original_height = button_height;

            vertical = vertical_menu;

            //has_sub_menus = sub_menus_to_display;

            menu_state = -1;
        }

        //------------------------- Add Button ------------------------------
        void add_button(string button_label,bool is_a_switch){
            ofx_Button* tmp = new ofx_Button();
            tmp->setup(object_width,object_height,button_label,is_a_switch);
            _Menu_Buttons.push_back(tmp);
        }
         void add_button(string button_label,bool is_a_switch,int button_width,int button_height){
            ofx_Button* tmp = new ofx_Button();
            tmp->setup(button_width,button_width,button_label,is_a_switch);
            _Menu_Buttons.push_back(tmp);
        }

        void add_button(ofx_Button*  button){
            _Menu_Buttons.push_back(button);
        }
        //------------------------- Draws -----------------------------------
        void draw (int x , int y , ofx_Color color, int window_w, int window_h);
        void draw (int x , int y , unsigned char color, int window_w, int window_h);

        //------------------------ Mouse Interaction ------------------------
        bool mouse_click (int x , int y);
        void mouse_hover (int x , int y);
        bool mouse_drag (int x , int y);
        //--------------------------- Get / Set -----------------------------
        int Width(){
            if(vertical){
                return object_width;
            }else{
                return object_width * _Menu_Buttons.size();
            }
        }
        int Height(){
            if(vertical){
                return object_height * _Menu_Buttons.size();
            }else{
                return object_height;
            }
        }
        //--------------------------------------------------------------
        void Reset_Menu(){
            for(int i = 0 ; i < _Menu_Buttons.size() ; i ++){
                _Menu_Buttons[i]->Button_State(false);
            }
            menu_state = -1;
        }

        void Reset_Menu(vector <string>  titles){
            Clear_Menu();
            for(int i = 0 ; i < titles.size() ; i ++){
                add_button(titles[i],true);
            }
            menu_state = -1;
        }
        //--------------------------------------------------------------
        void Clear_Menu(){
            for(int i = 0 ; i < _Menu_Buttons.size() ; i ++){
                delete _Menu_Buttons[i];
            }
            _Menu_Buttons.clear();
            menu_state = -1;
        }
        //--------------------------------------------------------------
        void delete_button(int index){
            _Menu_Buttons.erase(_Menu_Buttons.begin() + index);
            menu_state = -1;
        }
        //--------------------------------------------------------------
        int Menu_State(){
            return menu_state;
        }
        void Menu_State(int state){
            if(menu_state < _Menu_Buttons.size() && menu_state != -1){
                _Menu_Buttons[menu_state]->Button_State(false);
            }
            menu_state = state;
            if(menu_state < _Menu_Buttons.size() && menu_state != -1){
                _Menu_Buttons[menu_state]->Button_State(true);
            }
        }

        string Button_String(int index){
            if(index != -1 && index < _Menu_Buttons.size()){
               return _Menu_Buttons[index]->Return_Label();
            }
            return "";
        }
        string Button_String(){
            if(menu_state != -1 && menu_state < _Menu_Buttons.size()){
               return _Menu_Buttons[menu_state]->Return_Label();
            }
            return "";
        }
        void Set_Button_String(int index, string new_label){
            _Menu_Buttons[index]->Set_Label(new_label);
        }

        int Button_Count(){
            return _Menu_Buttons.size();
        }

        void Delete_Menu (){
            for(int i = 0; i < _Menu_Buttons.size() ; i++){
                delete _Menu_Buttons[i];
            }
            _Menu_Buttons.clear();
        }

    protected:
        vector<ofx_Button*> _Menu_Buttons;

        ofx_Slider          menu_slider;

        int                 menu_state;

        bool                vertical;

        int                 original_width;
        int                 original_height;

        //bool                has_sub_menus;

    private:
};

#endif // OFX_MENU_H

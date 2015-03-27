#ifndef OFX_MENUSUB_H
#define OFX_MENUSUB_H

#include "ofMain.h"

#include "ofx_Color.h"
#include "ofx_Placement.h"
#include "ofx_Button.h"
#include "ofx_Menu.h"

class ofx_MenuSub : public ofx_Placement
{
    public:
        ofx_MenuSub() : ofx_Placement(){}
        virtual ~ofx_MenuSub(){
            Delete_Sub_Menus ();
        }



        //------------------------- Setup -----------------------------------
        void setup (int button_width,int button_height, vector<string> sub_titles );
        //------------------------- Setup -----------------------------------
        void setup (int button_width,int button_height,int sub_button_width,int  sub_button_height);


        void add_sub_menu (vector<string> sub_titles , bool is_a_switch,int index);
        void add_sub_menu (vector<string> sub_titles , bool is_a_switch,int index,int button_width,int button_height);

        void set_sub_menu (ofx_Menu* tmp ,int index){
            ofx_Menu* old = Menu_Subs[index];
            Menu_Subs[index] = tmp;
            delete old;
        }
        int add_button (string  button_title);
        void reset_sub_menu (vector<string> sub_titles, int index);
        //--------------------------------------------------------------
        void delete_menu(int index){
            if(index != -1 && index < Menu_Subs.size()){
                Menu_Main.delete_button(index);
                Menu_Subs.erase(Menu_Subs.begin() + index);
            }
        }
        void clear_sub(){
            Menu_Subs.clear();
        }
        //------------------------- Draws -----------------------------------
        void draw (int x , int y , ofx_Color color, int window_w, int window_h);
        void draw (int x , int y , unsigned char color, int window_w, int window_h);

        //------------------------ Mouse Interaction ------------------------
        bool mouse_click (int x , int y);
        void mouse_hover (int x , int y);
        bool mouse_drag (int x , int y);

        ofx_Menu* Get_Main_Button(){
            return &Menu_Main;
        }

        int Menu_Main_State(){
            return Menu_Main.Menu_State();
        }
        int Menu_Sub_State(){
            int state = Menu_Main.Menu_State();
            if(state != -1 && state < Menu_Subs.size() ){
                return Menu_Subs[state]->Menu_State();
            }
            return -1;
        }

        void Reset_Menu(){
            Menu_Main.Reset_Menu();
            for(int i = 0 ; i < Menu_Subs.size() ; i++){
                Menu_Subs[i]->Reset_Menu();
            }
        }

        string Button_String(){
            int index = Menu_Main_State();
            if(index != -1){
                int indexsub = Menu_Sub_State();
                if(indexsub != -1){
                    return Menu_Subs[index]->Button_String(indexsub);
                }else{
                    return Menu_Main.Button_String();
                }
            }else{
                return "";
            }
        }

        string Get_Button_Label(bool get_main,int main_index , int sub_index){
            if(get_main){
                return Menu_Main.Button_String(main_index);
            }else {
                return Menu_Subs[main_index]->Button_String(sub_index);
            }
        }

        int Button_Count() {
            return Menu_Main.Button_Count();
        }
        int Sub_Button_Count() {
            int index = Menu_Main.Menu_State();
            if(index != -1 && index < Menu_Subs.size()){
                return Menu_Subs[index]->Button_Count();
            }
            return -1;
        }

        void Delete_Sub_Menus (){
            for(int i = 0; i < Menu_Subs.size() ; i++){
                delete Menu_Subs[i];
            }
            Menu_Subs.clear();
        }
    protected:

        ofx_Menu                Menu_Main;
        vector<ofx_Menu*>       Menu_Subs;


    private:
};

#endif // OFX_MENUSUB_H

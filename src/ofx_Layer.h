#ifndef OFX_LAYER_H
#define OFX_LAYER_H

#include "ofMain.h"

#include "ofx_Image.h"
#include "ofx_Filter.h"
#include "ofx_Point_Processing.h"
#include "ofx_Neighborhood_Processing.h"
#include "ofx_Greyscale.h"
#include "ofx_Normal_Map.h"

#include "ofx_Menu.h"
#include "ofx_MenuSub.h"

#include "ofx_Histogram.h"

class ofx_Layer
{
    public:
        ofx_Layer(){}
        virtual ~ofx_Layer(){}

        void setup(int image_width, int image_height, int button_width, int button_height, string layer_type);
        void reset(int image_width, int image_height);
        void update(unsigned char* input_image);
        void update();
        void draw(int x, int y , unsigned char color, int window_w, int window_h);

        //------------------------ Mouse Interaction ------------------------
        void mouse_click (int x , int y);
        void mouse_hover (int x , int y);
        void mouse_drag (int x , int y);

        void set_base_image(unsigned char* input_image){  }

        void add_Layer(string header , string filter, bool can_be_deleted);
        void delete_Layer(int index );
        void replace_Layer(int index , int type , string filter);
        void reset_Layers();

        ofx_MenuSub* Get_Program_Menu(){
            return &program_menu;
        }

        unsigned char* Get_Image(){
            if(Canvas_Storage.empty()){
                return Base_Image.image;
            }else{
                return Canvas_Storage[Canvas_Storage.size()-1]->image;
            }
        }

        int Get_Canvas_Count(){ return Canvas_Storage.size();}
        int Set_Menu_State(int menu_state){Layer_Buttons.Menu_State(menu_state);}

        bool                got_reference;
        bool                slider_drag;

        string              log_string;


        string Log_String(){
            stringstream tmp;
            string str = "";
            if(log_string != ""){
                str = log_string;
                log_string = "";
            }
            tmp << log_string << "\n";
            if(slider_drag){
                string filter_data = Canvas_Storage[Layer_Buttons.Menu_State()]->Filter_Slider_Settings() ;
                tmp << "layer_updated=" << Layer_Buttons.Menu_State() << "/" << Canvas_Storage[Layer_Buttons.Menu_State()]->title << "/";
                tmp << filter_data ;
                slider_drag = false;
                tmp >> str;
            }
            return str;
        }


    protected:

        void set_sub_menu(string filter_types)
        {
            int menus_added = 0;
            program_menu.setup(button_w,button_h,button_w,button_h);
            if(filter_types == "diffuse" || filter_types == "height"){
                ofx_Point_Processing tmp;
                program_menu.add_button(tmp.title);
                program_menu.add_sub_menu(tmp.possible_commands,false,menus_added);
                menus_added++;
            }
            /*if(filter_types == "height"){
                ofx_Greyscale tmp;
                program_menu.add_button(tmp.title);
                program_menu.add_sub_menu(tmp.possible_commands,false,menus_added);
                menus_added++;
            }*/
            if(filter_types == "diffuse" || filter_types == "normal" || filter_types == "height"){
                ofx_Neighborhood_Processing tmp;
                program_menu.add_button(tmp.title);
                program_menu.add_sub_menu(tmp.possible_commands,false,menus_added);
                menus_added++;
            }
            /*
            if(filter_types == "normal"){
                ofx_Normal_Map tmp;
                program_menu.add_button(tmp.title);
                program_menu.add_sub_menu(tmp.possible_commands,false,menus_added);
                menus_added++;
            }
            */
        }



        ofx_Histogram       hist;

        ofx_MenuSub         program_menu;
        ofx_Menu            Layer_Buttons;
        ofx_MenuSub         Layer_Com_Buttons;

        vector<ofx_Filter*> Canvas_Storage;

        ofx_Image           Base_Image;

        int                 layer_state;

        int                 image_w;
        int                 image_h;
        int                 button_w;
        int                 button_h;

        bool                image_grey;

        ofImage             drawImage;

        ofTexture           tex;
        ofTexture           tex_grey;

        string              layer_type;

    private:
};


#endif // OFX_LAYER_H


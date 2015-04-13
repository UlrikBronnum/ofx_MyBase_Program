#ifndef OFX_FILTER_H
#define OFX_FILTER_H

#include "ofx_Image.h"
#include "ofx_Color.h"
#include "ofx_SMenu.h"
#include "ofx_Button.h"


class ofx_Filter : public ofx_Image
{
    public:

        ofx_Filter() {invert_output = false;}
        virtual ~ofx_Filter() {}

        virtual void setup(int width, int height, string image_type){
            object_width = width;
            object_height = height;

            if(image_type == "grey" || image_type == "Grey" || image_type == "GREY"){
                channels = 1;
            }else if(image_type == "rgb" || image_type == "RGB" ){
                channels = 3;
            }else if(image_type == "rgba" || image_type == "RGBA"){
                channels = 4;
            }else{
                channels = 3;
            }

            image = new unsigned char[object_width * object_height * channels];

            Filter_Slider.setup(200,18);

            command = "";
            filter_set = false;
            update_needed = true;
        }
        virtual void reset(int width, int height){

            object_width = width;
            object_height = height;

            delete [] image;

            image = new unsigned char[object_width * object_height * channels];
            update_needed = true;
        }
        virtual void apply_filter(ofx_Image* input){}
        virtual void apply_filter(vector<ofx_Filter*> input,int start,int fin){}
        //------------------------- Draws -----------------------------------
        virtual void draw (int slider_x , int slider_y , ofx_Color color){
            Filter_Slider.draw(slider_x,slider_y,color);
        }
        virtual void draw (int slider_x , int slider_y , unsigned char color){
            Filter_Slider.draw(slider_x,slider_y,color);
        }

        bool mouse_drag (int x , int y){
            if(Filter_Slider.mouse_drag(x,y)){
                update_needed = true;
                return true;
            }
            return false;
        }


        void set_filter_button(int width,int height,string new_label,bool is_switch){
            command = new_label;
            Filter_Button.setup(width,height,new_label,is_switch);
            filter_set = false;
        }
        void reset_filter(string new_label){
            Filter_Slider.reset_slider();
            command = new_label;
            filter_set = false;
            update_needed = true;
        }

        ofx_Button* Get_Button(){  return &Filter_Button; }

        ofx_SMenu* Get_Sliders(){  return &Filter_Slider; }

        string Filter_Slider_Settings(){return Filter_Slider.Filter_Settings();}



        vector<string> possible_commands;
        string          title;
        string          command;

        bool            update_needed;

        bool        invert_output;


    protected:


        ofx_Button  Filter_Button;
        ofx_SMenu   Filter_Slider;

        bool filter_set;




        //-------------------------------------------------------------------------------
        void set_filter_sliders(string slider_labels[],float upper_limits[], float lower_limits[], int indexs)
        {
            for(int i = 0; i < indexs ; i++){
                Filter_Slider.add_slider(slider_labels[i], upper_limits[i], lower_limits[i]);
            }
        }
        //-------------------------------------------------------------------------------
        void set_filter_sliders(string slider_labels,float upper_limits, float lower_limits)
        {
            Filter_Slider.add_slider(slider_labels, upper_limits, lower_limits);
        }



    private:
};

#endif // OFX_FILTER_H

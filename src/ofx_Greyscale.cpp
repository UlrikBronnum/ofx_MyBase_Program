#include "ofx_Greyscale.h"



void ofx_Greyscale::apply_filter(ofx_Image* input){
    if(update_needed){
        if(command == "greyscale"){
            greyscale(input->Get_Image());
        }else if(command == "greyscale_from_channel"){
            greyscale_from_channel(input->Get_Image());
        }else if(command == "HSB"){
            HSB(input->Get_Image());
        }
        update_needed = false;
    }
}

void ofx_Greyscale::greyscale(unsigned char* input){
    for(int y = 0; y < object_height; y++){
        for(int x = 0 ; x < object_width; x++){
            int sum = 0;
            for(int c = 0; c < 3; c++){
                sum += input[(y*object_width+x)*3+c];
            }
            image[y*object_width+x] = sum/3;
        }
    }
}
void ofx_Greyscale::greyscale_from_channel(unsigned char* input){
    if(!filter_set){
        set_filter_sliders("channel",2, 0);
        filter_set = true;
    }
    for(int y = 0; y < object_height; y++){
        for(int x = 0 ; x < object_width; x++){
            image[y*object_width+x] = input[(y*object_width+x)*3 + return_channel()];
        }
    }
}

//----------------------Filter Functions------------------------
void ofx_Greyscale::HSB(unsigned char* input){
    if(!filter_set){

        float s_max[9]      = {360.0f   ,360.0f ,2.0f   ,100.0f ,100.0f , 2.0f  ,100.0f ,100.0f ,2.0f};
        float s_min[9]      = {0.0f     ,0.0f   ,-1.0f  ,0.0f   ,0.0f   , -1.0f ,  0.0f ,0.0f   ,-1.0f};
        string s_titles[9]  = {"Hue_Max","Hue_Min","Hue_Out","Saturation_Max","Saturation_Min","Saturation_Out","Brightness_Max","Brightness_Min","Brightness_Out"};

        set_filter_sliders(s_titles, s_max, s_min, 9);
        filter_set = true;
    }


    float hue, saturation, brightness;
    unsigned char result_r,result_g,result_b;

    ofColor myColor;
    for(int y = 0; y < object_height; y++){
        for(int x = 0 ; x < object_width; x++){
            int resultr[3],resultg[3],resultb[3];
            int result[3];

            myColor.r = input[(y*object_width+x)*3 + 0];
            myColor.g = input[(y*object_width+x)*3 + 1];
            myColor.b = input[(y*object_width+x)*3 + 2];



            myColor.getHsb( hue, saturation, brightness );

            if( hue < Filter_Slider._Menu_Sliders[0]->Slider_Value()
            && hue > Filter_Slider._Menu_Sliders[1]->Slider_Value() )
            {
                resultr[0] = Filter_Slider._Menu_Sliders[2]->Slider_Value() * input[(y*object_width+x)*3 + 0]  ;
                resultg[0] = Filter_Slider._Menu_Sliders[2]->Slider_Value()  * input[(y*object_width+x)*3 + 1]  ;
                resultb[0] = Filter_Slider._Menu_Sliders[2]->Slider_Value()  * input[(y*object_width+x)*3 + 2]  ;

            }
            else if((hue > Filter_Slider._Menu_Sliders[0]->Slider_Value()
            && hue < Filter_Slider._Menu_Sliders[1]->Slider_Value() )
            && Filter_Slider._Menu_Sliders[0]->Slider_Value() <  Filter_Slider._Menu_Sliders[1]->Slider_Value())

            {
                resultr[0] = Filter_Slider._Menu_Sliders[2]->Slider_Value() * input[(y*object_width+x)*3 + 0]  ;
                resultg[0] = Filter_Slider._Menu_Sliders[2]->Slider_Value()  * input[(y*object_width+x)*3 + 1]  ;
                resultb[0] = Filter_Slider._Menu_Sliders[2]->Slider_Value()  * input[(y*object_width+x)*3 + 2]  ;

            }else{
                resultr[0] = 0 ;
                resultg[0] = 0 ;
                resultb[0] = 0 ;
            }

            if( saturation < Filter_Slider._Menu_Sliders[3]->Slider_Value()
            &&  saturation > Filter_Slider._Menu_Sliders[4]->Slider_Value() )
            {
                resultr[1] = Filter_Slider._Menu_Sliders[5]->Slider_Value() * input[(y*object_width+x)*3 + 0]  ;
                resultg[1] = Filter_Slider._Menu_Sliders[5]->Slider_Value() * input[(y*object_width+x)*3 + 1]  ;
                resultb[1] = Filter_Slider._Menu_Sliders[5]->Slider_Value() * input[(y*object_width+x)*3 + 2]  ;
            }else{
                resultr[1] = 0  ;
                resultg[1] = 0  ;
                resultb[1] = 0 ;
            }

            if( brightness < Filter_Slider._Menu_Sliders[6]->Slider_Value()
            &&  brightness > Filter_Slider._Menu_Sliders[7]->Slider_Value() )
            {
                resultr[2] = Filter_Slider._Menu_Sliders[8]->Slider_Value() * 255  ;
                resultg[2] = Filter_Slider._Menu_Sliders[8]->Slider_Value() * 255  ;
                resultb[2] = Filter_Slider._Menu_Sliders[8]->Slider_Value() * 255 ;

            }else{
                resultr[2] = 0;
                resultg[2] = 0;
                resultb[2] = 0;
            }
            result[0] = (resultr[0] + resultr[1] + resultr[2]);
            result[1] = (resultg[0] + resultg[1] + resultg[2]);
            result[2] = (resultb[0] + resultb[1] + resultb[2]);

            if(result[0] > 255){
                result[0] = 255;
            }else if(result[0] < 0){
                result[0] = 0;
            }

            if(result[1] > 255){
                result[1] = 255;
            }else if(result[1] < 0){
                result[1] = 0;;
            }

            if(result[2] > 255){
                result[2] = 255;
            }else if(result[2] < 0){
                result[2] = 0;;
            }

            image[(y*object_width+x)] = (result[0] +  result[1] + result[2]) / 3;


        }
    }
}

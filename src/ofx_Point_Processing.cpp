#include "ofx_Point_Processing.h"

void ofx_Point_Processing::apply_filter(ofx_Image* input){
    if(update_needed){
        if(input->Image_Channel_Count() == 3){
            if(command == "brightness"){
                brightness_rgb(input->Get_Image());
            }else if(command == "contrast"){
                contrast_rgb(input->Get_Image());
            }else if(command == "gamma"){
                gamma_rgb(input->Get_Image());
            }else if(command == "invert"){
                invert_rgb(input->Get_Image());
            }else if(command == "HSB"){
                HSB(input->Get_Image());
            }else if(command == "threshold"){
                threshold_rgb(input->Get_Image());
            }
        }else if(input->Image_Channel_Count() == 1){
            if(command == "brightness"){
                brightness_grey(input->Get_Image());
            }else if(command == "contrast"){
                contrast_grey(input->Get_Image());
            }else if(command == "gamma"){
                gamma_grey(input->Get_Image());
            }else if(command == "invert"){
                invert_grey(input->Get_Image());
            }else if(command == "threshold"){
                threshold_grey(input->Get_Image());
            }
        }
        update_needed = false;
    }
}
//----------------------Filter Functions------------------------
//--------------------------Rgb Image---------------------------
void ofx_Point_Processing::brightness_rgb(unsigned char* input){
    if(!filter_set){
        set_filter_sliders("brightness",255, -255);
        filter_set = true;
    }
    for(int y = 0; y < object_height; y++){
        for(int x = 0 ; x < object_width; x++){
            for(int c = 0; c < 3; c++){
                int sum = input[(y*object_width+x)*3+c] + Filter_Slider._Menu_Sliders[0]->Slider_Value();
                if(sum > 255){
                    image[(y*object_width+x)*3+c] = 255;
                }else if(sum < 0){
                    image[(y*object_width+x)*3+c] = 0;
                }else{
                    image[(y*object_width+x)*3+c] = sum;
                }
            }
        }
    }
}
//-------------------------Grey Image---------------------------
void ofx_Point_Processing::brightness_grey(unsigned char* input){
    if(!filter_set){
        set_filter_sliders("brightness",255, -255);
        filter_set = true;
    }
    for(int y = 0; y < object_height; y++){
        for(int x = 0 ; x < object_width; x++){
            int sum = input[y*object_width+x] + Filter_Slider._Menu_Sliders[0]->Slider_Value();
            if(sum > 255){
                image[y*object_width+x] = 255;
            }else if(sum < 0){
                image[y*object_width+x] = 0;
            }else{
                image[y*object_width+x] = sum;
            }
        }
    }
}

//----------------------Filter Functions------------------------
//--------------------------Rgb Image---------------------------
void ofx_Point_Processing::contrast_rgb(unsigned char* input){
    if(!filter_set){
        set_filter_sliders("contrast",2.0f, 0.0f);
        filter_set = true;
    }
    for(int y = 0; y < object_height; y++){
        for(int x = 0 ; x < object_width; x++){
            for(int c = 0; c < 3; c++){
                int sum = input[(y*object_width+x)*3+c] * Filter_Slider._Menu_Sliders[0]->Slider_Value();
                if(sum > 255){
                    image[(y*object_width+x)*3+c] = 255;
                }else if(sum < 0){
                    image[(y*object_width+x)*3+c] = 0;
                }else{
                    image[(y*object_width+x)*3+c] = sum;
                }
            }
        }
    }
}
//-------------------------Grey Image---------------------------
void ofx_Point_Processing::contrast_grey(unsigned char* input){
    if(!filter_set){
        set_filter_sliders("contrast",2.0f, 0.0f);
        filter_set = true;
    }
    for(int y = 0; y < object_height; y++){
        for(int x = 0 ; x < object_width; x++){
            int sum = input[y*object_width+x] * Filter_Slider._Menu_Sliders[0]->Slider_Value();
            if(sum > 255){
                image[y*object_width+x] = 255;
            }else if(sum < 0){
                image[y*object_width+x] = 0;
            }else{
                image[y*object_width+x] = sum;
            }
        }
    }
}
//----------------------Filter Functions------------------------
//--------------------------Rgb Image---------------------------
void ofx_Point_Processing::gamma_rgb(unsigned char* input){
    if(!filter_set){
        set_filter_sliders("gamma",5, 0);
        filter_set = true;
    }
    for(int y = 0; y < object_height; y++){
        for(int x = 0 ; x < object_width; x++){
            for(int c = 0; c < 3; c++){
                unsigned char pixelVal = input[(y*object_width+x)*3+c];

                float gammaVal = pixelVal/255.0f;

                float outVal = pow(gammaVal,Filter_Slider._Menu_Sliders[0]->Slider_Value())*255;

                if(outVal > 255){
                    image[(y*object_width+x)*3+c] = 255;
                }else if(outVal < 0){
                    image[(y*object_width+x)*3+c] = 0;
                }else{
                    image[(y*object_width+x)*3+c] = outVal;
                }
            }
        }
    }
}
//-------------------------Grey Image---------------------------
void ofx_Point_Processing::gamma_grey(unsigned char* input){
    if(!filter_set){
        set_filter_sliders("gamma",5, 0);
        filter_set = true;
    }
    for(int y = 0; y < object_height; y++){
        for(int x = 0 ; x < object_width; x++){
            unsigned char pixelVal = input[y*object_width+x];

            float gammaVal = pixelVal/255.0f;

            float outVal = pow(gammaVal,Filter_Slider._Menu_Sliders[0]->Slider_Value())*255;

            if(outVal > 255){
                image[y*object_width+x] = 255;
            }else if(outVal < 0){
                image[y*object_width+x] = 0;
            }else{
                image[y*object_width+x] = outVal;
            }
        }

    }
}
//----------------------Filter Functions------------------------
//--------------------------Rgb Image---------------------------
void ofx_Point_Processing::threshold_rgb(unsigned char* input){
    if(!filter_set){
        float s_max[3]      = {255.0f   ,255.0f ,255.0f};
        float s_min[3]      = {0.0f     ,0.0f   ,0.0f   };
        string s_titles[3]  = {"Red","Green","Blue"};

        set_filter_sliders(s_titles, s_max, s_min, 3);
        filter_set = true;
    }
    for(int y = 0; y < object_height; y++){
        for(int x = 0 ; x < object_width; x++){
                unsigned char r = input[(y*object_width+x)*3+0];
                unsigned char g = input[(y*object_width+x)*3+1];
                unsigned char b = input[(y*object_width+x)*3+2];

                if(r > Filter_Slider._Menu_Sliders[0]->Slider_Value()){
                    image[(y*object_width+x)*3+0] = r;
                }else{
                    image[(y*object_width+x)*3+0] = 0;
                }
                if(g > Filter_Slider._Menu_Sliders[1]->Slider_Value()){
                    image[(y*object_width+x)*3+1] = g;
                }else{
                    image[(y*object_width+x)*3+1] = 0;
                }
                if(b > Filter_Slider._Menu_Sliders[2]->Slider_Value()){
                    image[(y*object_width+x)*3+2] = b;
                }else{
                    image[(y*object_width+x)*3+2] = 0;
                }

        }
    }
}
//-------------------------Grey Image---------------------------
void ofx_Point_Processing::threshold_grey(unsigned char* input){
    if(!filter_set){
        set_filter_sliders("threshold", 255.0f, 0.0f );
        filter_set = true;
    }
    for(int y = 0; y < object_height; y++){
        for(int x = 0 ; x < object_width; x++){
            if(input[y*object_width+x] > Filter_Slider._Menu_Sliders[0]->Slider_Value()){
                image[y*object_width+x] = input[y*object_width+x];
            }else{
                image[y*object_width+x] = 0;
            }
        }
    }
}
//----------------------Filter Functions------------------------
//--------------------------Rgb Image---------------------------
void ofx_Point_Processing::invert_rgb(unsigned char* input){
    for(int y = 0; y < object_height; y++){
        for(int x = 0 ; x < object_width; x++){
            for(int c = 0; c < 3; c++){
                image[(y*object_width+x)*3+c] = 255 - input[(y*object_width+x)*3+c];
            }
        }
    }
}
//-------------------------Grey Image---------------------------
void ofx_Point_Processing::invert_grey(unsigned char* input){
    for(int y = 0; y < object_height; y++){
        for(int x = 0 ; x < object_width; x++){
            image[y*object_width+x] = 255 - input[y*object_width+x];
        }
    }
}
//----------------------Filter Functions------------------------
void ofx_Point_Processing::HSB(unsigned char* input){
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

            image[(y*object_width+x)*3 + 0] = result[0];
            image[(y*object_width+x)*3 + 1] = result[1];
            image[(y*object_width+x)*3 + 2] = result[2];

        }
    }
}

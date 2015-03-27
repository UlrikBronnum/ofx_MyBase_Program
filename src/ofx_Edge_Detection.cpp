#include "ofx_Edge_Detection.h"


void ofx_Edge_Detection::apply_filter(ofx_Image* input){
    if(update_needed){
        if(command == "sobel_edge"){
            sobel_edge(input->Get_Image());
        }
        else if(command == "prewitt_edge"){
            prewitt_edge(input->Get_Image());
        }
        else if(command == "laplacian_edge"){
            laplacian_edge(input->Get_Image());
        }

        update_needed = false;
    }
}
//-------------------------Grey Image---------------------------
//----------------------Filter Functions------------------------
void ofx_Edge_Detection::prewitt_edge(unsigned char* input){
    if(!filter_set){
        set_filter_sliders("threshold",255,0);
        filter_set = true;
    }
    float prewittvertical[3][3] = {     {-1 , 0 , 1},
                                        {-1 , 0 , 1},
                                        {-1 , 0 , 1}};

    float prewitthorisontal[3][3] = {   {-1 ,-1 ,-1},
                                        { 0 , 0 , 0},
                                        { 1 , 1 , 1}};

    for(int y = 0; y < object_height ; y++){
        for(int x = 0; x < object_width ; x++){
            float sumV = 0.0f;
            float sumH = 0.0f;
            for(int fy = -1; fy <=1; fy++){
                for(int fx = -1; fx <=1; fx++){

                    int pos_x = x+fx;
                    int pos_y = y+fy;

                    if(pos_y < 0){
                        pos_y = object_height + fy;
                    }else if(pos_y >= object_height){
                        pos_y = fy;
                    }
                    if(pos_x < 0){
                        pos_x = object_width + fx;
                    }else if(pos_x >= object_width){
                        pos_x = fx;
                    }


                    sumV+=input[(pos_y)*object_width+(pos_x)] * prewittvertical[fy + 1][fx + 1];
                    sumH+=input[(pos_y)*object_width+(pos_x)] * prewitthorisontal[fy + 1][fx + 1];
                }
            }
            if(sumH > Filter_Slider._Menu_Sliders[0]->Slider_Value() || sumV > Filter_Slider._Menu_Sliders[0]->Slider_Value()){
                image[y*object_width+x] = 255;
            }else{
                image[y*object_width+x] = 0;
            }
        }

    }
}
//----------------------Filter Functions------------------------
void ofx_Edge_Detection::sobel_edge(unsigned char* input){
    if(!filter_set){
        set_filter_sliders("threshold",255,0);
        filter_set = true;
    }

    float sobelvertical[3][3] = {   {-1 , 0 , 1},
                                    {-2 , 0 , 2},
                                    {-1 , 0 , 1}};

    float sobelhorisontal[3][3] = { {-1 ,-2 ,-1},
                                    { 0 , 0 , 0},
                                    { 1 , 2 , 1}};

    for(int y = 0; y < object_height ; y++){
        for(int x = 0; x < object_width ; x++){
            float sumV = 0.0f;
            float sumH = 0.0f;
            for(int fy = -1; fy <=1; fy++){
                for(int fx = -1; fx <=1; fx++){

                    int pos_x = x+fx;
                    int pos_y = y+fy;

                    if(pos_y < 0){
                        pos_y = object_height + fy;
                    }else if(pos_y >= object_height){
                        pos_y = fy;
                    }
                    if(pos_x < 0){
                        pos_x = object_width + fx;
                    }else if(pos_x >= object_width){
                        pos_x = fx;
                    }

                    sumV+=input[(pos_y)*object_width+(pos_x)] * sobelvertical[fy + 1][fx + 1];
                    sumH+=input[(pos_y)*object_width+(pos_x)] * sobelhorisontal[fy + 1][fx + 1];
                }
            }
            if(sumH > Filter_Slider._Menu_Sliders[0]->Slider_Value() || sumV > Filter_Slider._Menu_Sliders[0]->Slider_Value()){
                image[y*object_width+x] = 255;
            }else{
                image[y*object_width+x] = 0;
            }

        }
    }
}
//----------------------Filter Functions------------------------
void ofx_Edge_Detection::laplacian_edge(unsigned char* input){
    if(!filter_set){
        set_filter_sliders("threshold",255,0);
        filter_set = true;
    }
    for(int y = 1; y < object_height-1 ; y++){
        for(int x = 1; x < object_width - 1; x++){
            int sum = 0;
            unsigned char one = input[(y-1) * object_width+x];
            unsigned char two = input[(y+1) * object_width+x];
            unsigned char three = input[y * object_width + (x-1)];
            unsigned char four = input[y * object_width + (x+1)];
            sum = (one+three) - (4 * input[(y*object_width+x)]) + two+four;
            if(sum > Filter_Slider._Menu_Sliders[0]->Slider_Value()){
                sum = 255;
            }else {
                sum = abs(sum);
            }
            image[y*object_width+x] = sum;
        }
    }
}

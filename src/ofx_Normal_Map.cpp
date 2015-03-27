#include "ofx_Normal_Map.h"


void ofx_Normal_Map::apply_filter(ofx_Image* input)
{
    if(!refs_set){
        ref_image = new unsigned char[object_width * object_height];
        s_image = new int[object_width * object_height];
        t_image = new int[object_width * object_height];


        refs_set = true;

        if(!filter_set){
            set_filter_sliders("roughness", 1.0f, 0.0f);
            filter_set = true;
        }
    }
    if(update_needed){
        memcpy(ref_image,input->Get_Image(),sizeof(unsigned char) * object_width * object_height);

        S_function(Filter_Slider._Menu_Sliders[0]->Slider_Value());
        T_function(Filter_Slider._Menu_Sliders[0]->Slider_Value());
        N_function();
        update_needed = false;
    }
}

void ofx_Normal_Map::S_function(float scalar){
    for(int y = 0; y < object_height; y++){
        for(int x = 0 ; x < object_width; x++){
            int pos_r = x+1;
            int pos_l = x-1;

            if(pos_r >= object_width){
                pos_r =  1;
            }
            if(pos_l < 0 ){
                pos_l = object_width - 1;
            }

            int sum = (ref_image[y*object_width+pos_l] - ref_image[y*object_width+pos_r])* scalar;
            s_image[y*object_width+x] = sum;
        }
    }
}

void ofx_Normal_Map::T_function( float scalar){
    for(int y = 0; y < object_height; y++){
        for(int x = 0 ; x < object_width; x++){
            int pos_d = y+1;
            int pos_u = y-1;

            if(pos_d >= object_height){
                pos_d = 0;
            }
            if(pos_u < 0 ){
                pos_u = object_height - 1;
            }

            int sum = (ref_image[pos_u*object_width+x] - ref_image[pos_d*object_width+x] )* scalar;
            t_image[y*object_width+x] = sum;
        }
    }
}

void ofx_Normal_Map::N_function(){
    for(int y = 0; y < object_height; y++){
        for(int x = 0 ; x < object_width; x++){
            float length_vector = sqrt( pow(float(s_image[y*object_width+x]),2.0f) + pow(float(t_image[y*object_width+x]),2.0f) + 1 );
            image[(y*object_width+x)*3+0] = ((- s_image[y*object_width+x]/ length_vector) * 127) + 127;
            image[(y*object_width+x)*3+1] = ((- t_image[y*object_width+x]/ length_vector) * 127) + 127;
            image[(y*object_width+x)*3+2] = 255 ;
        }
    }
}


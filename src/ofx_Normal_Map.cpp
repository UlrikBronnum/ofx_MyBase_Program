#include "ofx_Normal_Map.h"


void ofx_Normal_Map::apply_filter(ofx_Image* input)
{
    if(!refs_set){
        ref_image = new unsigned char[object_width * object_height];
        s_image = new int[object_width * object_height];
        t_image = new int[object_width * object_height];
        refs_set = true;

        if(!filter_set){
            set_filter_sliders("roughness", 1.0f, -1.0f);
            filter_set = true;
        }
    }
    if(update_needed){
        memcpy(ref_image,input->image,sizeof(unsigned char) * object_width * object_height);

        S_function(Filter_Slider._Menu_Sliders[0]->Slider_Value());
        T_function(Filter_Slider._Menu_Sliders[0]->Slider_Value());
        N_function();
        update_needed = false;
    }
}

void ofx_Normal_Map::S_function(float scalar){

    for(int y = 0; y < object_height; y++){
        for(int x = 1 ; x < object_width -1; x++){
            int sum = (ref_image[y*object_width+(x - 1)] - ref_image[y*object_width+(x + 1)])* scalar;
            s_image[y*object_width+x] = sum;
        }
    }
}

void ofx_Normal_Map::T_function( float scalar){

    for(int y = 1; y < object_height -1; y++){
        for(int x = 0 ; x < object_width; x++){
            int sum = (ref_image[(y - 1)*object_width+x] - ref_image[(y + 1)*object_width+x] )* scalar;
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


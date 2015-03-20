#include "ofx_Greyscale.h"



void ofx_Greyscale::apply_filter(ofx_Image* input){
    if(update_needed){
        if(command == "greyscale"){
            greyscale(input->image);
        }else if(command == "greyscale_from_channel"){
            greyscale_from_channel(input->image);
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

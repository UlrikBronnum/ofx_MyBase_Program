#include "ofx_Combine_Filter.h"


void ofx_Combine_Filter::apply_filter(vector<ofx_Filter*> input,int start,int fin){
    if(!filter_set){
        set_filter_combine( input,start,fin);
    }
    if(update_needed){
        if(command == "multiply combine"){
            multiply_combine(input,start,fin);
        }
        else if(command == "addition combine"){
            addition_combine(input,start,fin);
        }


        update_needed = false;
    }


}

void ofx_Combine_Filter::multiply_combine(vector<ofx_Filter*> input,int start,int fin){
    unsigned char* tmp_ref = new unsigned char[object_width * object_height];
    for(int y = 0; y < object_height; y++){
        for(int x = 0 ; x < object_width; x++){
            float sum = 0;
            int pixel_val = 0;
            for(int i = start; i < fin ; i++){
                sum += 1 * input[i]->Get_Image()[y*object_width+x]/255.0f * Filter_Slider._Menu_Sliders[i - start]->Slider_Value();
            }
            pixel_val = sum * 255;
            if(pixel_val > 255){
                pixel_val = 255;
            }else if(pixel_val < 0){
                pixel_val = 0;
            }
            tmp_ref[y*object_width+x] = pixel_val;
        }
    }

    int n = 1;
    for(int y = 0; y < object_height ; y++){
        for(int x = 0 ; x < object_width ; x++){
            int sum = 0;
            for(int fy = -n; fy <= n; fy++){
                for(int fx = -n; fx <= n; fx++){

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
                    sum += tmp_ref[(pos_y)*object_width+(pos_x)];
                }
            }
            sum /= 9;
            image[y*object_width+x] = sum;
        }
    }

    update_needed = false;

    delete [] tmp_ref;

}

void ofx_Combine_Filter::addition_combine(vector<ofx_Filter*> input,int start,int fin){
    unsigned char* tmp_ref = new unsigned char[object_width * object_height];
    for(int y = 0; y < object_height; y++){
        for(int x = 0 ; x < object_width; x++){
            int sum = 0;
            int counter = 0;
            for(int i = start; i < fin ; i++){
                sum += input[i]->Get_Image()[y*object_width+x] * Filter_Slider._Menu_Sliders[i - start]->Slider_Value();
                counter++;
            }
            /*if(sum > 255){
                sum = 255;
            }else if(sum < 0){
                sum = 0;
            }*/
            tmp_ref[y*object_width+x] = sum/counter;
        }
    }

    int n = 1;
    for(int y = 0; y < object_height ; y++){
        for(int x = 0 ; x < object_width ; x++){
            int sum = 0;
            for(int fy = -n; fy <= n; fy++){
                for(int fx = -n; fx <= n; fx++){

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
                    sum += tmp_ref[(pos_y)*object_width+(pos_x)];
                }
            }
            sum /= 9;
            image[y*object_width+x] = sum;
        }
    }

    update_needed = false;

    delete [] tmp_ref;

}



void ofx_Combine_Filter::set_filter_combine(vector<ofx_Filter*> input,int start,int fin){
    for(int i = start; i < fin ; i++){
        set_filter_sliders(input[i]->command, 1.0f, 0.0f );
    }
    filter_set = true;
}

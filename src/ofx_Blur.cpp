#include "ofx_Blur.h"

void ofx_Blur::apply_filter(ofx_Image* input){
    if(update_needed){
        if(input->Image_Channel_Count() == 3){
            if(command == "mean_filter"){
                if(!filter_set){
                    set_filter_sliders("kernel_size",9,1);
                    filter_set = true;
                }
                mean_blur_rgb(input->Get_Image(),return_kernel_size());
            }else if(command == "median_filter"){
                if(!filter_set){
                    set_filter_sliders("kernel_size",9,1);
                    filter_set = true;
                }
                median_blur_rgb(input->Get_Image(),return_kernel_size());
            }else if(command == "max_filter"){
                if(!filter_set){
                    set_filter_sliders("kernel_size",9,1);
                    filter_set = true;
                }
                max_blur_rgb(input->Get_Image(),return_kernel_size());
            }else if(command == "min_filter"){
                if(!filter_set){
                    set_filter_sliders("kernel_size",9,1);
                    filter_set = true;
                }
                min_blur_rgb(input->Get_Image(),return_kernel_size());
            }
        }else if(input->Image_Channel_Count() == 1){
            if(command == "mean_filter"){
                if(!filter_set){
                    set_filter_sliders("kernel_size",9,1);
                    filter_set = true;
                }
                mean_blur_grey(input->Get_Image(),return_kernel_size());
            }else if(command == "median_filter"){
                if(!filter_set){
                    set_filter_sliders("kernel_size",9,1);
                    filter_set = true;
                }
                median_blur_grey(input->Get_Image(),return_kernel_size());
            }else if(command == "max_filter"){
                if(!filter_set){
                    set_filter_sliders("kernel_size",9,1);
                    filter_set = true;
                }
                max_blur_grey(input->Get_Image(),return_kernel_size());
            }else if(command == "min_filter"){
                if(!filter_set){
                    set_filter_sliders("kernel_size",9,1);
                    filter_set = true;
                }
                min_blur_grey(input->Get_Image(),return_kernel_size());
            }
        }
        update_needed = false;
    }
}
//----------------------Filter Functions------------------------
//--------------------------Rgb Image---------------------------
void ofx_Blur::mean_blur_rgb(unsigned char* input, int kernelSize){
    int n = (kernelSize-1)/2;
    for(int y = 0; y < object_height ; y++){
        for(int x = 0 ; x < object_width ; x++){
            for(int c = 0 ; c < 3; c++){
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
                        sum += input[((pos_y)*object_width+(pos_x))*3+c];
                    }
                }
                sum /= (kernelSize * kernelSize);
                image[(y*object_width+x)*3+c] = sum;
            }
        }
    }
}
//-------------------------Grey Image---------------------------
void ofx_Blur::mean_blur_grey(unsigned char* input, int kernelSize){
    int n = (kernelSize-1)/2;
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
                    sum += input[(pos_y)*object_width+(pos_x)];
                }
            }
            sum /= (kernelSize * kernelSize);
            image[y*object_width+x] = sum;
        }
    }
}

//----------------------Filter Functions------------------------
//--------------------------Rgb Image---------------------------
void ofx_Blur::median_blur_rgb(unsigned char* input, int kernelSize){
    int n = (kernelSize-1)/2;
    for(int y = 0; y < object_height ; y++){
        for(int x = 0 ; x < object_width ; x++){
            for(int c = 0 ; c < 3; c++){
                vector<unsigned char> sortPixels;
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

                        sortPixels.push_back(input[((pos_y)*object_width+(pos_x))*3+c]);
                    }
                }
                sort(sortPixels.begin(),sortPixels.end());
                image[(y*object_width+x)*3+c] = sortPixels[n];
            }
        }
    }
}
//-------------------------Grey Image---------------------------
void ofx_Blur::median_blur_grey(unsigned char* input, int kernelSize){
    int n = (kernelSize-1)/2;
    for(int y = 0; y < object_height ; y++){
        for(int x = 0 ; x < object_width ; x++){
            vector<unsigned char> sortPixels;
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

                    sortPixels.push_back(input[(pos_y)*object_width+(pos_x)]);
                }
            }
            sort(sortPixels.begin(),sortPixels.end());
            image[y*object_width+x] = sortPixels[n];
        }
    }
}
//----------------------Filter Functions------------------------
//--------------------------Rgb Image---------------------------
void ofx_Blur::max_blur_rgb(unsigned char* input, int kernelSize){
    int n = (kernelSize-1)/2;
    for(int y = 0; y < object_height ; y++){
        for(int x = 0 ; x < object_width ; x++){
            for(int c = 0 ; c < 3; c++){
                unsigned char maxVal;
                maxVal = 0;
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

                        if(maxVal < input[((pos_y)*object_width+(pos_x))*3+c])
                            maxVal = input[((pos_y)*object_width+(pos_x))*3+c];
                    }
                }
                image[(y*object_width+x)*3+c] = maxVal;
            }
        }
    }
}
//-------------------------Grey Image---------------------------
void ofx_Blur::max_blur_grey(unsigned char* input, int kernelSize){
    int n = (kernelSize-1)/2;
    for(int y = 0; y < object_height ; y++){
        for(int x = 0 ; x < object_width ; x++){
            unsigned char maxVal;
            maxVal = 0;
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

                    if(maxVal < input[(pos_y)*object_width+(pos_x)])
                        maxVal = input[(pos_y)*object_width+(pos_x)];
                }
            }
            image[y*object_width+x] = maxVal;
        }
    }
}
//----------------------Filter Functions------------------------
//--------------------------Rgb Image---------------------------
void ofx_Blur::min_blur_rgb(unsigned char* input, int kernelSize){
    int n = (kernelSize-1)/2;
    for(int y = 0; y < object_height ; y++){
        for(int x = 0 ; x < object_width ; x++){
            for(int c = 0 ; c < 3; c++){
                unsigned char minVal ;
                minVal = 255;
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

                        if(minVal > input[((pos_y)*object_width+(pos_x))*3+c])
                            minVal = input[((pos_y)*object_width+(pos_x))*3+c];
                    }
                }
                image[(y*object_width+x)*3+c] = minVal;
            }
        }
    }
}
//-------------------------Grey Image---------------------------
void ofx_Blur::min_blur_grey(unsigned char* input, int kernelSize){
    int n = (kernelSize-1)/2;
    for(int y = 0; y < object_height ; y++){
        for(int x = 0 ; x < object_width ; x++){
            unsigned char minVal ;
            minVal = 255;
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

                    if(minVal > input[(pos_y)*object_width+(pos_x)])
                        minVal = input[(pos_y)*object_width+(pos_x)];
                }
            }
            image[y*object_width+x] = minVal;
        }
    }
}

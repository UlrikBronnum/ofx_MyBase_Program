#include "ofx_Neighborhood_Processing.h"

void ofx_Neighborhood_Processing::apply_filter(ofx_Image* input){
    if(update_needed){
        if(input->Image_Channel_Count() == 3){
            if(command == "mean_filter"){
                if(!filter_set){
                    set_filter_sliders("kernel_size",9,1);
                    filter_set = true;
                }
                mean_blur_rgb(input->image,return_kernel_size());
            }else if(command == "median_filter"){
                if(!filter_set){
                    set_filter_sliders("kernel_size",9,1);
                    filter_set = true;
                }
                median_blur_rgb(input->image,return_kernel_size());
            }else if(command == "max_filter"){
                if(!filter_set){
                    set_filter_sliders("kernel_size",9,1);
                    filter_set = true;
                }
                max_blur_rgb(input->image,return_kernel_size());
            }else if(command == "min_filter"){
                if(!filter_set){
                    set_filter_sliders("kernel_size",9,1);
                    filter_set = true;
                }
                min_blur_rgb(input->image,return_kernel_size());
            }
            else if(command == "sobel_edge"){
                sobel_edge_rgb(input->image);
            }
            else if(command == "prewitt_edge"){
                prewitt_edge_rgb(input->image);
            }
            else if(command == "laplacian_edge"){
                laplacian_edge_rgb(input->image);
            }
        }else if(input->Image_Channel_Count() == 1){
            if(command == "mean_filter"){
                if(!filter_set){
                    set_filter_sliders("kernel_size",9,1);
                    filter_set = true;
                }
                mean_blur_grey(input->image,return_kernel_size());
            }else if(command == "median_filter"){
                if(!filter_set){
                    set_filter_sliders("kernel_size",9,1);
                    filter_set = true;
                }
                median_blur_grey(input->image,return_kernel_size());
            }else if(command == "max_filter"){
                if(!filter_set){
                    set_filter_sliders("kernel_size",9,1);
                    filter_set = true;
                }
                max_blur_grey(input->image,return_kernel_size());
            }else if(command == "min_filter"){
                if(!filter_set){
                    set_filter_sliders("kernel_size",9,1);
                    filter_set = true;
                }
                min_blur_grey(input->image,return_kernel_size());
            }
            else if(command == "sobel_edge"){
                sobel_edge_grey(input->image);
            }
            else if(command == "prewitt_edge"){
                prewitt_edge_grey(input->image);
            }
            else if(command == "laplacian_edge"){
                laplacian_edge_grey(input->image);
            }
        }
        update_needed = false;
    }
}
//----------------------Filter Functions------------------------
//--------------------------Rgb Image---------------------------
void ofx_Neighborhood_Processing::mean_blur_rgb(unsigned char* input, int kernelSize){
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
void ofx_Neighborhood_Processing::mean_blur_grey(unsigned char* input, int kernelSize){
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
void ofx_Neighborhood_Processing::median_blur_rgb(unsigned char* input, int kernelSize){
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
void ofx_Neighborhood_Processing::median_blur_grey(unsigned char* input, int kernelSize){
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
void ofx_Neighborhood_Processing::max_blur_rgb(unsigned char* input, int kernelSize){
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
void ofx_Neighborhood_Processing::max_blur_grey(unsigned char* input, int kernelSize){
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
void ofx_Neighborhood_Processing::min_blur_rgb(unsigned char* input, int kernelSize){
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
void ofx_Neighborhood_Processing::min_blur_grey(unsigned char* input, int kernelSize){
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

//----------------------Filter Functions------------------------
//--------------------------Rgb Image---------------------------
void ofx_Neighborhood_Processing::prewitt_edge_rgb(unsigned char* input){
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
            for(int c = 0; c < 3; c++){
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


                        sumV+=input[((pos_y)*object_width+(pos_x))*3+c] * prewittvertical[fy + 1][fx + 1];
                        sumH+=input[((pos_y)*object_width+(pos_x))*3+c] * prewitthorisontal[fy + 1][fx + 1];
                    }
                }
                if(sumH > Filter_Slider._Menu_Sliders[0]->Slider_Value() || sumV > Filter_Slider._Menu_Sliders[0]->Slider_Value()){
                    image[(y*object_width+x)*3+c] = 255;
                }else{
                    image[(y*object_width+x)*3+c] = 0;
                }
            }
        }
    }
}
//-------------------------Grey Image---------------------------
void ofx_Neighborhood_Processing::prewitt_edge_grey(unsigned char* input){
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
//--------------------------Rgb Image---------------------------
void ofx_Neighborhood_Processing::sobel_edge_rgb(unsigned char* input){
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
            for(int c = 0; c < 3; c++){
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

                        sumV+=input[((pos_y)*object_width+(pos_x))*3+c] * sobelvertical[fy + 1][fx + 1];
                        sumH+=input[((pos_y)*object_width+(pos_x))*3+c] * sobelhorisontal[fy + 1][fx + 1];
                    }
                }
                if(sumH > Filter_Slider._Menu_Sliders[0]->Slider_Value() || sumV > Filter_Slider._Menu_Sliders[0]->Slider_Value()){
                    image[(y*object_width+x)*3+c] = 255;
                }else{
                    image[(y*object_width+x)*3+c] = 0;
                }
            }
        }
    }
}
//-------------------------Grey Image---------------------------
void ofx_Neighborhood_Processing::sobel_edge_grey(unsigned char* input){
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
//--------------------------Rgb Image---------------------------
void ofx_Neighborhood_Processing::laplacian_edge_rgb(unsigned char* input){
    if(!filter_set){
        set_filter_sliders("threshold",255,-255);
        filter_set = true;
    }
    for(int y = 1; y < object_height-1 ; y++){
        for(int x = 1; x < object_width - 1; x++){
            for(int c = 0; c < 3; c++){
                int sum = 0;
                unsigned char one = input[((y-1) * object_width+x)*3 + c];
                unsigned char two = input[((y+1) * object_width+x)*3 + c];
                unsigned char three = input[(y * object_width + (x-1)) * 3 + c];
                unsigned char four = input[(y * object_width + (x+1)) * 3 + c];
                sum = (one+three) - (4 * input[(y*object_width+x)]) + two+four;
                if(sum > Filter_Slider._Menu_Sliders[0]->Slider_Value()){
                    sum = 255;
                }else {
                    sum = abs(sum);
                }
                image[(y*object_width+x)*3+c] = sum;
            }
        }
    }
}
//-------------------------Grey Image---------------------------
void ofx_Neighborhood_Processing::laplacian_edge_grey(unsigned char* input){
    if(!filter_set){
        set_filter_sliders("threshold",255,-255);
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

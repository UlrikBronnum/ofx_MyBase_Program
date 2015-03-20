#ifndef OFX_NEIGHBORHOOD_PROCESSING_H
#define OFX_NEIGHBORHOOD_PROCESSING_H

#include <ofx_Filter.h>


class ofx_Neighborhood_Processing : public ofx_Filter
{
    public:
        ofx_Neighborhood_Processing(){
            possible_commands.push_back("mean_filter");
            possible_commands.push_back("median_filter");
            possible_commands.push_back("max_filter");
            possible_commands.push_back("min_filter");
            possible_commands.push_back("sobel_edge");
            possible_commands.push_back("prewitt_edge");
            possible_commands.push_back("laplacian_edge");

            title = "Neighborhood_Processing";
        }
        virtual ~ofx_Neighborhood_Processing(){}

        void apply_filter(ofx_Image* input);

        void mean_blur_rgb(unsigned char* input, int kernelSize);
        void median_blur_rgb(unsigned char* input, int kernelSize);
        void max_blur_rgb(unsigned char* input, int kernelSize);
        void min_blur_rgb(unsigned char* input, int kernelSize);
        void sobel_edge_rgb(unsigned char* input);
        void prewitt_edge_rgb(unsigned char* input);
        void laplacian_edge_rgb(unsigned char* input);

        void mean_blur_grey(unsigned char* input, int kernelSize);
        void median_blur_grey(unsigned char* input, int kernelSize);
        void max_blur_grey(unsigned char* input, int kernelSize);
        void min_blur_grey(unsigned char* input, int kernelSize);
        void sobel_edge_grey(unsigned char* input);
        void prewitt_edge_grey(unsigned char* input);
        void laplacian_edge_grey(unsigned char* input);

    protected:

        int return_kernel_size(){
            if(Filter_Slider._Menu_Sliders[0]->Slider_Value() >= 0 &&
               Filter_Slider._Menu_Sliders[0]->Slider_Value() < 2){
                return 1;
            }else if(Filter_Slider._Menu_Sliders[0]->Slider_Value() > 2 &&
                     Filter_Slider._Menu_Sliders[0]->Slider_Value() < 4){
                return 3;
            }else if(Filter_Slider._Menu_Sliders[0]->Slider_Value() > 4 &&
                     Filter_Slider._Menu_Sliders[0]->Slider_Value() < 6){
                return 5;
            }else if(Filter_Slider._Menu_Sliders[0]->Slider_Value() > 6 &&
                     Filter_Slider._Menu_Sliders[0]->Slider_Value() < 8){
                return 7;
            }else{
                return 9;
            }
        }
    private:
};

#endif // OFX_NEIGHBORHOOD_PROCESSING_H

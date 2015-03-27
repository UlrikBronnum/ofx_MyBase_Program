#ifndef OFX_BLUR_H
#define OFX_BLUR_H

#include <ofx_Filter.h>


class ofx_Blur : public ofx_Filter
{
    public:
        ofx_Blur(){
            possible_commands.push_back("mean_filter");
            possible_commands.push_back("median_filter");
            possible_commands.push_back("max_filter");
            possible_commands.push_back("min_filter");

            title = "Blur";
        }
        virtual ~ofx_Blur(){}


        void apply_filter(ofx_Image* input);


        // ----------------RGB------------------------
        void mean_blur_rgb(unsigned char* input, int kernelSize);
        void median_blur_rgb(unsigned char* input, int kernelSize);
        void max_blur_rgb(unsigned char* input, int kernelSize);
        void min_blur_rgb(unsigned char* input, int kernelSize);
        // ----------------Grey------------------------
        void mean_blur_grey(unsigned char* input, int kernelSize);
        void median_blur_grey(unsigned char* input, int kernelSize);
        void max_blur_grey(unsigned char* input, int kernelSize);
        void min_blur_grey(unsigned char* input, int kernelSize);



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

#endif // OFX_BLUR_H

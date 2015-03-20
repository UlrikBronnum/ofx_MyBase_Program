#ifndef OFX_GREYSCALE_H
#define OFX_GREYSCALE_H

#include <ofx_Filter.h>


class ofx_Greyscale : public ofx_Filter
{
    public:
        ofx_Greyscale(){
            possible_commands.push_back("greyscale");
            possible_commands.push_back("greyscale_from_channel");

            title = "Greyscale";
        }
        virtual ~ofx_Greyscale(){}

        void apply_filter(ofx_Image* input);

        void greyscale(unsigned char* input);
        void greyscale_from_channel(unsigned char* input);

    protected:

        int return_channel(){
            if(Filter_Slider._Menu_Sliders[0]->Slider_Value() >= 0 &&
               Filter_Slider._Menu_Sliders[0]->Slider_Value() < 0.8f){
                return 0;
            }else if(Filter_Slider._Menu_Sliders[0]->Slider_Value() > 0.8f &&
                     Filter_Slider._Menu_Sliders[0]->Slider_Value() < 1.6f){
                return 1;
            }else {
                return 2;
            }
        }
    private:
};

#endif // OFX_GREYSCALE_H

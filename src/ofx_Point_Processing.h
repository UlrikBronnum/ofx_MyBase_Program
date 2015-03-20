#ifndef OFX_POINT_PROCESSING_H
#define OFX_POINT_PROCESSING_H

#include <ofx_Filter.h>


class ofx_Point_Processing : public ofx_Filter
{
    public:
        ofx_Point_Processing(){
            possible_commands.push_back("brightness");
            possible_commands.push_back("contrast");
            possible_commands.push_back("gamma");
            possible_commands.push_back("invert");
            possible_commands.push_back("threshold");
            possible_commands.push_back("HSB");


            title = "Point_Processing";
        }
        virtual ~ofx_Point_Processing(){}

        void apply_filter(ofx_Image* input);

        void invert_rgb(unsigned char* input);
        void brightness_rgb(unsigned char* input);
        void contrast_rgb(unsigned char* input);
        void gamma_rgb(unsigned char* input);
        void HSB(unsigned char* input);
        void threshold_rgb(unsigned char* input);

        void invert_grey(unsigned char* input);
        void brightness_grey(unsigned char* input);
        void contrast_grey(unsigned char* input);
        void gamma_grey(unsigned char* input);
        void threshold_grey(unsigned char* input);


    protected:
    private:
};

#endif // OFX_POINT_PROCESSING_H

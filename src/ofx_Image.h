#ifndef OFX_IMAGE_H
#define OFX_IMAGE_H

#include "ofMain.h"

#include "ofx_Placement.h"


class ofx_Image : public ofx_Placement
{
    public:
        ofx_Image() : ofx_Placement(){
            image = NULL;
        }
        virtual ~ofx_Image() {
            if (image !=  NULL) {
                delete [] image;
            }
        }


        virtual void setup(int width, int height, string type){
            object_width = width;
            object_height = height;

            if(type == "grey" || type == "Grey" || type == "GREY"){
                channels = 1;
            }else if(type == "rgb" || type == "RGB" ){
                channels = 3;
            }else if(type == "rgba" || type == "RGBA"){
                channels = 4;
            }else{
                channels = 3;
            }

            image = new unsigned char[object_width * object_height * channels];
        }

        virtual void update(unsigned char* base_image){
            memcpy(image,base_image,sizeof(unsigned char) * object_width * object_height * channels);
        }
        virtual void update(ofx_Image* base_image){ }



        unsigned char* Get_Image(){
            return image;
        }

        short Image_Channel_Count(){
            return channels;
        }

    protected:

        unsigned char*  image;
        short           channels;


    private:
};

#endif // OFX_IMAGE_H

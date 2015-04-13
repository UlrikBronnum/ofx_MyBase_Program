#ifndef OFX_NORMAL_MAP_H
#define OFX_NORMAL_MAP_H

#include <ofx_Filter.h>


class ofx_Normal_Map : public ofx_Filter
{
    public:
        ofx_Normal_Map(){
            possible_commands.push_back("normal");

            title = "Normal";
            refs_set = false;
        }
        virtual ~ofx_Normal_Map(){
            delete [] s_image;
            delete [] t_image;
        }

        void reset(int width, int height){

            object_width = width;
            object_height = height;

            delete [] image;

            image = new unsigned char[object_width * object_height * channels];
            update_needed = true;
            refs_set = false;
        }


        void apply_filter(ofx_Image* input);

        void S_function( float scalar);
        void T_function( float scalar);
        void N_function();


        int* s_image;
        int* t_image;

    protected:

        unsigned char* ref_image;

        bool refs_set  ;
    private:
};

#endif // OFX_NORMAL_MAP_H

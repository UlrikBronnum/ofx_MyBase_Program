#ifndef OFX_EDGE_DETECTION_H
#define OFX_EDGE_DETECTION_H

#include <ofx_Filter.h>

class ofx_Edge_Detection : public ofx_Filter
{
    public:
        ofx_Edge_Detection(){
            possible_commands.push_back("sobel_edge");
            possible_commands.push_back("prewitt_edge");
            possible_commands.push_back("laplacian_edge");

            title = "Edge_Detection";
        }
        virtual ~ofx_Edge_Detection(){}

        void apply_filter(ofx_Image* input);

        void sobel_edge(unsigned char* input);
        void prewitt_edge(unsigned char* input);
        void laplacian_edge(unsigned char* input);

    protected:
    private:
};

#endif // OFX_EDGE_DETECTION_H

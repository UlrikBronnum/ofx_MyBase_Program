#ifndef OFX_COMBINE_FILTER_H
#define OFX_COMBINE_FILTER_H

#include <ofx_Filter.h>


class ofx_Combine_Filter : public ofx_Filter
{
    public:
        ofx_Combine_Filter(){
            possible_commands.push_back("multiply combine");
            possible_commands.push_back("addition combine");

            title = "Combine";
        }
        virtual ~ofx_Combine_Filter(){}

        void apply_filter(ofx_Image* input){}
        void apply_filter(vector <ofx_Filter*> input,int start,int fin);

        void multiply_combine(vector<ofx_Filter*> input,int start,int fin);
        void addition_combine(vector<ofx_Filter*> input,int start,int fin);

        void set_filter_combine(vector<ofx_Filter*> input,int start,int fin);

    protected:
    private:
};

#endif // OFX_COMBINE_FILTER_H

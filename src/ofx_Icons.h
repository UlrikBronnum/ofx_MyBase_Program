#ifndef OFX_ICONS_H
#define OFX_ICONS_H

#include "ofx_Placement.h"

#include "ofMain.h"

class ofx_Icons: public ofx_Placement
{
    public:
        ofx_Icons(){}
        virtual ~ofx_Icons(){}

        void load(string file_name);
        void load(unsigned char* pixels, int w , int h);
        void draw(int x, int y);
        void resize_icon(int w, int h);

    protected:

        ofImage icon;

    private:
};

#endif // OFX_ICONS_H

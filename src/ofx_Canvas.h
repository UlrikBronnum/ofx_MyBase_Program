#ifndef OFX_CANVAS_H
#define OFX_CANVAS_H


class ofx_Canvas
{
    public:
        ofx_Canvas();
        virtual ~ofx_Canvas();

        // setup, update, draw and mouse
        void setup(int image_width, int image_height, int button_width, int button_height);
        void set_reference(unsigned char* input_image);
        void update();
        void draw(int x, int y , unsigned char color, int window_w, int window_h);
        //------------------------ Mouse Interaction ------------------------
        void mouse_click (int x , int y);
        void mouse_hover (int x , int y);
        void mouse_drag (int x , int y);
        //


    protected:
    private:
};

#endif // OFX_CANVAS_H

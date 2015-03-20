#ifndef OFX_PLACEMENT_H
#define OFX_PLACEMENT_H


class ofx_Placement
{
    public:
        //----------------- Constructor/Deconstructor -----------------------
        ofx_Placement() { }
        virtual ~ofx_Placement() { }

        //------------------------- Setup -----------------------------------
        void set_dimensions(int w , int h){
            object_width = w;
            object_height = h;
        }
        void set_placement(int x , int y){
            object_x = x;
            object_y = y;
        }

        //------------------------ Mouse Interaction ------------------------
        bool Mouse_Over_Button(int x , int y){
            if( x > object_x && x < object_x + object_width &&
                y > object_y && y < object_y + object_height){
                return true;
            }else{
                return false;
            }
        }
        //--------------------------- Get / Set -----------------------------
        virtual int Width(){return object_width;}
        virtual int Height(){return object_height;}


    protected:

        int object_width;
        int object_height;

        int object_x;
        int object_y;

};

#endif // OFX_PLACEMENT_H

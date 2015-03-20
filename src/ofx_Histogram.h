#ifndef OFX_HISTOGRAM_H
#define OFX_HISTOGRAM_H


class ofx_Histogram
{
    public:
        ofx_Histogram(){}
        virtual ~ofx_Histogram(){}

        void reset(){
            largest_bin = -1;
            histogram_min = -1;
            histogram_max = -1;
            for(int i = 0; i < 256; i++){
                containers[i] = 0;
            }
        }
        void update(unsigned char* image,int width, int height, bool rgb){
            reset();
            if(rgb){
                for(int y = 0; y < height; y++){
                    for(int x = 0 ; x < width; x++){
                        for(int c = 0; c < 3; c++){
                            containers[ image[(y*width+x)*3+c] ] ++;
                        }
                    }
                }
            }else{
                for(int y = 0; y < height; y++){
                    for(int x = 0 ; x < width; x++){
                        containers[ image[y*width+x] ] ++;
                    }
                }
            }

            calc_min();
            calc_max();
            calc_largest_bin();
        }

        void draw(int x,int y,int width, int height,unsigned char color){
            ofSetColor(255 - color );
            ofRect( x + 10 ,y - 2 ,256, height + 4 );

            ofSetColor(color);

            int new_w = width / 256;

            for(int i = 0 ; i < 256 ; i++){
                if(i > 10 && i < 256){
                    ofSetColor(color);
                    float newHeight = float(containers[i])/ float(largest_bin);
                    ofRect( 12 + x + (i - 11) * new_w ,y + height - height * newHeight + 2,new_w, height* newHeight );
                }

            }
        }

        void calc_max(){
            for(int i = 0; i < 256; i++){
                if(containers[i] != 0){
                    histogram_max = i;
                    return;
                }
            }
        }
        void calc_min(){
            for(int i = 255; i >= 0  ; i++){
                if(containers[i] != 0){
                    histogram_min = i;
                    return;
                }
            }
        }

        void calc_largest_bin(){
            largest_bin = 0;
            for(int i = 0; i < 256; i++){
                if(containers[i] > largest_bin){
                    largest_bin = containers[i];
                }
            }
        }

        int Histogram_Min(){
            return histogram_min;
        }
        int Histogram_Max(){
            return histogram_max;
        }

    protected:

        int containers[256];
        int largest_bin;
        int histogram_min;
        int histogram_max;

    private:
};

#endif // OFX_HISTOGRAM_H

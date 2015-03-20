#include "ofx_Icons.h"

void ofx_Icons::load(string file_name){
    string final_string = "icons/" + file_name;
    icon.loadImage(final_string);
    cout << final_string << " " << icon.getWidth() << " " << icon.getHeight() << " " << endl;
    set_dimensions(icon.getWidth(),icon.getHeight());
}
void ofx_Icons::draw(int x, int y){
    icon.draw(x,y);
}
void ofx_Icons::resize_icon(int w, int h){
    icon.resize(w,h);
    set_dimensions(icon.getWidth(),icon.getHeight());
}

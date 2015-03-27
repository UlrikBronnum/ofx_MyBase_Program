#include "ofx_Layer.h"

void ofx_Layer::setup(int image_width, int image_height, int button_width, int button_height, string new_layer_type){
    image_w = image_width;
    image_h = image_height;
    button_w = button_width;
    button_h = button_height;

    got_reference = false;
    slider_drag = false;

    layer_type = new_layer_type;
    if(layer_type == "diffuse"){
        Base_Image.setup(image_w,image_h,"rgb");
    }else if(layer_type == "height"){
        Base_Image.setup(image_w,image_h,"rgb");
    }else if(layer_type == "normal"){
        Base_Image.setup(image_w,image_h,"grey");
    }

    set_sub_menu(layer_type);

    Layer_Buttons.setup (button_w,button_h, true , false);
    Layer_Com_Buttons.setup (button_h,button_h,button_w,button_h);

    tex.allocate(image_w,image_h,GL_RGB);
    tex_grey.allocate(image_w,image_h,GL_LUMINANCE);
    hist.reset();
}
void ofx_Layer::reset(int image_width, int image_height){
    image_w = image_width;
    image_h = image_height;

    got_reference = false;
    slider_drag = false;

    if(layer_type == "diffuse"){
        Base_Image.setup(image_w,image_h,"rgb");
    }else if(layer_type == "height"){
        Base_Image.setup(image_w,image_h,"rgb");
    }else if(layer_type == "normal"){
        Base_Image.setup(image_w,image_h,"grey");
    }

    for(int i = 0; i < Canvas_Storage.size();i++){
        Canvas_Storage[i]->reset(image_width, image_height);
    }
    tex.allocate(image_w,image_h,GL_RGB);
    tex_grey.allocate(image_w,image_h,GL_LUMINANCE);
}
void ofx_Layer::update(unsigned char* input_image){

    Base_Image.update(input_image);
    if(layer_type == "diffuse"){
        tex.loadData(Base_Image.Get_Image(),image_w,image_h,GL_RGB);
        hist.update(Base_Image.Get_Image(),image_w,image_h,true);
    }else if(layer_type == "height"){
        tex_grey.loadData(Base_Image.Get_Image(),image_w,image_h,GL_LUMINANCE);
        hist.update(Base_Image.Get_Image(),image_w,image_h,false);
    }else if(layer_type == "normal"){
        tex_grey.loadData(Base_Image.Get_Image(),image_w,image_h,GL_LUMINANCE);
        hist.update(Base_Image.Get_Image(),image_w,image_h,false);
    }
    got_reference = true;
    for(int i = 0 ; i < Canvas_Storage.size() ; i++){
        Canvas_Storage[i]->update_needed = true;
    }
}
void ofx_Layer::update(){
    if(Canvas_Storage.size() > Layer_Buttons.Menu_State() && Layer_Buttons.Menu_State() != -1){
        if(Canvas_Storage.size() == 1 || Layer_Buttons.Menu_State() == 0)
        {
            Canvas_Storage[Layer_Buttons.Menu_State()]->apply_filter(&Base_Image);
        }
        else
        {
            for(int i = 0 ; i < Canvas_Storage.size() ; i++){
                if(Canvas_Storage[i]->update_needed){
                    if( i == 0){
                        Canvas_Storage[i]->apply_filter(&Base_Image);
                    }else{
                        Canvas_Storage[i]->apply_filter(Canvas_Storage[i - 1]);
                    }
                }
            }
        }
        if(Canvas_Storage[Layer_Buttons.Menu_State()]->Image_Channel_Count() == 3)
        {
            hist.update(Canvas_Storage[Layer_Buttons.Menu_State()]->Get_Image(),image_w,image_h,true);
            image_grey = false;
            tex.loadData(Canvas_Storage[Layer_Buttons.Menu_State()]->Get_Image(),image_w,image_h,GL_RGB);
        }
        else if(Canvas_Storage[Layer_Buttons.Menu_State()]->Image_Channel_Count() == 1)
        {
            hist.update(Canvas_Storage[Layer_Buttons.Menu_State()]->Get_Image(),image_w,image_h,false);
            image_grey = true;
            tex_grey.loadData(Canvas_Storage[Layer_Buttons.Menu_State()]->Get_Image(),image_w,image_h,GL_LUMINANCE);
        }
    }else{
        hist.update(Base_Image.Get_Image(),image_w,image_h,true);
        image_grey = false;
        tex.loadData(Base_Image.Get_Image(),image_w,image_h,GL_RGB);
    }

}
void ofx_Layer::add_Layer(string header , string filter, bool can_be_deleted){
    stringstream func_string;
    bool newAction = false;
    if(header == "Point_Processing"){
        func_string << "layer_added" << "=" << filter ;

        ofx_Point_Processing* tmp = new ofx_Point_Processing();
        if(!Canvas_Storage.empty()){
            if(Canvas_Storage[Canvas_Storage.size()-1]->Image_Channel_Count() == 1){
                tmp->setup(image_w,image_h,"grey");
            }else if(Canvas_Storage[Canvas_Storage.size()-1]->Image_Channel_Count() == 3){
                tmp->setup(image_w,image_h,"rgb");
            }
        }else{
            tmp->setup(image_w,image_h,"rgb");
        }
        tmp->set_filter_button(button_w,button_h,filter,true);
        Layer_Buttons.add_button(tmp->Get_Button());
        Layer_Buttons.Menu_State(Layer_Buttons.Button_Count()-1);
        image_grey = false;

        Layer_Com_Buttons.add_button(" ");
        vector<string> tmp_title = tmp->possible_commands;
        if(can_be_deleted){tmp_title.push_back("delete");}

        Layer_Com_Buttons.add_sub_menu(tmp_title,false,Layer_Com_Buttons.Button_Count() - 1);

        Canvas_Storage.push_back(tmp);
        newAction = true;
    }
    if(header == "Neighborhood_Processing"){
        func_string << "layer_added" << "=" << filter ;

        ofx_Neighborhood_Processing* tmp = new ofx_Neighborhood_Processing();
        if(!Canvas_Storage.empty()){
            if(Canvas_Storage[Canvas_Storage.size()-1]->Image_Channel_Count() == 1){
                tmp->setup(image_w,image_h,"grey");
            }else if(Canvas_Storage[Canvas_Storage.size()-1]->Image_Channel_Count() == 3){
                tmp->setup(image_w,image_h,"rgb");
            }
        }else{
            tmp->setup(image_w,image_h,"rgb");
        }
        tmp->set_filter_button(button_w,button_h,filter,true);

        Layer_Com_Buttons.add_button(" ");
        vector<string> tmp_title = tmp->possible_commands;
        if(can_be_deleted){tmp_title.push_back("delete");}
        Layer_Com_Buttons.add_sub_menu(tmp_title,false,Layer_Com_Buttons.Button_Count() - 1);

        Canvas_Storage.push_back(tmp);
        Layer_Buttons.add_button(tmp->Get_Button());
        Layer_Buttons.Menu_State(Layer_Buttons.Button_Count()-1);
        image_grey = false;
        newAction = true;
    }
    if(header == "Blur"){
        func_string << "layer_added" << "=" << filter ;

        ofx_Blur* tmp = new ofx_Blur();
        if(!Canvas_Storage.empty()){
            if(Canvas_Storage[Canvas_Storage.size()-1]->Image_Channel_Count() == 1){
                tmp->setup(image_w,image_h,"grey");
            }else if(Canvas_Storage[Canvas_Storage.size()-1]->Image_Channel_Count() == 3){
                tmp->setup(image_w,image_h,"rgb");
            }
        }else{
            tmp->setup(image_w,image_h,"rgb");
        }
        tmp->set_filter_button(button_w,button_h,filter,true);

        Layer_Com_Buttons.add_button(" ");
        vector<string> tmp_title = tmp->possible_commands;
        if(can_be_deleted){tmp_title.push_back("delete");}
        Layer_Com_Buttons.add_sub_menu(tmp_title,false,Layer_Com_Buttons.Button_Count() - 1);

        Canvas_Storage.push_back(tmp);
        Layer_Buttons.add_button(tmp->Get_Button());
        Layer_Buttons.Menu_State(Layer_Buttons.Button_Count()-1);
        image_grey = false;
        newAction = true;
    }
    if(header == "Greyscale"){
        func_string << "layer_added" << "=" << filter ;

        ofx_Greyscale* tmp = new ofx_Greyscale();
        tmp->setup(image_w,image_h,"grey");
        tmp->set_filter_button(button_w,button_h,filter,true);

        Layer_Com_Buttons.add_button(" ");
        vector<string> tmp_title = tmp->possible_commands;
        if(can_be_deleted){tmp_title.push_back("delete");}
        Layer_Com_Buttons.add_sub_menu(tmp_title,false,Layer_Com_Buttons.Button_Count() - 1);

        Canvas_Storage.push_back(tmp);
        Layer_Buttons.add_button(tmp->Get_Button());
        Layer_Buttons.Menu_State(Layer_Buttons.Button_Count()-1);
        image_grey = true;
        newAction = true;
    }
    if(header == "Edge_Detection"){
        func_string << "layer_added" << "=" << filter ;

        ofx_Edge_Detection* tmp = new ofx_Edge_Detection();
        tmp->setup(image_w,image_h,"grey");
        tmp->set_filter_button(button_w,button_h,filter,true);

        Layer_Com_Buttons.add_button(" ");
        vector<string> tmp_title = tmp->possible_commands;
        if(can_be_deleted){tmp_title.push_back("delete");}
        Layer_Com_Buttons.add_sub_menu(tmp_title,false,Layer_Com_Buttons.Button_Count() - 1);

        Canvas_Storage.push_back(tmp);
        Layer_Buttons.add_button(tmp->Get_Button());
        Layer_Buttons.Menu_State(Layer_Buttons.Button_Count()-1);
        image_grey = true;
        newAction = true;
    }
    if(header == "Normal_map"){
        func_string << "layer_added" << "=" << filter ;

        ofx_Normal_Map* tmp = new ofx_Normal_Map();
        tmp->setup(image_w,image_h,"rgb");
        tmp->set_filter_button(button_w,button_h,filter,true);

        Layer_Com_Buttons.add_button(" ");
        vector<string> tmp_title = tmp->possible_commands;
        if(can_be_deleted){tmp_title.push_back("delete");}
        Layer_Com_Buttons.add_sub_menu(tmp_title,false,Layer_Com_Buttons.Button_Count() - 1);

        Canvas_Storage.push_back(tmp);
        Layer_Buttons.add_button(tmp->Get_Button());
        Layer_Buttons.Menu_State(Layer_Buttons.Button_Count()-1);
        image_grey = false;
        newAction = true;
    }

    if(newAction) func_string >> log_string;
}

void ofx_Layer::delete_Layer(int index ){
    stringstream func_string;
    func_string << "layer_deleted=" << index << "=" << Layer_Buttons.Button_String(index);
    func_string >> log_string;
    Layer_Buttons.delete_button(index);
    delete Canvas_Storage[index];
    Canvas_Storage.erase(Canvas_Storage.begin() + index);
    Layer_Com_Buttons.delete_menu(index);
    if(Layer_Buttons.Button_Count() != 0 ){
        Layer_Buttons.Menu_State(Layer_Buttons.Button_Count() - 1);
    }else{
        Layer_Buttons.Menu_State(-1);
    }
}

void ofx_Layer::reset_Layers(){

}

void ofx_Layer::draw(int x, int y , unsigned char color, int window_w, int window_h){

    if(image_grey){
        ofSetColor(255);
        tex_grey.draw(x,y);
    }else{
        ofSetColor(255);
        tex.draw(x,y);
    }

    hist.draw(window_w-256,30,256,96,color);
    Layer_Buttons.draw(window_w -button_w, window_h/6 + 2,color ,  window_w,  window_h);
    if(Layer_Buttons.Height() + window_h/3 > window_h){
        Layer_Com_Buttons.draw(window_w -button_w - button_h - 20, window_h/6 + 2,color ,  window_w,  window_h);
    }else{
        Layer_Com_Buttons.draw(window_w -button_w - button_h , window_h/6 + 2,color ,  window_w,  window_h);
    }

    if(Canvas_Storage.size() > Layer_Buttons.Menu_State() && Layer_Buttons.Menu_State() != -1 )
    {
        Canvas_Storage[Layer_Buttons.Menu_State()]->draw(20,window_h/6 ,color);
    }

}


void  ofx_Layer::mouse_click (int x , int y){
    Layer_Buttons.mouse_click (x , y);
    Layer_Com_Buttons.mouse_click (x , y);

    if(Layer_Com_Buttons.Menu_Main_State() != -1)
    {
        if(Layer_Com_Buttons.Menu_Sub_State() != -1 )
        {
            if(Layer_Com_Buttons.Button_String() != "delete"){
                Canvas_Storage[Layer_Com_Buttons.Menu_Main_State()]->reset_filter(Layer_Com_Buttons.Button_String());
                Layer_Buttons.Set_Button_String(Layer_Com_Buttons.Menu_Main_State() ,Layer_Com_Buttons.Button_String());
                log_string = "layer_change=" + Layer_Com_Buttons.Button_String() ;
            }else{
                log_string = "layer_deleted=" + Layer_Com_Buttons.Button_String() ;
                delete_Layer(Layer_Com_Buttons.Menu_Main_State() );
            }
            Layer_Com_Buttons.Reset_Menu();
        }
    }
}
void  ofx_Layer::mouse_hover (int x , int y){
    Layer_Buttons.mouse_hover (x , y);
    Layer_Com_Buttons.mouse_hover (x , y);
}
void  ofx_Layer::mouse_drag (int x , int y){
    Layer_Buttons.mouse_drag (x , y);
    if(Canvas_Storage.size() > Layer_Buttons.Menu_State() && Layer_Buttons.Menu_State() != -1 ){
        if(Canvas_Storage[Layer_Buttons.Menu_State()]->mouse_drag (x , y)){
            slider_drag = true;
        }
    }
}

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetFrameRate(60);

    load_external_file = true;
    back_button.setup(60,30,"Back",false);

    system_log_string = "";
    save_format = ".png";
    string startup_time_string = create_time_string();

    string logStr = "program_logs/log_" ;
	logStr +=  startup_time_string;

    save_folder_name = startup_time_string;

    cout << save_folder_name << endl;
    Log.open(logStr + "/log.txt", ofFile::WriteOnly, false);
    // Log version
    Log << program_version << endl;

    //=====================Video Recordings===============================
    Window_Width            = ofGetWidth();
    Window_Height           = ofGetHeight();
    aux_Window_Width 		= 320;	// try to grab at this size.
	aux_Window_Height 		= 240;

	if(record){
        // Initiate webcam feed
        vidGrabber.setDeviceID(0);
        vidGrabber.setVerbose(true);
        vidGrabber.initGrabber(aux_Window_Width,aux_Window_Height);
        // Webcam save file
        string program_video_name = logStr + "/webcam_video.mov";
        save_webcam_window.setCodecQualityLevel(OF_QT_SAVER_CODEC_QUALITY_NORMAL);
        save_webcam_window.setup(aux_Window_Width, aux_Window_Height, program_video_name);
        // Program save file
        program_video_name = logStr + "/program_video.mov";
        save_main_window.setCodecQualityLevel(OF_QT_SAVER_CODEC_QUALITY_NORMAL);
        save_main_window.setup(ofGetWidth(), ofGetHeight(),  program_video_name);
	}

    // Start log
    logStr = "program_started=";
    logStr += startup_time_string;
    Log << logStr << endl;

    reset_layers();

    Program_Header_System.setup();
    Program_Header_System.Set_Sub_Menu(Image_Layers[0]->Get_Program_Menu());

    Image_Selector_Menu.setup(522/3,36,false,false);
    Image_Selector_Menu.add_button("Diffuse",true);
    Image_Selector_Menu.add_button("Heightmap",true);
    Image_Selector_Menu.add_button("Normalmap",true);

    filename_of_reference = "";

    ofBackground(0);

    ofx_Icons* tmp_icon = new ofx_Icons();
    tmp_icon->load("dragndrop_box.png");
    system_icons.push_back(tmp_icon);
    tmp_icon = new ofx_Icons();
    tmp_icon->load("dragndrop_arrow.png");
    system_icons.push_back(tmp_icon);
    tmp_icon = new ofx_Icons();
    tmp_icon->load("mouse.png");
    tmp_icon->resize_icon(32,32);
    system_icons.push_back(tmp_icon);
}

//--------------------------------------------------------------
void ofApp::update(){
    if(record){
        vidGrabber.update();
    //--------------RECORD VIDEO-----------------------------
        if(Window_Width != 0 || Window_Height != 0)
        {
            // Save videograbber feed
            save_webcam_window.addFrame(vidGrabber.getPixels());
            // Main window
            main_window.grabScreen(0, 0, Window_Width, Window_Height);
            save_main_window.addFrame(main_window.getPixels());
        }
    //------------RECORD VIDEO END---------------------------
    }


    if( system_ref_image.isAllocated() ){
        string newLog = "";
        if(Image_Selector_Menu.Menu_State() == 0){
            Image_Layers[0]->update();
            newLog = Image_Layers[0]->Log_String();
        }else if(Image_Selector_Menu.Menu_State() == 1){
            if(!Image_Layers[1]->got_reference){
                Image_Layers[1]->update(Image_Layers[0]->Get_Image());
            }
            Image_Layers[1]->update();
            newLog = Image_Layers[1]->Log_String();
        }else if(Image_Selector_Menu.Menu_State() == 2) {
            if(!Image_Layers[2]->got_reference){
                Image_Layers[2]->update(Image_Layers[1]->Get_Image());
            }
            Image_Layers[2]->update();
            newLog = Image_Layers[2]->Log_String();
        }

        if(newLog != "") Log << newLog << endl;
    }



}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    ofx_Color c;
    c.set_color(200);



    ofSetColor(200 - 200/5);
    ofRect(Window_Width/2 - 520/2+1,64+36,520,520);
    ofSetColor(255);
    Image_Selector_Menu.draw(Window_Width/2 - 520/2 ,64,c,Window_Width,Window_Height);


    if(!load_external_file  &&  system_ref_image.isAllocated() ){
        ofSetColor(255);
        if(Image_Selector_Menu.Menu_State() != -1 && Image_Selector_Menu.Menu_State() < Image_Layers.size()){
            Image_Layers[Image_Selector_Menu.Menu_State()]->draw(Window_Width/2 - 512/2 +1 ,64 + 36 + 4,200,Window_Width,Window_Height);
        }
    }else{
        ofSetColor(0);
        ofRect(0,0,Window_Width,Window_Height);
        if(system_ref_image.isAllocated()){
            back_button.draw(Window_Width - 80, Window_Height - 50,200);
        }

        ofSetColor(255);
        //ofRect(Window_Width/2 - 256 ,Window_Height/2 - 256,512,512);
        system_icons[0]->draw(Window_Width / 2 - (system_icons[0]->Width()/2),Window_Height/2 - (system_icons[0]->Height()/2) );
        system_icons[1]->draw(Window_Width / 2 - (system_icons[1]->Width()/2),Window_Height/2 - (system_icons[1]->Height()/2 + system_icons[1]->Height()/2) - (30 * sin(3*ofGetElapsedTimef()) ));
    }


    ofSetColor(255);
    ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate()) + "\ntime: " + ofToString(ofGetElapsedTimef()) + "\nfileformat: " + save_format ,10,Window_Height - 50);

    //Program_Header_System draws last!!!!!!!!!!!!!!!!!!!!!!
    ofSetColor(200);
    ofRect(1,1,Window_Width,23);
    Program_Header_System.draw(c,Window_Width,Window_Height);
    stringstream program_label;
    program_label  << filename_of_reference  << endl;
    ofDrawBitmapString(program_label.str(),Window_Width - Window_Width/5,18);

    ofSetColor(255);
    system_icons[2]->draw(mouse_x - system_icons[2]->Width()/2 ,mouse_y - system_icons[2]->Height()/2);

}
//--------------------------------------------------------------
void ofApp::exit(){

    string logStr = "program_terminate=";
	logStr += create_time_string() ;

    Log << logStr << endl;
    if(record){
        // Close screen grab
        save_main_window.finishMovie();
        save_webcam_window.finishMovie();
        closeQuicktime();
    }
}
//--------------------------------------------------------------
void ofApp::reset_layers(){

    Image_Layers.clear();
    save_counter.clear();

    for(int i = 0; i < 3 ; i++){
        if(i == 0){
            ofx_Layer* tmp = new ofx_Layer();
            tmp->setup(512,512,Window_Width/5,25,"diffuse");
            Image_Layers.push_back(tmp);
            save_counter.push_back(1);

        }else if(i == 1){
            ofx_Layer* tmp = new ofx_Layer();
            tmp->setup(512,512,Window_Width/5,25,"height");
            tmp->add_Layer("Greyscale" , "greyscale" , false);
            Image_Layers.push_back(tmp);
            save_counter.push_back(1);
        }else{
            ofx_Layer* tmp = new ofx_Layer();
            tmp->setup(512,512,Window_Width/5,25,"normal");
            tmp->add_Layer("Normal_map" , "normal" , false);
            Image_Layers.push_back(tmp);
            save_counter.push_back(1);
        }
    }

}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    mouse_x = x;
    mouse_y = y;

    Program_Header_System.mouse_hover(x,y);
    if(system_ref_image.isAllocated() ){
        if(Program_Header_System.Program_State() == -1){
            Image_Selector_Menu.mouse_hover(x,y);
        }
    }
    if(load_external_file){
        back_button.mouse_hover(x,y);
    }else{
        if(Image_Selector_Menu.Menu_State() > -1 && Image_Selector_Menu.Menu_State() < 3){
            Image_Layers[Image_Selector_Menu.Menu_State()]->mouse_hover(x,y);
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

    Program_Header_System.mouse_drag(x,y);

    if(Image_Selector_Menu.Menu_State() > -1 && Image_Selector_Menu.Menu_State() < 3){
        Image_Layers[Image_Selector_Menu.Menu_State()]->mouse_drag(x,y);
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){


    if(Program_Header_System.mouse_click(x,y)){
        string input = Program_Header_System.Get_Button_Label();
        if(input != ""){
            system_log_string = "program_input=" + input;
            Log << system_log_string << endl;
            cout << system_log_string << endl;
        }else{
            input = Program_Header_System.Program_String();
            if(input != ""){
                system_log_string = "program_input=" + input;
                Log << system_log_string << endl;
                cout << system_log_string << endl;
            }
        }
    }
    if(Program_Header_System.Program_State() == -1){
        if(system_ref_image.isAllocated() ){
            if(Image_Selector_Menu.mouse_click(x,y)){
                int image_selected = Image_Selector_Menu.Menu_State();
                system_log_string = "image_selected=" + Image_Selector_Menu.Button_String(image_selected);
                Log << system_log_string << endl;
                cout << system_log_string << endl;
                if(image_selected == 0){
                    Program_Header_System.Set_Sub_Menu(Image_Layers[0]->Get_Program_Menu());
                    Image_Layers[1]->got_reference = false;
                    Image_Layers[2]->got_reference = false;
                }else if(image_selected == 1){
                    Program_Header_System.Set_Sub_Menu(Image_Layers[1]->Get_Program_Menu());
                    Image_Layers[2]->got_reference = false;
                }else if(image_selected == 2){
                    Program_Header_System.Set_Sub_Menu(Image_Layers[2]->Get_Program_Menu());
                }
            }
        }
    }

    if(Program_Header_System.Program_State() == 0){
        // The menu state is -1 as default and is changed when a button is pressed
        if(Program_Header_System.Menu_State() == 0 && Program_Header_System.Program_String() != ""){
            // Filename and button tittle is the same so...
            string file_name =  Program_Header_System.Program_String();
            if(file_name == "Load External"){
                load_external_file = true;
            }else{
                load_image(file_name);
            }
        }
        if(Program_Header_System.Menu_State() == 1 ){
            if(Program_Header_System.Sub_State() > -1 && Program_Header_System.Sub_State() < Image_Layers.size()){
                save_image( Program_Header_System.Sub_State());
            }else if(Program_Header_System.Sub_State() == 3){
                for(int i = 0; i < 3 ; i++){
                    save_image( i );
                }
            }

        }
        if(Program_Header_System.Menu_State() == 2){
            ofExit();
        }
    }

    if(Program_Header_System.Program_State() == 1){
        if(Program_Header_System.Menu_State() == 0 && Program_Header_System.Program_String() != ""){
            save_format = Program_Header_System.Program_String();
        }
    }


    if(Program_Header_System.Program_State() == 2 && Image_Selector_Menu.Menu_State() != -1){
        if(Program_Header_System.Menu_State() > -1 && Program_Header_System.Program_String() != ""){
            string filter_cata = Program_Header_System.Get_Button_Labels_Sub(true,Program_Header_System.Program_State(),Program_Header_System.Menu_State(),Program_Header_System.Sub_State() ) ;
            string filter_type = Program_Header_System.Get_Button_Labels_Sub(false,Program_Header_System.Program_State(),Program_Header_System.Menu_State(),Program_Header_System.Sub_State() );
            cout << filter_cata << "\n" << filter_type << endl;
            if(Image_Selector_Menu.Menu_State() == 0){
                Image_Layers[0]->add_Layer(filter_cata , filter_type , true);
            }else if(Image_Selector_Menu.Menu_State() == 1){
                Image_Layers[1]->add_Layer(filter_cata , filter_type , true);
            }else if(Image_Selector_Menu.Menu_State() == 2) {
                Image_Layers[2]->add_Layer(filter_cata , filter_type , true);
            }
        }
    }

    if(load_external_file){
        if(back_button.mouse_click(x,y)){
            load_external_file = false;
        }
    }else{
        if(Image_Selector_Menu.Menu_State() > -1 && Image_Selector_Menu.Menu_State() < 3){
            Image_Layers[Image_Selector_Menu.Menu_State()]->mouse_click(x,y);
        }
    }



    cout << "program_state: " << Program_Header_System.Program_State() << endl;
    cout << "menu_state: " << Program_Header_System.Menu_State() << endl;
    cout << "sub_state: " << Program_Header_System.Sub_State() << endl;
    cout << "program_string: " << Program_Header_System.Program_String() << endl;
    cout << "image_state: " << Image_Selector_Menu.Menu_State() << endl;
    cout << "-----------------------------------------\n" << endl;


}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    Window_Width = w;
    Window_Height = h;
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    string file_name = "";
    std::size_t found = dragInfo.files[0].find('.');
    if (found==std::string::npos){
        string folder_location = dragInfo.files[0] + "\\";
        vector<string> tmp = load_folder(folder_location,false);
        for(int i = 0; i < tmp.size(); i++){
            file_name = tmp[i];
            unsigned found = file_name.find_last_of('.');
            string file_format = file_name.substr(found+1);
            if(found){
                if(file_format == "jpg" || file_format == "png" || file_format == "tga" || file_format == "tiff" ){
                    ofPixels pix;
                    ofLoadImage(pix,folder_location + file_name);
                    string save_file = "images/" + file_name;
                    ofSaveImage(pix,ofToDataPath(save_file) , OF_IMAGE_QUALITY_BEST );
                    cout << "found " << file_format << endl;
                }else{
                    cout << "not found" << endl;
                }
            }else{
                cout << "not found" << endl;
            }
        }

        if(file_name != ""){load_image(file_name);}

        cout << "loaded" << endl;
        Program_Header_System.replace_load_menu();

    }else{
        cout << "file" <<  endl;
        file_name = "";
        for(int i = 0; i < dragInfo.files.size(); i++){
            file_name = dragInfo.files[i];
            cout << file_name << endl;
            ofPixels pix;
            ofLoadImage(pix,file_name);
            unsigned found = file_name.find_last_of("/\\");
            file_name = file_name.substr(found+1);
            cout << file_name << endl;
            string save_file = "images/" + file_name;
            ofSaveImage(pix,ofToDataPath(save_file) , OF_IMAGE_QUALITY_BEST );
        }

        if(file_name != ""){load_image(file_name);}

        cout << "loaded" << endl;
        Program_Header_System.replace_load_menu();
    }


}
void ofApp::load_image(string filename){

    if(!Image_Layers.empty()){reset_layers();}
    // Filename and button tittle is the same so...
    string format = filename;
    string::size_type n;
    n = format.find('.');
    int p = format.size();
    format = format.substr (n, (p - n) );
    save_format = format;

    // openFrameworks image loads from the data folder by default
    // the image folder is specified as the load directory
    string load_file = "images/" + filename;
    // openFrameworks loads image from file and resizes it to 512x512
    filename_of_reference = load_file;
    system_ref_image.loadImage(load_file);
    system_ref_image.resize(512,512);
    //cout << "Load: " << load_file << endl;
    Image_Selector_Menu.Menu_State(0);
    Log << "image_selected=" << Image_Selector_Menu.Menu_State() << endl;
    Image_Layers[0]->update(system_ref_image.getPixels());
    Image_Layers[1]->update(Image_Layers[0]->Get_Image());
    Image_Layers[1]->update();
    Image_Layers[2]->update(Image_Layers[1]->Get_Image());
    Image_Layers[2]->update();
    system_log_string = "file_loaded=" + load_file;
    Log << system_log_string << endl;
    load_external_file = false;
}
//--------------------------------------------------------------
void ofApp::save_image(int layer_number){

    ofImage tmp_image;
    tmp_image.loadImage(filename_of_reference);
    int w = tmp_image.getWidth();
    int h = tmp_image.getHeight();



    string filename = "";
    if(layer_number == 0){
        filename = "/diffuse_";
        system_ref_image.setFromPixels(create_diffuse(tmp_image.getPixels(), w,h), w,h , OF_IMAGE_COLOR,true);
    }else if(layer_number == 1){
        filename = "/height_";
        system_ref_image.setFromPixels( greyscale2rgb( create_height ( create_diffuse (tmp_image.getPixels(), w,h), w,h),w ,h), w,h , OF_IMAGE_COLOR,false);
    }else if(layer_number == 2){
        filename = "/normal_";
        system_ref_image.setFromPixels(create_normal(create_height ( create_diffuse (tmp_image.getPixels(), w,h), w,h), w,h) , w,h , OF_IMAGE_COLOR,true);
    }

    ofPixels pix = system_ref_image.getPixelsRef();
    string destination = "image_output/" + save_folder_name + filename + ofToString(save_counter[layer_number]) + save_format;
    save_counter[layer_number]++;
    cout << "Pixels is set!" << endl;
    ofFile newFile(ofToDataPath(destination)); //file doesn't exist yet
    newFile.create();
    cout << "File open!" << endl;
    ofSaveImage(pix,ofToDataPath(destination) , OF_IMAGE_QUALITY_BEST );
    cout << "File saved!" << endl;
    newFile.close();
    cout << "File closed!" << endl;

    system_ref_image.loadImage(filename_of_reference);
    system_ref_image.resize(512,512);
    w = system_ref_image.getWidth();
    h = system_ref_image.getHeight();
    cout <<w << " " << h<< endl;
    create_normal(create_height ( create_diffuse (system_ref_image.getPixels(), w,h), w,h), w,h);
}
//--------------------------------------------------------------
unsigned char* ofApp::create_diffuse(unsigned char* image ,int w ,int h ){
    Image_Layers[0]->reset(w,h);
    Image_Layers[0]->update(image);
    for(int i = 0; i < Image_Layers[0]->Get_Canvas_Count(); i++){
        Image_Layers[0]->Set_Menu_State(i);
        Image_Layers[0]->update();
    }
    return Image_Layers[0]->Get_Image();
}
//--------------------------------------------------------------
unsigned char* ofApp::create_height(unsigned char* image ,int w ,int h ){
    Image_Layers[1]->reset(w,h);
    Image_Layers[1]->update(image);
    for(int i = 0; i < Image_Layers[1]->Get_Canvas_Count(); i++){
        Image_Layers[1]->Set_Menu_State(i);
        Image_Layers[1]->update();
    }
    return Image_Layers[1]->Get_Image();
}
//--------------------------------------------------------------
unsigned char* ofApp::create_normal(unsigned char* image,int w ,int h){
    Image_Layers[2]->reset(w,h);
    Image_Layers[2]->update(image);
    for(int i = 0; i < Image_Layers[2]->Get_Canvas_Count(); i++){
        Image_Layers[2]->Set_Menu_State(i);
        Image_Layers[2]->update();
    }
    return Image_Layers[2]->Get_Image();
}
//--------------------------------------------------------------

string ofApp::create_time_string(){
    time_t now = time(0);
    tm* localtm = localtime(&now);
    ostringstream convert;   // stream used for the conversion
    convert << localtm->tm_mday <<"-"<<localtm->tm_hour <<"-"<<localtm->tm_min<<"-"<<localtm->tm_sec;
    return convert.str();
}
//--------------------------------------------------------------
unsigned char* ofApp::greyscale2rgb(unsigned char* image,int w ,int h){
    unsigned char* update_image = new unsigned char[w*h*3];
    for(int y = 0; y < h; y++){
        for(int x = 0 ; x < w; x++){
            for(int c = 0; c < 3; c++){
                update_image[(y*w+x)*3+c] = image[y*w+x];
            }
        }
    }
    return update_image;
}

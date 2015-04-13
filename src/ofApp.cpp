#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofFile un;
    string usernum;
    un.open("program_files/index.txt", ofFile::ReadOnly, false);
    un >> usernum;
    un.close();

    user_count = ofToInt(usernum);

    //if(check_path("\\data\\program_files\\",true)){cout << "true" << endl;}


    startup_time_string = create_time_string();
    find_drives();

    ofFile pf;string fileContents;
    pf.open("program_files/save_info.txt", ofFile::ReadOnly, false);
    pf >> fileContents;
    pf.close();
    cout << fileContents << endl;

    if(check_path(fileContents,false)){
        pf.open("program_files/save_info.txt", ofFile::WriteOnly, false);
        if(fileContents.size() != 0){
            save_folder_name = fileContents;
            pf << save_folder_name;
        }else{
            save_folder_name = "image_output/" ;
            pf << save_folder_name;
        }
        pf.close();
    }else{
        pf.open("program_files/save_info.txt", ofFile::WriteOnly, false);
        save_folder_name = "image_output/";
        pf << save_folder_name;
        pf.close();
    }

    cout << "Images are saved at " << save_folder_name << endl;

    system_log_string = "";
    save_counter_str = "";
    filename_of_reference = "";
    save_format = ".png";
    set_save_folder = false;
    load_external_file = true;

    string logStr = "program_logs/log_" ;
	logStr +=  startup_time_string;
    Log.open(logStr + "/log.txt", ofFile::WriteOnly, false);
    // Log version
    Log << "User=" << user_count << endl;
    Log << program_version << endl;
    Log << return_program_path() << endl;
    Log << save_folder_name << endl;



    reset_layers();

    back_button.setup(60,30,"Back",false);

    Program_Header_System.setup();

    Image_Selector_Menu.setup(522/3,36,false,false);
    Image_Selector_Menu.add_button("Diffuse Texture",true);
    Image_Selector_Menu.add_button("Height Texture",true);
    Image_Selector_Menu.add_button("Normal Texture",true);

    //=====================Video Recordings===============================
    Window_Width            = ofGetWidth();
    Window_Height           = ofGetHeight();
    aux_Window_Width 		= 320;	// try to grab at this size.
	aux_Window_Height 		= 240;

    lalala.setup(Window_Width,Window_Height,logStr);

	ofSetFrameRate(60);

	if(my_record){
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



    ofBackground(0);

    ofx_Icons* tmp_icon = new ofx_Icons();
    tmp_icon->load("dragndrop_box.png");
    system_icons.push_back(tmp_icon);
    tmp_icon = new ofx_Icons();
    tmp_icon->load("dragndrop_arrow.png");
    system_icons.push_back(tmp_icon);
    tmp_icon = new ofx_Icons();
    tmp_icon->load("placeholder.tga");
    system_icons.push_back(tmp_icon);
    tmp_icon = new ofx_Icons();
    tmp_icon->load("mouse.png");
    tmp_icon->resize_icon(32,32);
    system_icons.push_back(tmp_icon);

}

//--------------------------------------------------------------
void ofApp::update(){
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
            if(!Image_Layers[1]->got_reference){
                Image_Layers[1]->update(Image_Layers[0]->Get_Image());
            }
            Image_Layers[1]->update();
            if(!Image_Layers[2]->got_reference){
                Image_Layers[2]->update(Image_Layers[0]->Get_Image());
            }
            Image_Layers[2]->update();
            newLog = Image_Layers[2]->Log_String();
        }

        if(newLog != "") Log << newLog << endl;
    }

    if(Program_Header_System.Program_State() == 0){
        // The menu state is -1 as default and is changed when a button is pressed
        if(Program_Header_System.Menu_State() == 0 && Program_Header_System.Sub_State() != -1){
            // Filename and button tittle is the same so...
            string file_name =  Program_Header_System.Program_String();
            if(file_name == "Load External"){
                load_external_file = true;
                set_save_folder = false;
            }else{
                load_image(file_name);
                set_save_folder = false;
            }
            Program_Header_System.Reset_Menu();
        }
        if(Program_Header_System.Menu_State() == 1 && Program_Header_System.Sub_State() != -1){
            if(Program_Header_System.Sub_State() > -1 && Program_Header_System.Sub_State() < Image_Layers.size()){
                save_counter_str = "s" + ofToString(Program_Header_System.Sub_State());
                Program_Header_System.Reset_Menu();
            }else if(Program_Header_System.Sub_State() == 3){
                save_counter_str = "a0";
                Program_Header_System.Reset_Menu();
            }
        }
        if(Program_Header_System.Menu_State() == 2 && Program_Header_System.Sub_State() != -1){
            save_format = Program_Header_System.Program_String();
            Program_Header_System.Reset_Menu();
        }
        if(Program_Header_System.Menu_State() == 3 && Program_Header_System.Sub_State() != -1){
            load_external_file = false;
            set_save_folder = true;
            Program_Header_System.Reset_Menu();
        }
        if(Program_Header_System.Menu_State() == 4){
            ofExit();
        }
    }


    if(Program_Header_System.Program_State() == 1 && Image_Selector_Menu.Menu_State() != -1){

        if(Program_Header_System.Menu_State() > -1 && Program_Header_System.Program_String() != ""){
            string filter_cata = Program_Header_System.Get_Button_Labels_Sub(true,Program_Header_System.Program_State(),Program_Header_System.Menu_State(),Program_Header_System.Sub_State() ) ;
            string filter_type = Program_Header_System.Get_Button_Labels_Sub(false,Program_Header_System.Program_State(),Program_Header_System.Menu_State(),Program_Header_System.Sub_State() );
            if(Image_Selector_Menu.Menu_State() == 0 && Program_Header_System.Sub_State() != -1){
                Image_Layers[0]->add_Layer(filter_cata , filter_type , true);
                Program_Header_System.Reset_Menu();
            }else if(Image_Selector_Menu.Menu_State() == 1 && Program_Header_System.Sub_State() != -1){
                Image_Layers[1]->add_Layer(filter_cata , filter_type , true);
                lalala.update(my_mouse_x,my_mouse_y,filter_type);
                Program_Header_System.Reset_Menu();
            }else if(Image_Selector_Menu.Menu_State() == 2 && Program_Header_System.Sub_State() != -1) {
                Image_Layers[2]->add_Layer(filter_cata , filter_type , true);
                Program_Header_System.Reset_Menu();
            }
        }
    }


    if(!save_counter_str.empty() && save_counter_str.at(save_counter_str.size()-1) == 'd'){
        if(save_counter_str.size() == 3){
            if(save_counter_str.at(0) == 's'){
                save_image( int (save_counter_str.at(1) ) - 48);
                save_counter_str = "";
            }else if (save_counter_str.at(0) == 'a'){
                int value = int (save_counter_str.at(1) ) - 48;
                if(value != -1 && value < 3){
                    save_image( value);
                    value++;
                    if(value < 3){
                        save_counter_str = "a" + ofToString(value);
                    }else{
                        lalala.update(my_mouse_x,my_mouse_y,"all");
                        save_counter_str = "";
                    }
                }
            }
        }else{
            if(save_counter_str.at(0) == 'f'){
                load_dragInfo_folder(save_counter_str.substr(1,save_counter_str.size()-2));
                save_counter_str = "";
            }else if(save_counter_str.at(0) == 'i'){
                load_dragInfo_file(save_counter_str);
                save_counter_str = "";
            }
        }
    }


    if(my_record){
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

    lalala.update(my_mouse_x,my_mouse_y,"");
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    ofx_Color c;
    c.set_color(200);

    lalala.draw(Window_Width,Window_Height);

    if(!lalala.isRunning){

        if(save_counter_str == ""){
            if( !load_external_file && !set_save_folder &&  system_ref_image.isAllocated() ){

                ofSetColor(200 - 200/5);
                ofRect(Window_Width/2 - 520/2+1,64+36,520,520);
                ofSetColor(255);
                Image_Selector_Menu.draw(Window_Width/2 - 520/2 ,64,c,Window_Width,Window_Height);

                ofSetColor(255);
                if(Image_Selector_Menu.Menu_State() != -1 && Image_Selector_Menu.Menu_State() < Image_Layers.size()){
                    Image_Layers[Image_Selector_Menu.Menu_State()]->draw(Window_Width/2 - 512/2 +1 ,64 + 36 + 4,200,Window_Width,Window_Height);
                }
            }else{
                //ofSetColor(0);
                //ofRect(0,0,Window_Width,Window_Height);

                ofSetColor(255);
                system_icons[0]->draw(Window_Width / 2 - (system_icons[0]->Width()/2),Window_Height/2 - (system_icons[0]->Height()/2) );
                system_icons[1]->draw(Window_Width / 2 - (system_icons[1]->Width()/2),Window_Height/2 - (system_icons[1]->Height()/2 + system_icons[1]->Height()/2) - (30 * sin(3*ofGetElapsedTimef()) ));

                ofSetColor(255);
                string load_text = "";
                if( load_external_file){
                    load_text = "Drop file or folder";
                    ofDrawBitmapString( load_text ,Window_Width / 2 - (load_text.size() * 8 /2),Window_Height/3 - 160);
                    if(system_ref_image.isAllocated()){
                        back_button.draw(Window_Width - 80, Window_Height - 50,200);
                    }
                }else if( set_save_folder){
                    load_text = "Current save folder: " + save_folder_name;
                    ofDrawBitmapString( load_text ,Window_Width / 2 - (load_text.size() * 8 /2),Window_Height/3 - 160);
                    back_button.draw(Window_Width - 80, Window_Height - 50,200);
                }


            }
        }else{
            //ofSetColor(0);
            //ofRect(0,0,Window_Width,Window_Height);
            if(save_counter_str.at(0) == 's' || save_counter_str.at(0) == 'a'){
                ofSetColor(255);
                int val = save_counter_str.at(1)-48;
                string load_text = "Greetings, I'm Saving ";
                if(val == 1 || (val == 2 && Image_Layers[val]->Image_Channel_Count() == 1) ){
                    unsigned char* convert_gray = greyscale2rgb(Image_Layers[val]->Get_Image(),512,512);
                    system_icons[2]->load(convert_gray,512,512);
                    load_text += "Height";
                    delete [] convert_gray;
                }else{
                    system_icons[2]->load(Image_Layers[val]->Get_Image(),512,512);
                    if(val == 0){load_text += "Diffuse";}else{load_text += "Normal";}
                }

                system_icons[2]->resize_icon(256,256);
                system_icons[2]->draw(Window_Width / 2 - (system_icons[2]->Width()/2),Window_Height/3 - (system_icons[2]->Height()/2) );

                ofSetColor(255);

                ofDrawBitmapString( load_text ,Window_Width / 2 - 113,Window_Height/3 - 160);
                save_counter_str += "d";
            }else if(save_counter_str.at(0) == 'i' || save_counter_str.at(0) == 'f'){
                ofSetColor(255);
                system_icons[2]->load("placeholder.tga");
                system_icons[2]->resize_icon(256,256);
                system_icons[2]->draw(Window_Width / 2 - (system_icons[2]->Width()/2),Window_Height/3 - (system_icons[2]->Height()/2) );
                ofSetColor(255);
                string load_text = "Loading...." ;
                ofDrawBitmapString( load_text ,Window_Width / 2 - 50,Window_Height/3 - 160);
                save_counter_str += "d";
            }
        }
        //Program_Header_System draws last!!!!!!!!!!!!!!!!!!!!!!
        Program_Header_System.draw(c,Window_Width,Window_Height);
    }



    ofSetColor(255);
    ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate()) + "\ntime: " + ofToString(ofGetElapsedTimef()) + "\nfileformat: " + save_format ,10,Window_Height - 50);




    if(my_record){
        ofSetColor(255);
        system_icons[3]->draw(my_mouse_x - system_icons[3]->Width()/2 ,my_mouse_y - system_icons[3]->Height()/2);
    }


}
//--------------------------------------------------------------
void ofApp::exit(){

    string logStr = "program_terminate=";
	logStr += create_time_string() ;

    Log << logStr << endl;
    if(my_record){
        // Close screen grab
        save_main_window.finishMovie();
        save_webcam_window.finishMovie();
        closeQuicktime();
    }

    for(int i = 0; i < Image_Layers.size() ; i++){
        delete Image_Layers[i];
    }
    Image_Layers.clear();
    save_counter.clear();
    for(int i = 0; i < system_icons.size() ; i++){
        delete system_icons[i];
    }
    system_icons.clear();

    if(lalala.done){
        ofFile pf;
        pf.open("program_files/index.txt", ofFile::WriteOnly, false);
        pf << user_count + 1 << endl;
        pf.close();
    }
}
//--------------------------------------------------------------
void ofApp::reset_layers(){
    for(int i = 0; i < Image_Layers.size() ; i++){
        delete Image_Layers[i];
    }
    Image_Layers.clear();
    save_counter.clear();

    int b_width = 222;
    int b_height = 25;

    for(int i = 0; i < 3 ; i++){
        if(i == 0){
            ofx_Layer* tmp = new ofx_Layer();
            tmp->setup(512,512,b_width,b_height,"diffuse",true);
            Image_Layers.push_back(tmp);
            save_counter.push_back(1);
        }else if(i == 1){
            ofx_Layer* tmp = new ofx_Layer();
            tmp->setup(512,512,b_width,b_height,"height",true);
            tmp->add_Layer("Greyscale" , "greyscale" , false);
            Image_Layers.push_back(tmp);
            save_counter.push_back(1);
        }else{
            ofx_Layer* tmp = new ofx_Layer();
            tmp->setup(512,512,b_width,b_height,"normal",false);
            tmp->add_Layer("Greyscale" , "greyscale" , false);
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
    my_mouse_x = x;
    my_mouse_y = y;

    Program_Header_System.mouse_hover(x,y);
    if(system_ref_image.isAllocated() ){
        if(Program_Header_System.Program_State() == -1){
            Image_Selector_Menu.mouse_hover(x,y);
        }
    }
    if(load_external_file || set_save_folder){
        back_button.mouse_hover(x,y);
    }else{
        if(Image_Selector_Menu.Menu_State() > -1 && Image_Selector_Menu.Menu_State() < 3){
            Image_Layers[Image_Selector_Menu.Menu_State()]->mouse_hover(x,y);
        }
    }

    lalala.mouse_hover(x,y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    my_mouse_x = x;
    my_mouse_y = y;

    Program_Header_System.mouse_drag(x,y);

    if(Image_Selector_Menu.Menu_State() > -1 && Image_Selector_Menu.Menu_State() < 3){
        Image_Layers[Image_Selector_Menu.Menu_State()]->mouse_drag(x,y);
        if(Image_Layers[Image_Selector_Menu.Menu_State()]->slider_drag){
            lalala.update(my_mouse_x,my_mouse_y,"drag");
        }
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    lalala.mouse_click(x,y);

    if(Program_Header_System.mouse_click(x,y)){
        string input = Program_Header_System.Get_Button_Label();
        if(input != ""){

            system_log_string = "program_input=" + input;
            Log << system_log_string << endl;
            cout  <<system_log_string << endl;
        }else{

            input = Program_Header_System.Program_String();

            if(input != ""){
                system_log_string = "program_input=" + input;
                Log << system_log_string << endl;
                cout << system_log_string << endl;
            }
        }

        if(Program_Header_System.Menu_State() == -1 && Program_Header_System.Program_State() == 0 ){Program_Header_System.replace_load_menu();cout << "replace" << endl;}
    }
    if(Program_Header_System.Program_State() == -1){
        if( (!load_external_file && !set_save_folder) && system_ref_image.isAllocated() ){
            if(Image_Selector_Menu.mouse_click(x,y)){
                int image_selected = Image_Selector_Menu.Menu_State();
                system_log_string = "image_selected=" + Image_Selector_Menu.Button_String(image_selected);
                Log << system_log_string << endl;
                cout << system_log_string << endl;
                if(image_selected == 0){
                    lalala.update(my_mouse_x,my_mouse_y,"diffuse");
                    Program_Header_System.Set_Sub_Menu(Image_Layers[0]->Get_Program_Menu());
                    Image_Layers[1]->got_reference = false;
                    Image_Layers[2]->got_reference = false;
                }else if(image_selected == 1){
                    lalala.update(my_mouse_x,my_mouse_y,"height");
                    Image_Layers[1]->got_reference = false;
                    Program_Header_System.Set_Sub_Menu(Image_Layers[1]->Get_Program_Menu());
                    Image_Layers[2]->got_reference = false;
                }else if(image_selected == 2){
                    lalala.update(my_mouse_x,my_mouse_y,"normal");
                    Program_Header_System.Set_Sub_Menu(Image_Layers[2]->Get_Program_Menu());
                }
            }
        }
    }


    if( set_save_folder || (load_external_file && system_ref_image.isAllocated()) ){
        if(back_button.mouse_click(x,y)){
            load_external_file = false;
            set_save_folder = false;
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
    cout << "load setting: " << load_external_file << endl;
    cout << "-----------------------------------------\n" << endl;

    lalala.update(my_mouse_x,my_mouse_y,Program_Header_System.Program_String());
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
    if(load_external_file){
        string file_name = "";
        std::size_t found = dragInfo.files[0].find('.');
        cout << "number of files " << dragInfo.files.size() << endl;

        if (found==std::string::npos){
            save_counter_str = "f" + dragInfo.files[0];
            Log << "dragInfo_loadfolder=" << dragInfo.files[0] << endl;
        }else{
            save_counter_str = "i";
            for(int i = 0; i < dragInfo.files.size(); i++){
                save_counter_str += dragInfo.files[i] + ",";
                Log << "dragInfo_loadfile=" << dragInfo.files[i] << endl;
            }
        }
    }
    if(set_save_folder){
        int tmp_counter = 0;
        string tmp_cstr  = dragInfo.files[0];
        bool folder_found = false;
        while(!folder_found && tmp_counter < available_drives.size()){
            tmp_cstr  =  available_drives[tmp_counter] + dragInfo.files[0];
            if(check_path(tmp_cstr,false)){
                cout << tmp_cstr << endl;
                folder_found = true;
            }
            tmp_counter++;
        }
        if(folder_found){save_folder_name = tmp_cstr;cout << tmp_cstr << endl;}

        Log << save_folder_name << endl;
        ofFile pf;
        pf.open("program_files/save_info.txt", ofFile::WriteOnly, false);
        pf << save_folder_name;
        pf.close();

        Log << "dragInfo_savefolder=" << save_folder_name << endl;

        lalala.update(my_mouse_x,my_mouse_y,"folder");
        //set_save_folder = false;
    }
}

void ofApp::load_dragInfo_file(string filename){
    string file_name = "";

    vector<string> files;
    for(int i = 1; i < filename.size(); i++){
        if(filename.at(i) != ','){
            file_name += filename.at(i);
        }else{
            files.push_back(file_name);
            cout << "file found: "<< file_name << endl;
            Log << "file_found=" << file_name << endl;
            file_name = "";
        }
    }
    bool could_load = false;
    for(int i = 0; i < files.size(); i++){

        file_name = files[i];
        unsigned found = file_name.find_last_of('.');
        string file_format = file_name.substr(found+1);
        if (found!=std::string::npos){
            ofPixels pix;
            string driveInfo = "";
            string tmp_cstr  = file_name;
            int tmp_counter = 0;
            could_load = ofLoadImage(pix,tmp_cstr);
            bool break_loop = false;
            if(could_load){break_loop = true;cout << "loading file "<< tmp_cstr << endl;}

            while(!break_loop){
                tmp_cstr  = available_drives[tmp_counter] + file_name;

                could_load = ofLoadImage(pix,tmp_cstr);

                if(could_load){
                    if(tmp_counter != -1){driveInfo = available_drives[tmp_counter];}
                    break_loop = true;
                }
                if(tmp_counter > available_drives.size() - 1){
                    break_loop = true;
                }
                tmp_counter++;
            }
            cout << "loading file "<< tmp_cstr << endl;
            if(could_load){
                unsigned found = file_name.find_last_of("/\\");
                file_name = file_name.substr(found+1);
                string save_file = "images/" + file_name;
                Log << "file_saved=" << tmp_cstr << endl;
                ofSaveImage(pix,ofToDataPath(save_file) , OF_IMAGE_QUALITY_BEST );
            }else{
                Log << "load failed=" << tmp_cstr << endl;
                file_name = "";
                cout << "load failed" << endl;
            }
        }else{
            Log << "load failed=" << file_name << endl;
            file_name = "";
            cout << "load failed" << endl;
        }
    }
    if(could_load){load_image(file_name);cout << "loaded file "<< file_name  << endl;}

    Program_Header_System.replace_load_menu();

}

void ofApp::load_dragInfo_folder(string foldername){
    string folder_location = foldername + "\\";
    string file_name =  "";
    vector<string> tmp = load_folder(folder_location,false);
    if(tmp.size() == 0){
        string driveInfo = "";
        string tmp_cstr  = "";
        int tmp_counter = 0;
        bool folder_found = false;
        while(tmp.size() == 0 && tmp_counter < available_drives.size()){
            tmp_cstr  =  available_drives[tmp_counter] + folder_location;
            tmp = load_folder(tmp_cstr,false);
            if(tmp.size() != 0){
                cout << tmp_cstr << endl;
                folder_found = true;
                driveInfo = available_drives[tmp_counter];
            }
            tmp_counter++;
        }
        if(folder_found){
            for(int i = 0; i < tmp.size(); i++){
                file_name =  tmp[i];
                unsigned found = file_name.find_last_of('.');
                string file_format = file_name.substr(found+1);
                if(found){
                    if(file_format == "jpg" || file_format == "JPG" || file_format == "JPEG"
                       || file_format == "png"
                       || file_format == "tga"
                       || file_format == "tiff" )
                    {
                        ofPixels pix;
                        if(ofLoadImage(pix,driveInfo + folder_location + file_name) ){
                            cout << "loading file "<< file_format << endl;
                            string save_file = "images/" + file_name;
                            Log << "file_saved="  << tmp_cstr << endl;
                            ofSaveImage(pix,ofToDataPath(save_file) , OF_IMAGE_QUALITY_BEST );
                        }
                    }else{
                        Log << "load failed=" << tmp_cstr << endl;
                        cout << "load failed" << endl;
                        file_name = "";
                    }
                }else{
                    Log << "load failed=" << tmp_cstr << endl;
                    cout << "load failed" << endl;
                    file_name = "";
                }
            }
        }
    }
    if(file_name != ""){load_image(file_name);cout << "loaded file " << file_name << endl;}

    Program_Header_System.replace_load_menu();
}

void ofApp::find_drives(){
    if(!available_drives.empty() ){available_drives.clear();}

    const int BUFSIZE = 100;
    char buffer[ BUFSIZE ];
    DWORD n = GetLogicalDriveStrings( BUFSIZE, buffer );
    DWORD i =  0;

    string drive_name = "";
    while( i < n )   {
        stringstream drive_name_ss;
        int t = GetDriveType( &buffer[i] );
        cout << &buffer[i] << " type is " << t << endl;
        if(t == 2 || t == 3 ){
            drive_name_ss << &buffer[i];
            drive_name_ss >> drive_name;
            available_drives.push_back(drive_name);
        }

        i += strlen( &buffer[i] ) + 1 ;
    }
    cout << "Number of drives: " << available_drives.size() << endl;
}
void ofApp::load_image(string filename){

    if(!Image_Layers.empty()){reset_layers();startup_time_string = create_time_string();}
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
    Program_Header_System.Set_Sub_Menu(Image_Layers[0]->Get_Program_Menu());
    Log << "image_selected=" << Image_Selector_Menu.Menu_State() << endl;
    Image_Layers[0]->update(system_ref_image.getPixels());

    Image_Layers[1]->update(Image_Layers[0]->Get_Image());
    Image_Layers[1]->update();

    Image_Layers[2]->update(Image_Layers[0]->Get_Image());
    Image_Layers[2]->update();
    system_log_string = "file_loaded=" + load_file;
    Log << system_log_string << endl;
    load_external_file = false;

    lalala.update(my_mouse_x,my_mouse_y,"load");
}
//--------------------------------------------------------------
void ofApp::save_image(int layer_number){

    ofImage tmp_image;
    tmp_image.loadImage(filename_of_reference);
    int w = tmp_image.getWidth();
    int h = tmp_image.getHeight();

    unsigned found = filename_of_reference.find_last_of("/\\");
    string save_name = filename_of_reference.substr(found+1);
    string::size_type n;
    n = save_name.find('.');
    int p = save_name.size();
    save_name = save_name.substr (0, n );
    cout << save_name << endl;

    string filename = "";
    unsigned char* tmp_save_image = new unsigned char[w * h * 3];

    if(layer_number == 0)
    {
        filename = "/" + save_name + "_" + startup_time_string + "/" + save_name + "_diff";
        tmp_save_image = create_diffuse(tmp_image.getPixels(), w,h);
        system_ref_image.setFromPixels(tmp_save_image , w,h , OF_IMAGE_COLOR,true);
    }
    else if(layer_number == 1)
    {
        filename = "/" + save_name + "_" + startup_time_string + "/" + save_name + "_height";
        tmp_save_image = greyscale2rgb( create_height ( create_diffuse (tmp_image.getPixels(), w,h), w,h),w ,h);
        system_ref_image.setFromPixels(tmp_save_image , w,h , OF_IMAGE_COLOR,false);
    }
    else if(layer_number == 2)
    {
        filename = "/" + save_name + "_" + startup_time_string + "/" + save_name +  "_norm";
        if(Image_Layers[layer_number]->Image_Channel_Count() == 3){
            cout << "rgb" << endl;
            tmp_save_image = create_normal(create_diffuse (tmp_image.getPixels(), w,h), w,h);
            system_ref_image.setFromPixels(tmp_save_image , w,h , OF_IMAGE_COLOR,true);
        }else if(Image_Layers[layer_number]->Image_Channel_Count() == 1){
            cout << "grey" << endl;
            tmp_save_image = greyscale2rgb( create_normal(create_diffuse (tmp_image.getPixels(), w,h), w,h) , w,h);
            system_ref_image.setFromPixels(tmp_save_image , w,h , OF_IMAGE_COLOR,false);
        }

    }


    ofPixels pix = system_ref_image.getPixelsRef();
    string destination =  save_folder_name + filename + ofToString(save_counter[layer_number]) + save_format;
    save_counter[layer_number]++;
    cout << "Pixels is set!" << endl;
    ofFile newFile(ofToDataPath(destination)); //file doesn't exist yet
    newFile.create();
    cout << "File open!" << endl;
    ofSaveImage(pix,ofToDataPath(destination) , OF_IMAGE_QUALITY_BEST );
    cout << "File saved!" << endl;
    newFile.close();
    cout << "File closed!" << endl;
    cout << 0 <<endl;
    system_ref_image.loadImage(filename_of_reference);
    system_ref_image.resize(512,512);
    cout << 1 <<endl;
    w = system_ref_image.getWidth();
    h = system_ref_image.getHeight();
    cout << 2 <<endl;
    create_height( create_diffuse (system_ref_image.getPixels(), w,h), w,h);
    cout << 3 <<endl;
    create_normal( create_diffuse (system_ref_image.getPixels(), w,h), w,h);
    cout << 4 <<endl;
    delete [] tmp_save_image;
    cout << 5 <<endl;
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

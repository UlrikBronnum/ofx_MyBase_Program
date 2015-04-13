#include "test_questionnaire.h"


void test_questionnaire::set_questionnaire(){
    if(counter == 0 ){
        question_string = "Load any image";
    }else if(counter == 1 ){
        question_string = "Apply a gamma filter to the image and adjust it";
    }else if(counter == 2 ){
        question_string = "Apply a contrast filter to the image and adjust it";
    }else if(counter == 3 ){
        question_string = "Apply a mean blur filter and adjust the kernel size";
    }else if(counter == 4 ){
        question_string = "Save the diffuse image";
    }else if(counter == 5 ){
        question_string = "Switch to the height image";
    }else if(counter == 6 ){
        question_string = "Change the save format to targa (.tga)";
    }else if(counter == 7 ){
        question_string = "Switch to the normal image";
    }else if(counter == 8 ){
        question_string = "Adjust the roughness";
    }else if(counter == 9 ){
        question_string = "Save all images";
    }else if(counter == 10 ){
        question_string = "Change the location where the program saves the image output to a folder of your choice";
    }else if(counter == 11 ){
        question_string = "Load a new image into the program";
    }
}
void test_questionnaire::exit(){
    string filename = savelocation + "/result_user" + ofToString(user_count) + ".txt";
    save_results.open(filename, ofFile::WriteOnly, false);
    for(int i = 0 ; i < 12 ; i++){
        counter = i;
        set_questionnaire();
        string greating = ofToString(counter+1) + ". " + question_string;

        save_results << result[i].first << " " << result[i].second << endl;
    }
    save_results.close();
}
void test_questionnaire::setup(int window_w, int window_h, string folder_string){

    saveData = false;

    Window_Width = window_w;
    Window_Height = window_h;

    savelocation = folder_string;

    ofFile pf;
    string fileContent;
    pf.open("program_files/index.txt", ofFile::ReadOnly, false);
    pf >> fileContent;
    pf.close();

    user_count = ofToInt(fileContent);

    if(fileContent != ""){
        cout << fileContent << endl;
    }

    counter = 0;

    done = false;
    received_answer = false;

    display_strings[0] =  "1. How would you rate the difficulty of this task?";
    display_strings[1] =  "2. The navigation of the program interface is logical?";

    set_questionnaire();


    vector<string> labels;
	labels.push_back("Very difficult");
	labels.push_back("Difficult");
	labels.push_back("Neutral");
	labels.push_back("Easy");
	labels.push_back("Very easy");

    menu_1.setup(window_w/labels.size(),60,false,false);
    for(int i = 0; i < labels.size() ; i++){
        menu_1.add_button(labels[i],true);
    }

    labels.clear();
    labels.push_back("Strongly disagree");
	labels.push_back("Disagree");
	labels.push_back("Neutral");
	labels.push_back("Agree");
	labels.push_back("Strongly agree");

    menu_2.setup(window_w/labels.size(),60,false,false);
    for(int i = 0; i < labels.size() ; i++){
        menu_2.add_button(labels[i],true);
    }

    button_next.setup(window_w/10,40,"Next",false);
    button_prev.setup(window_w/10,40,"Previous",false);

}
void test_questionnaire::update(){

    if(menu_1.Menu_State() != -1 && menu_2.Menu_State() != -1){
        received_answer = true;
    }
}
void test_questionnaire::draw(){

    ofSetColor(255);
    if(!done){
        menu_1.draw(2,Window_Height/10 * 4,200,Window_Width,Window_Height);
        menu_2.draw(2,Window_Height/10 * 6,200,Window_Width,Window_Height);

        if(received_answer){
            button_next.draw(Window_Width - Window_Width/10,Window_Height/10 * 8,200);
        }
        if(counter){
            button_prev.draw(2,Window_Height/10 * 8,200);
        }

        ofSetColor(255);
        string greating = ofToString(counter+1) + ". Task was:";
        ofDrawBitmapString(greating, Window_Width / 2 - (greating.size() * 8 /2), Window_Height/10 * 2 );

        ofSetColor(255);
        ofDrawBitmapString(question_string, Window_Width / 2 - (question_string.size() * 8 /2), Window_Height/10 * 2.5 );

        ofSetColor(255);
        ofDrawBitmapString(display_strings[0],Window_Width / 2 - (display_strings[0].size() * 8 /2),Window_Height/10 * 3.7 );

        ofSetColor(255);
        ofDrawBitmapString(display_strings[1],Window_Width / 2 - (display_strings[1].size() * 8 /2),Window_Height/10 * 5.7 );

    }
}
void test_questionnaire::mouse_hover(int x, int y ){

    menu_1.mouse_hover(x,y);
    menu_2.mouse_hover(x,y);

    button_next.mouse_hover(x,y);
    button_prev.mouse_hover(x,y);
}

//--------------------------------------------------------------
void test_questionnaire::mouse_click(int x, int y){

    menu_1.mouse_click(x,y);
    menu_2.mouse_click(x,y);

    if(received_answer){
        if(button_next.mouse_click(x,y)){

            result[counter].first = menu_1.Menu_State();
            result[counter].second = menu_2.Menu_State();
            //cout << result[counter].first << " " << result[counter].second << endl;

            if(counter > 10) {done = true; exit();cout << result[counter].first << " " << result[counter].second << endl;} else { counter++; }
            received_answer = false;
            menu_1.Reset_Menu();
            menu_2.Reset_Menu();
            set_questionnaire();

        }
    }
    if(button_prev.mouse_click(x,y)){
        if(counter > 0){counter--;}
        received_answer = false;
        menu_1.Reset_Menu();
        menu_2.Reset_Menu();
        set_questionnaire();
    }

}

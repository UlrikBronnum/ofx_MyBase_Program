#include "ofx_Program.h"

//------------------------- Setup -----------------------------------
void ofx_Program::setup (){

    program_state = -1;
    menu_state = -1;
    sub_state = -1;

    set_dimensions(1024/8,25);

    vector<string> labels;
	labels.push_back("File");
	labels.push_back("Filter");

    create_program_menu(labels);


    // File menu's

    _Program_Menu_Content[0]->add_button("Load");
    labels.clear();
    labels.push_back("Load External");
    vector<string> tmp = load_folder("\\data\\images\\",true);
    labels.insert(labels.end(), tmp.begin(), tmp.end());
    _Program_Menu_Content[0]->add_sub_menu(labels,false,0);

    labels.clear();
    labels.push_back("Diffuse Texture");
    labels.push_back("Height Texture");
    labels.push_back("Normal Texture");
    labels.push_back("All");
	_Program_Menu_Content[0]->add_button("Save");
    _Program_Menu_Content[0]->add_sub_menu(labels,false,1);

    labels.clear();
    labels.push_back(".png");
    labels.push_back(".jpg");
    labels.push_back(".tga");
    labels.push_back(".tiff");
    _Program_Menu_Content[0]->add_button("Save Format");
    _Program_Menu_Content[0]->add_sub_menu(labels,false,2);

    labels.clear();
    labels.push_back("Set save folder");
    _Program_Menu_Content[0]->add_button("Properties");
    _Program_Menu_Content[0]->add_sub_menu(labels,false,3);

    labels.clear();
    _Program_Menu_Content[0]->add_button("Exit");
    _Program_Menu_Content[0]->add_sub_menu(labels,false,4);


    /*

    labels.clear();
	labels.push_back("Introduction");
	labels.push_back("Qeustionnaire");
	labels.push_back("Program Info");

    _Program_Menu_Content[3]->add_button("Introduction");
    _Program_Menu_Content[3]->add_sub_menu(tmp,false,0);
	_Program_Menu_Content[3]->add_button("Qeustionnaire");
    _Program_Menu_Content[3]->add_sub_menu(labels,false,1);
    _Program_Menu_Content[3]->add_button("Program Info");
    _Program_Menu_Content[3]->add_sub_menu(labels,false,2);
    */
    for(int i = 0; i < _Program_Menu_Content.size() ; i++){
         _Program_Menu_Content[i]->Reset_Menu();
    }

}


#pragma once

#include "ofMain.h"
#include <string>

#include "ofx_Button.h"

#include "ofx_Icons.h"
#include "ofx_Menu.h"
#include "ofx_Program.h"

#include "ofx_Layer.h"
#include "ofxQtVideoSaver.h"


#include "test_runner.h"

#define program_version "version_1.0"
#define my_record FALSE


class ofApp : public ofBaseApp , public ofx_Loader {

	public:
		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);


        void load_dragInfo_file(string filename);
        void load_dragInfo_folder(string foldername);
		void save_image(int layer_number);
		void load_image(string filename);
		void find_drives();
		void reset_layers();


		unsigned char* create_diffuse(unsigned char* image ,int w ,int h );
		unsigned char* create_height(unsigned char* image,int w ,int h);
		unsigned char* create_normal(unsigned char* image,int w ,int h);
        unsigned char* greyscale2rgb(unsigned char* image,int w ,int h);


        test_runner lalala;

		string create_time_string();


        ofx_Program Program_Header_System;

        ofx_Menu Image_Selector_Menu;

        string filename_of_reference;
        string system_log_string;
        string save_folder_name;
        string save_format;

        ofx_Button back_button;
        bool load_external_file;
        bool set_save_folder;


        ofImage system_ref_image;
        vector<ofx_Icons*> system_icons;

        vector<ofx_Layer*> Image_Layers;
        vector<int>        save_counter;

        vector<string>     available_drives;


        int my_mouse_x;
        int my_mouse_y;

        int Window_Width;
        int Window_Height;


        int aux_Window_Width;
        int aux_Window_Height;

        ofVideoGrabber 		vidGrabber;

        ofImage main_window;
        ofxQtVideoSaver save_main_window;
        ofImage aux_window;
        ofxQtVideoSaver save_webcam_window;

        ofFile Log;
        string save_counter_str;
        string startup_time_string;


        int  user_count;

};

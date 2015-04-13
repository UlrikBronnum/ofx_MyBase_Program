#ifndef TEST_QUESTIONNAIRE_H
#define TEST_QUESTIONNAIRE_H

#include "ofMain.h"

#include "ofx_Button.h"
#include "ofx_Menu.h"

struct Score{
    int first;
    int second;

    Score(){
        first = -1;
        second = -1;
    }
};

class test_questionnaire
{
    public:
        test_questionnaire(){}
        virtual ~test_questionnaire(){}

        void setup(int window_w, int window_h, string folder_string);
		void update();
		void draw();
		void exit();

		void mouse_click(int x, int y);
		void mouse_hover(int x, int y);

        bool  done;

    protected:


        void set_questionnaire();

		Score result[12];

		ofx_Button button_next,  button_prev;

		ofx_Menu   menu_1;
		ofx_Menu   menu_2;

        int Window_Width;
        int Window_Height;

        int counter;
        bool received_answer ;

        string display_strings[2];
        string question_string;

        int user_count;

        ofFile save_results;

        string savelocation;

        bool saveData;

    private:
};

#endif // TEST_QUESTIONNAIRE_H

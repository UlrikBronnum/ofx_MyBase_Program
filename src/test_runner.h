#ifndef TEST_RUNNER_H
#define TEST_RUNNER_H

#include "ofMain.h"

#include "test_questionnaire.h"
#include "ofx_Button.h"

class test_runner
{
    public:
        test_runner(){  test_button.setup(160,60,"Understood",false);
                        isRunning = true;
                        count_tasks = 0;
                        set_string();
                        delay_time = 3000;
                        done = false;
                        question_time = false;
                        test_done = false;
                        }
        virtual ~test_runner(){}

        void setup (int window_w, int window_h , string folder_string);
        void update(int mouse_x, int mouse_y, string program_string);
        void draw (int window_w, int window_h);

        void mouse_click(int x,int y);
        void mouse_hover(int x,int y);

        void set_string();
        void set_save_folder(string folder_string){
            save_location = folder_string;
        }

        bool done;
        bool isRunning;
        string test_task;

        test_questionnaire qna;

    protected:

        bool firstDone;
        bool test_done;
        bool question_time;

        int count_tasks;

        int delay_time;

        ofFile time_distance_data;
        ofx_Button test_button;

        unsigned long long time;
        unsigned long long delayTime;

        string save_location;
    private:
};

#endif // TEST_RUNNER_H

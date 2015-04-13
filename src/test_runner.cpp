#include "test_runner.h"

void test_runner::setup(int window_w, int window_h, string folder_string){
    save_location = folder_string;
    qna.setup(window_w, window_h,save_location);
    time_distance_data.open(save_location +"/test_log.txt", ofFile::WriteOnly, false);

}

void test_runner::update(int mouse_x, int mouse_y, string program_string){

    unsigned long long nTime = ofGetElapsedTimeMillis();

    unsigned long long elapsedTime = 0;

    if( !isRunning && !test_done){
        elapsedTime = nTime - time;
        if(delayTime == 0){
            time_distance_data << count_tasks << ": time="<<  elapsedTime << endl;
            time_distance_data << "x=" << mouse_x <<":y="<< mouse_y << endl;
        }

        if(program_string == "load" && count_tasks == 0)
        {
            time_distance_data << count_tasks  << ": done=" <<elapsedTime << endl;
            time_distance_data << "x=" << mouse_x <<":y="<< mouse_y << endl;
            delayTime = nTime + delay_time;

        }
        else if(count_tasks == 1 )
        {
            if(program_string == "gamma"){
                time_distance_data << count_tasks  << ": first=" <<elapsedTime << endl;
                time_distance_data << "x=" << mouse_x <<":y="<< mouse_y << endl;
                firstDone = true;
            }else if(program_string == "drag" && firstDone){
                time_distance_data << count_tasks  << ": done=" <<elapsedTime << endl;
                time_distance_data << "x=" << mouse_x <<":y="<< mouse_y << endl;
                delayTime = nTime + delay_time;
            }
        }

        else if(count_tasks == 2 )
        {
            if(program_string == "contrast"){
                time_distance_data << count_tasks  << ": first=" <<elapsedTime << endl;
                time_distance_data << "x=" << mouse_x <<":y="<< mouse_y << endl;
                firstDone = true;
            }else if(program_string == "drag" && firstDone){
                time_distance_data << count_tasks  << ": done=" <<elapsedTime << endl;
                time_distance_data << "x=" << mouse_x <<":y="<< mouse_y << endl;
                delayTime = nTime + delay_time;
            }
        }
        else if(count_tasks == 3 )
        {
            if(program_string == "mean_filter"){
                time_distance_data << count_tasks  << ": first=" <<elapsedTime << endl;
                time_distance_data << "x=" << mouse_x <<":y="<< mouse_y << endl;
                firstDone = true;
            }else if(program_string == "drag" && firstDone){
                time_distance_data << count_tasks  << ": done=" <<elapsedTime << endl;
                time_distance_data << "x=" << mouse_x <<":y="<< mouse_y << endl;
                delayTime = nTime + delay_time;
            }
        }
        else if(program_string == "Diffuse Texture" && count_tasks == 4 ){
            time_distance_data << count_tasks  << ": done=" <<elapsedTime << endl;
            time_distance_data << "x=" << mouse_x <<":y="<< mouse_y << endl;
            delayTime = nTime + delay_time;

        }
        else if(program_string == "height" && count_tasks == 5 ){
            time_distance_data << count_tasks  << ": done=" <<elapsedTime << endl;
            time_distance_data << "x=" << mouse_x <<":y="<< mouse_y << endl;
            delayTime = nTime + delay_time;
        }
        else if(program_string == ".tga" && count_tasks == 6 ){
            time_distance_data << count_tasks  << ": done=" <<elapsedTime << endl;
            time_distance_data << "x=" << mouse_x <<":y="<< mouse_y << endl;
            delayTime = nTime + delay_time;
        }
        else if(program_string == "normal" && count_tasks == 7 ){
            time_distance_data << count_tasks << ": done=" <<elapsedTime << endl;
            time_distance_data << "x=" << mouse_x <<":y="<< mouse_y << endl;
            delayTime = nTime + delay_time;
        }
        else if(program_string == "drag" && count_tasks == 8 ){
            time_distance_data << count_tasks << ": done=" <<elapsedTime << endl;
            time_distance_data << "x=" << mouse_x <<":y="<< mouse_y << endl;
            delayTime = nTime + delay_time;
        }
        else if( count_tasks == 9 ){
            if(program_string == "All"){
                time_distance_data << count_tasks  << ": first=" <<elapsedTime << endl;
                time_distance_data << "x=" << mouse_x <<":y="<< mouse_y << endl;
                firstDone = true;
            }else if(program_string == "all" && firstDone){
                time_distance_data << count_tasks  << ": done=" <<elapsedTime << endl;
                time_distance_data << "x=" << mouse_x <<":y="<< mouse_y << endl;
                delayTime = nTime + delay_time;
            }
        }
        else if(program_string == "folder" && count_tasks == 10 ){
            time_distance_data << count_tasks << ": done=" <<elapsedTime << endl;
            time_distance_data << "x=" << mouse_x <<":y="<< mouse_y << endl;
            delayTime = nTime + delay_time;
        }
        else if(program_string == "load" && count_tasks == 11 ){
            time_distance_data << count_tasks << ": done=" <<elapsedTime << endl;
            time_distance_data << "x=" << mouse_x <<":y="<< mouse_y << endl;
            delayTime = nTime + delay_time;
        }

        if(delayTime < nTime && delayTime != 0 ){
            isRunning = true;
            firstDone = false;
            delayTime = 0;
            count_tasks++;
            set_string();
        }
    }else if (question_time){

        if(qna.done){
            count_tasks++;
            done = true;
            set_string();
        }else{
            qna.update();
        }
    }


}
void test_runner::draw (int window_w, int window_h){



    if(isRunning ){

        if(!question_time){
            ofSetColor(255);
            test_button.draw(window_w/2 - test_button.Width()/2, window_h/3 * 2,200);
        }else if(!qna.done){
            ofSetColor(255);
            qna.draw();
        }else if(qna.done){
            ofSetColor(255);
            string greating = "Thank you! Now a little interview.";
            ofDrawBitmapString(greating, window_w / 2 - (greating.size() * 8 /2), window_h/10 * 2 );
        }
    }

    if(test_done && !question_time && !isRunning){
        ofSetColor(255);
        test_button.draw(window_w/2 - test_button.Width()/2, window_h/10 * 9,200);
        ofSetColor(255);
        ofDrawBitmapString(test_task,window_w / 2 - (test_task.size() * 8 /2),55);
    }else if(count_tasks < 12){
        ofSetColor(255);
        ofDrawBitmapString(test_task,window_w / 2 - (test_task.size() * 8 /2),55);
    }

}

void test_runner::mouse_click(int x,int y){

    unsigned long long nTime = ofGetElapsedTimeMillis();
    unsigned long long elapsedTime = 0;

    if( isRunning || test_done){
        if(test_button.mouse_click(x,y)){
            if(test_done){
                isRunning = true;
                question_time = true;
            }else{
                if(time != 0){elapsedTime = nTime - time;}else{elapsedTime = 0;}
                time_distance_data << count_tasks << ": press=" << elapsedTime << endl;
                time_distance_data << "x=" << x <<":y="<< y << endl;
            }

            if(!question_time || !test_done){
                time = ofGetElapsedTimeMillis();
                isRunning = false;
            }



        }
        if(question_time){
            qna.mouse_click(x,y);
        }
    }else if( !isRunning){

        if(time != 0){elapsedTime = nTime - time;}else{elapsedTime = 0;}

        time_distance_data << count_tasks << ": press=" << elapsedTime << endl;
        time_distance_data << "x=" << x <<":y="<< y << endl;
    }

}
void test_runner::mouse_hover(int x,int y){
    if( isRunning || test_done){
        test_button.mouse_hover(x,y);
    }
    if(question_time){
        qna.mouse_hover(x,y);
    }

}
void test_runner::set_string(){
    if(count_tasks == 0 ){
        test_task = "Load any image";
    }else if(count_tasks == 1 ){
        test_task = "Apply a gamma filter to the image and adjust it";
    }else if(count_tasks == 2 ){
        test_task = "Apply a contrast filter to the image and adjust it";
    }else if(count_tasks == 3 ){
        test_task = "Apply a mean blur filter and adjust the kernel size";
    }else if(count_tasks == 4 ){
        test_task = "Save the diffuse image";
    }else if(count_tasks == 5 ){
        test_task = "Switch to the height image";
    }else if(count_tasks == 6 ){
        test_task = "Change the save format to targa (.tga)";
    }else if(count_tasks == 7 ){
        test_task = "Switch to the normal image";
    }else if(count_tasks == 8 ){
        test_task = "Adjust the roughness";
    }else if(count_tasks == 9 ){
        test_task = "Save all images";
    }else if(count_tasks == 10 ){
        test_task = "Change the location where the program saves the image output to a folder of your choice";
    }else if(count_tasks == 11 ){
        test_task = "Load a new image into the program";
    }else if(count_tasks == 12 ){
        test_task = "Feel free to explore, when done press Continue";
        test_done = true;
        test_button.Set_Label("Continue");
        isRunning = false;
    }
}

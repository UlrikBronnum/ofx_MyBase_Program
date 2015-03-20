#ifndef OFX_PROGRAM_H
#define OFX_PROGRAM_H

#include <ofx_App.h>


class ofx_Program : public ofx_App
{
    public:
        ofx_Program() : ofx_App() {}
        virtual ~ofx_Program(){}

        //------------------------- Setup -----------------------------------
        void setup ();
        void setup (ofx_MenuSub* menu){}

        void replace_load_menu(){
            vector<string> tmpstr;
            vector<string> tmp = load_folder("\\data\\images\\",true);
            tmpstr.push_back("Load External");
            tmpstr.insert(tmpstr.end(), tmp.begin(), tmp.end());
            _Program_Menu_Content[0]->reset_sub_menu(tmpstr,0);
        }

};

#endif // OFX_PROGRAM_H

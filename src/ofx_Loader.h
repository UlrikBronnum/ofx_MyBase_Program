#ifndef OFX_LOADER_H
#define OFX_LOADER_H

#include "ofMain.h"

class ofx_Loader
{
    public:
        ofx_Loader() {}
        virtual ~ofx_Loader() {}




        //--------------------------------------------------------------
        //-------------------- Access Filesystem -----------------------
        //--------------------------------------------------------------
        vector<string> load_folder(string folder_path, bool local_folder){
            vector<string> names;
            string folder;
            if(local_folder){
                folder = return_program_path() + folder_path;
            }else{
                folder = folder_path;
            }

            char search_path[200];
            sprintf(search_path, "%s*.*", folder.c_str());
            WIN32_FIND_DATA fd;
            HANDLE hFind = ::FindFirstFile(search_path, &fd);
            if(hFind != INVALID_HANDLE_VALUE)
            {
                do
                {
                    // read all (real) files in current folder
                    // , delete '!' read other 2 default folder . and ..
                    if(! (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
                    {
                        names.push_back(fd.cFileName);
                    }
                }while(::FindNextFile(hFind, &fd));
                ::FindClose(hFind);
            }
            return names;
        }
        //--------------------------------------------------------------
        string return_program_path(){
            char buffer[MAX_PATH];
            GetModuleFileNameA( NULL, buffer, MAX_PATH );
            string::size_type pos = string( buffer ).find_last_of( "\\/" );
            string pathToExe = string( buffer ).substr( 0, pos);
            return pathToExe;
        }
        //--------------------------------------------------------------
        unsigned char* image_importer(string filename, int width, int height){
            // opFrameworks
            ofImage import_image;
            string load_file_named = "images/" + filename;
            import_image.loadImage(load_file_named);
            import_image.resize(512,512);
            return import_image.getPixels();
        }


    protected:

        void set_load_menu(ofx_Menu* menu){
            vector<string> tmp_titles;
            string location_string = "\\data\\images\\";
            tmp_titles = load_folder(location_string,true);
            cout << "size"<< tmp_titles.size()<< endl;
            for(int i = 0 ; i < tmp_titles.size() ; i++){
                menu->add_button(tmp_titles[i],false);
            }
            menu->Reset_Menu();

        }



    private:
};

#endif // OFX_LOADER_H

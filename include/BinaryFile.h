#pragma once
#include <vector>
#include <fstream>
#include "User.h"

class BinaryFile
{
    private:
        string Path;
    public:
        BinaryFile(string path)
        {
            Path = path;
        }
        
        void GrabarDato(User obj)
        {
            FILE* file;
            file = fopen((char*)&Path[0], "ab");
            fwrite((char*)&obj, sizeof(User), 1, file);
            fclose(file);
        }

        vector<User> LeerDato()
        {
            vector<User> objs;
            User obj;
            int size;

            FILE* file;
            file = fopen((char*)&Path[0], "rb");

            fread(&obj, sizeof(User), 1, file);

            while(!feof(file))
            {
                objs.push_back(obj);
                fread(&obj, sizeof(User), 1, file);
            };

            fclose(file);

            return objs;
        }
};
#include <iostream>
#include <fstream>
#include <string>
#include "Artist.h"
using namespace std;

class Archive
{
    private:
        string Path;
        int Type;
    public:
        Archive(){};
        Archive(string path, int type)
        {
            Path = path;
            Type = type;
        }
        
        template <class T>
        void saveNewLine(T obj)
        {
            try
            {
                fstream userArchive;
                userArchive.open(Path, ios :: app);
                if(userArchive.is_open())
                {
                    switch (Type)
                    {
                    case 0:
                        userArchive << obj.getCode() << ";" << obj.getName() << ";" << obj.getEmail() << ";" << obj.getPhoneNumber() << ";" << obj.getUsername() << ";" << obj.getPassword() << ";" << endl;
                        userArchive.close();    
                        break;
                    case 1:
                        // Crear cancion
                    case 2:
                        // Crear playlist
                    default:
                        cout << "Ese tipo de archivo no existe!!!" << endl;
                        break;
                    }
                    
                }
            }catch(exception e)
            {
                cout << "Ocurrio un error al grabar el archivo!!!";
            }
        }
};
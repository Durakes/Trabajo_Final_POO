#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "User.h"
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
        void saveNewLine(T obj)//guarda las lineas csv
        {
            try
            {
                fstream archive;
                archive.open(Path, ios :: app);
                if(archive.is_open())
                {
                    switch (Type)
                    {
                    case 0:
                        archive << obj.getCode() << ";" << obj.getName() << ";" << obj.getEmail() << ";" << obj.getPhoneNumber() << ";" << obj.getUsername() << ";" << obj.getPassword() << ";" << endl;
                        archive.close();    
                        break;
                    case 1:
                        // Crear cancion
                    case 2:
                        // Crear playlist 
                        break;
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


        User crear(vector<string> temp)
        {
            User usuario(temp[0], temp[1], temp[2], temp[3], temp[4], temp[5]);

            return usuario;
        }

        template <class T>
        void cargarDatos(vector<T> *objs)//carga los dtos del archivo en un vector
        {
            try
            {
                int i;
                string line;
                size_t posi; //Cantidad Maxima
                fstream archive;

                archive.open(Path, ios :: in);
                if(archive.is_open())
                {
                    while (!archive.eof())
                    {
                        while (getline(archive, line))
                        {
                            vector<string> temp;
                            while ((posi = line.find(";")) != string::npos /*Valor constante que vale -1*/)
                            {
                                temp.push_back(line.substr(0, posi));
                                line.erase(0, posi+1);
                            }
                            T obj;
                            switch (Type)
                            {
                            case 0:
                                obj=crear(temp);
                                objs->push_back(obj);
                                break;                           
                            default:
                                cout << "No existe ese archivo" << endl;
                                break;
                            }
                        }
                    }
                }
                archive.close();
            }catch(exception e)
            {
                cout << "Ocurrio un error al leer el archivo!!!";
            }
        }
};
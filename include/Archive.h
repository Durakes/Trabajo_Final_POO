#ifndef __ARCHIVE_H__
#define __ARCHIVE_H__
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "User.h"
#include "Cancion.h"
using namespace std;

class Archive
{
    private:
        string Path;
    public:
        Archive(){};
        Archive(string path)
        {
            Path = path;
        }

        string crearLinea(Cancion obj)
        {
            string cancion = to_string(obj.getCodigo()) + ";" + obj.getNombre() + ";" + obj.getAutor() + ";" + to_string(obj.getDuracion()) + ";" + obj.getDireccion() + ";";
            return cancion;
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
                    archive << crearLinea(obj) << endl;
                    archive.close();
                }

            }catch(exception e)
            {
                cout << "Ocurrio un error al grabar el archivo!!!";
            }
        }

        void crearObjeto(vector<string> temp, Cancion *cancion)
        {
            cancion->setCodigo(stoi(temp[0]));
            cancion->setNombre(temp[1]);
            cancion->setAutor(temp[2]);
            cancion->setDuracion(stoi(temp[3]));
            cancion->setDireccion(temp[4]);
        }

        template <class T>
        void cargarDatos(T obj, vector<T> *objs)
        {
            try
            {
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
                            crearObjeto(temp, &obj);
                            objs->push_back(obj);
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
#endif

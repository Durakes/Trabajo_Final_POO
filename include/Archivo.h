#ifndef __ARCHIVO_H__
#define __ARCHIVO_H__

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Usuario.h"
#include "Cancion.h"
#include "Playlist.h"

using namespace std;

class Archivo
{
    private:
        string Ruta;
    public:
        Archivo(){};
        Archivo(string ruta)
        {
            Ruta = ruta;
        }

        string crearLinea(Cancion obj)
        {
            string cancion = to_string(obj.getCodigo()) + ";" + obj.getNombre() + ";" + obj.getAutor() + ";" + to_string(obj.getDuracion()) + ";" + obj.getAlbum() + ";" + to_string(obj.getCodigoAutor()) + ";";
            return cancion;
        }

        string crearLinea(Playlist obj)
        {
            string playlist = to_string(obj.getCodigo()) + ";" + obj.getNombre() + ";" + obj.getUsuario() + ";" + obj.getEstado() + ";";
            return playlist;
        }

        template <class T>
        void grabarNuevaLinea(T obj)
        {
            try
            {
                fstream archivo;
                archivo.open(Ruta, ios :: app);
                if(archivo.is_open())
                {
                    archivo << crearLinea(obj) << endl;
                    archivo.close();
                }

            }catch(exception e)
            {
                cout << "Ocurrio un error al grabar el archivo!!!";
            }
        }

        void crearObjeto(vector<string> temporal, Cancion *cancion)
        {
            cancion->setCodigo(stoi(temporal[0]));
            cancion->setNombre(temporal[1]);
            cancion->setAutor(temporal[2]);
            cancion->setDuracion(stoi(temporal[3]));
            cancion->setAlbum(temporal[4]);
            cancion->setCodigoAutor(stoi(temporal[5]));
        }

        void crearObjeto(vector<string> temporal, Playlist *playlist)
        {
            vector<int> cancionNull;

            playlist->setCodigo(stoi(temporal[0]));
            playlist->setNombre(temporal[1]);
            playlist->setUsuario(temporal[2]);
            playlist->setEstado(temporal[3]);

            if(temporal.size()>4)
            {
                vector<int> canciones;
                for(int i=4; i<temporal.size(); i++)
                {
                    canciones.push_back(stoi(temporal[i]));
                }
                playlist->setCanciones(canciones);
            }else
            {
                playlist->setCanciones(cancionNull);
            }
        }

        template <class T>
        void cargarDatos(T obj, vector<T> *objs)
        {
            try
            {
                string linea;
                size_t posicionFinal;
                fstream archivo;

                archivo.open(Ruta, ios :: in);
                if(archivo.is_open())
                {
                    while (!archivo.eof())
                    {
                        while (getline(archivo, linea))
                        {
                            vector<string> temporal;
                            while ((posicionFinal = linea.find(";")) != string::npos)
                            {
                                temporal.push_back(linea.substr(0, posicionFinal));
                                linea.erase(0, posicionFinal+1);
                            }
                            //T obj;
                            crearObjeto(temporal, &obj);
                            objs->push_back(obj);
                        }
                    }
                }
                archivo.close();
            }catch(exception e)
            {
                cout << "Ocurrio un error al leer el archivo!!!";
            }
        }

        void modificarPlaylist(vector<Playlist> vectorPlaylist)
        {
            try
            {
                fstream archivo;

                archivo.open(Ruta, ios :: out);
                if(archivo.is_open())
                {
                    for(Playlist playlist:vectorPlaylist)
                    {
                        if(playlist.getCanciones().size()!=0)
                        {
                            stringstream concatenador;
                            for(size_t i = 0; i < playlist.getCanciones().size(); ++i)
                            {
                                if(i!=0)
                                {
                                    concatenador << ";";
                                }
                                concatenador << playlist.getCanciones()[i];
                            }
                            string codigos = concatenador.str();

                            archivo << to_string(playlist.getCodigo()) + ";" + playlist.getNombre() + ";" + playlist.getUsuario() + ";" + playlist.getEstado() + ";" + codigos + ";" << endl;
                        }
                        else
                        {
                            archivo << to_string(playlist.getCodigo()) + ";" + playlist.getNombre() + ";" + playlist.getUsuario() + ";" + playlist.getEstado() + ";" << endl;
                        }
                    }
                }
                archivo.close();
            }catch(exception e)
            {
                cout << "Ocurrio un error al modificar el archivo!!!";
            }
        }
};
#endif

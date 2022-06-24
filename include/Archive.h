#ifndef __ARCHIVE_H__
#define __ARCHIVE_H__
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "User.h"
#include "Cancion.h"
#include "playlist.h"
#include <sstream>
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
            string cancion = to_string(obj.getCodigo()) + ";" + obj.getNombre() + ";" + obj.getAutor() + ";" + to_string(obj.getDuracion()) + ";" + obj.getAlbum() + ";" + to_string(obj.getCodigoAutor()) + ";";
            return cancion;
        }

        string crearLinea(Playlist obj){
          string playlist = to_string(obj.getCodigo()) + ";" + obj.getNombre() + ";" + obj.getUsuario() + ";" + obj.getEstado() + ";";
          return playlist;
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
            cancion->setAlbum(temp[4]);
            cancion->setCodigoAutor(stoi(temp[5]));
        }

        void crearObjeto(vector<string> temp, Playlist *playlist)
        {
            vector<int> cancionNull;
            playlist->setCodigo(stoi(temp[0]));
            playlist->setNombre(temp[1]);
            playlist->setUsuario(temp[2]);
            playlist->setEstado(temp[3]);
            if(temp.size()>4){
              vector<int> canciones;
              for(int i=4; i<temp.size(); i++){
                canciones.push_back(stoi(temp[i]));
              }
              playlist->setCanciones(canciones);
            }else{
              playlist->setCanciones(cancionNull);
            }
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

        void modificarPlaylist(vector<Playlist> vectorPlaylist){//esta
        try{
          fstream archive;

          archive.open(Path, ios :: out);
          if(archive.is_open()){
              for(Playlist playlist:vectorPlaylist){
                if(playlist.getCanciones().size()!=0){
                  stringstream ss;
                  for(size_t i=0; i<playlist.getCanciones().size();++i){
                    if(i!=0){
                      ss<<";";
                    }
                    ss<<playlist.getCanciones()[i];
                  }
                  string codigos=ss.str();
                  archive << to_string(playlist.getCodigo()) + ";" + playlist.getNombre() + ";" + playlist.getUsuario() + ";" + playlist.getEstado() + ";" + codigos + ";" << endl;
                }
                else{
                  archive << to_string(playlist.getCodigo()) + ";" + playlist.getNombre() + ";" + playlist.getUsuario() + ";" + playlist.getEstado() + ";" << endl;
                }
              }
          }
          archive.close();
        }catch(exception e)
        {
            cout << "Ocurrio un error al modificar el archivo!!!";
        }
      }
};
#endif

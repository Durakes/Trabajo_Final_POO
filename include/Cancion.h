#ifndef __CANCION_H__
#define __CANCION_H__

#include <iostream>
#include <cmath>
#include <string>
using namespace std;

class Cancion
{
    private:
        int Codigo;
        string Nombre;
        string Autor;
        int Codautor;
        int Duracion;
        string Album;


    public:
        Cancion(){}
        Cancion( string nombre, string autor,string album, int codAut, int duracionSegundos)
        {
            this->Codigo = obtenerCodigo();
            this->Nombre = nombre;
            this->Autor = autor;
            this->Codautor = codAut;
            this->Duracion = duracionSegundos;
            this->Album = album;
        }

        int getCodigo(){ return Codigo; }
        void setCodigo(int codigo){ Codigo = codigo; }
        
        string getNombre(){ return Nombre; }
        void setNombre(string nombre){ Nombre = nombre; }
        
        string getAutor(){ return Autor; }
        void setAutor(string autor){ Autor = autor; }
        
        int getCodigoAutor() {return Codautor;}
        void setCodigoAutor(int codAut) { Codautor = codAut;}

        int getDuracion(){ return Duracion; }
        void setDuracion(int duracion){ Duracion = duracion; }

        string getAlbum(){ return Album; }
        void setAlbum( string direccion ){ this->Album = direccion; }

        string getDatosCompletos()
        {
            string tiempo = to_string(floor(Duracion * 0.016)) + ":";

            if(Duracion % 60 < 10)
            {
                tiempo += "0" + to_string(Duracion % 60);
            }else
            {
                tiempo += to_string(Duracion % 60);
            }

            return (Nombre + " - " + Autor + " " + tiempo);
        }

        int obtenerCodigo()
        {
            int filas = 1;
            ifstream archivo("../docs/Canciones.csv");
            string linea;
            while (getline(archivo, linea))
            filas++;
            archivo.close();
            return filas;
        }

};
#endif

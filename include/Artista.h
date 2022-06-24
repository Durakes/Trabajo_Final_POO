#pragma once
#include <iostream>

using namespace std;

class Artista{
    private:
        string nombre;
        int codArtista;
        int numCanciones;

    public:
        Artista(string nombre, int codArtista, int numCanciones){
            this->nombre = nombre;
            this->codArtista = codArtista;
            this->numCanciones = numCanciones;
        }

        //Setters and getters
        void setNombre(string nombre){this->nombre = nombre;}
        string getNombre(){return nombre;}

        void setCodigo(int codArtista){this->codArtista = codArtista;}
        int getCodigo(){return codArtista;}
        
        void setNumCanciones(int numCanciones){this->numCanciones = numCanciones;}
        int getNumCanciones(){return numCanciones;}
};
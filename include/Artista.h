#ifndef __ARTISTA_H__
#define __ARTISTA_H__
#include <iostream>

using namespace std;

class Artista
{
    private:
        string Nombre;
        int CodArtista;
        int NumCanciones;

    public:
        Artista(string nombre, int codArtista, int numCanciones)
        {
            this->Nombre = nombre;
            this->CodArtista = codArtista;
            this->NumCanciones = numCanciones;
        }

        //Setters and getters
        void setNombre(string nombre){this->Nombre = nombre;}
        string getNombre(){return Nombre;}

        void setCodigo(int codArtista){this->CodArtista = codArtista;}
        int getCodigo(){return CodArtista;}
        
        void setNumCanciones(int numCanciones){this->NumCanciones = numCanciones;}
        int getNumCanciones(){return NumCanciones;}
};
#endif
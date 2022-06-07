#ifndef __CANCION_H__
#define __CANCION_H__

#include<iostream>
#include<cmath>
#include<string>
using namespace std;

class Cancion{
    private:
        int Codigo;
        string Nombre;
        string Autor;       // O podría ser autor*(? Un puntero de objeto autor
        int Duracion; //En segundos
        string Album;

    
    public:
        //Constructor
        Cancion(){}
        Cancion( int codigo, string nombre, string autor, int duracionSegundos, string album){
            this->Codigo = codigo;
            this->Nombre = nombre;
            this->Autor = autor;
            this->Duracion = duracionSegundos;
            this->Album = album;
        }


        /*

            Setters Getters

        */


        void setAlbum( string direccion ){
            this->Album = direccion;
        }

        void setCodigo(int codigo)
        {
            Codigo = codigo;
        }
        
        void setNombre(string nombre)
        {
            Nombre = nombre;
        }

        void setAutor(string autor)
        {
            Autor = autor;
        }

        void setDuracion(int duracion)
        {
            Duracion = duracion;
        }

        int getCodigo(){
            return Codigo;
        }
        string getNombre(){
            return Nombre;
        }
        string getAutor(){
            return Autor;
        }
        int getDuracion(){
            return Duracion;
        }
        string getAlbum(){
            return Album;
        }


        /*

            Metodos/Funciones

        */

        //Regresa los datos de la cancion ordenados
        string getDatosCompletos(){

            string tiempo = to_string( floor(Duracion*0.016) ) 
                            + ":";
                        
            if (Duracion%60 < 10){
                tiempo += "0" + to_string( Duracion % 60 );
            } else {
                tiempo += to_string( Duracion % 60 );
            }

            return ( Nombre + " - " + Autor + " " + tiempo );
        }

        void reproducirCancion(){
            string defecto = "start " + Album;

            char *enviado = &defecto[0];
            cout<<"Reproduciendo: " + Nombre + " - " + Autor;
            system( enviado );
        }


};
#endif
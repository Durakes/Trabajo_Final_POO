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
        int Codautor;
        int Duracion; //En segundos
        string Album;


    public:
        //Constructor
        Cancion(){}
        Cancion( string nombre, string autor,string album, int codAut, int duracionSegundos ){
            this->Codigo = obtenerCodigo(); //Se obtiene el codigo automaticamente
            this->Nombre = nombre;
            this->Autor = autor;
            this->Codautor = codAut;
            this->Duracion = duracionSegundos;
            this->Album = album;
        }


        /*

            Setters Getters

        */

        void setAlbum( string direccion ){ this->Album = direccion; }
        void setCodigo(int codigo){ Codigo = codigo; }
        void setNombre(string nombre){ Nombre = nombre; }
        void setAutor(string autor){ Autor = autor; }
        void setDuracion(int duracion){ Duracion = duracion; }
        void setCodigoAutor(int codAut) { Codautor = codAut;}
        int getCodigo(){ return Codigo; }


        string getNombre(){ return Nombre; }
        string getAutor(){ return Autor; }
        int getCodigoAutor() {return Codautor;}
        int getDuracion(){ return Duracion; }
        string getAlbum(){ return Album; }


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


        // Cuenta la cantidad de filas en el archivo "data_canciones.csv",
        // así se sabe qué codigo de cancion
        int obtenerCodigo(){
            int filas=0;
            ifstream file("../docs/Canciones.csv");
            string line;
            while (getline(file, line))
            filas++;
            file.close();
            return filas;
        }


        void reproducirCancion(){
            string defecto = "start " + Album;

            char *enviado = &defecto[0];
            cout<<"Reproduciendo: " + Nombre + " - " + Autor;
            system( enviado );
        }


};
#endif

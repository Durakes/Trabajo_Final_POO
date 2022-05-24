#include<iostream>
#include<cmath>
using namespace std;

class Cancion{
    private:
        int Codigo;
        string Nombre;
        string Autor;       // O podría ser autor*(? Un puntero de objeto autor
        int Duracion; //En segundos
        string Direccion;

    
    public:
        //Constructor
        Cancion( int codigo, string nombre, string autor, int duracionSegundos, string direccion ){
            this->Codigo = codigo;
            this->Nombre = nombre;
            this->Autor = autor;
            this->Duracion = duracionSegundos;
            this->Direccion = direccion;
        }


        /*

            Setters Getters

        */

        //Cambia la direccion http de la cancion
        void setDireccion( string direccion ){
            this->Direccion = direccion;
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
        string getDireccion(){
            return Direccion;
        }


        /*

            Metodos/Funciones

        */

        //Regresa los datos de la cancion ordenados
        string getDatosCompletos(){

            string tiempo = std::to_string( floor(Duracion*0.016) ) 
                            + ":";
                        
            if (Duracion%60 < 10){
                tiempo += "0" + std::to_string( Duracion % 60 );
            } else {
                tiempo += std::to_string( Duracion % 60 );
            }

            return ( Nombre + " - " + Autor + " " + tiempo );
        }

        void reproducirCancion(){
            string defecto = "start " + Direccion;

            char *enviado = &defecto[0];
            cout<<"Reproduciendo: " + Nombre + " - " + Autor;
            system( enviado );
        }


};
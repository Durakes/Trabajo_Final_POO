#include<iostream>
#include<cmath>
using namespace std;

class Cancion{
    private:
        int codigo;
        string nombre;
        string autor;       // O podría ser autor*(? Un puntero de objeto autor
        int duracion; //En segundos
        string direccion;

    
    public:
        //Constructor
        Cancion( int codigo, string nombre, string autor, int duracionSegundos, string direccion ){
            this->codigo = codigo;
            this->nombre = nombre;
            this->autor = autor;
            this->duracion = duracionSegundos;
            this->direccion = direccion;
        }


        /*

            Setters Getters

        */

        //Cambia la direccion http de la cancion
        void setDireccion( string direccion ){
            this->direccion = direccion;
        }

        int getCodigo(){
            return codigo;
        }
        string getNombre(){
            return nombre;
        }
        string getAutor(){
            return autor;
        }
        int getDuracion(){
            return duracion;
        }
        string getDireccion(){
            return direccion;
        }


        /*

            Metodos/Funciones

        */

        //Regresa los datos de la cancion ordenados
        string getDatosCompletos(){

            string tiempo = std::to_string( floor(duracion*0.016) ) 
                            + ":";
                        
            if (duracion%60 < 10){
                tiempo += "0" + std::to_string( duracion % 60 );
            } else {
                tiempo += std::to_string( duracion % 60 );
            }

            return ( nombre + " - " + autor + " " + tiempo );
        }

        void reproducirCancion(){
            string defecto = "start " + direccion;

            char *enviado = &defecto[0];
            cout<<"Reproduciendo: " + nombre + " - " + autor;
            system( enviado );
        }


};
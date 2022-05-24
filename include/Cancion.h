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
        Cancion( int Codigo, string Nombre, string Autor, int DuracionSegundos, string Direccion ){
            this->Codigo = Codigo;
            this->Nombre = Nombre;
            this->Autor = Autor;
            this->Duracion = DuracionSegundos;
            this->Direccion = Direccion;
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
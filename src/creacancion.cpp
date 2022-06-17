#include<iostream>
#include<string>
#include<math.h>
#include<fstream>
#include"..\include\Cancion.h"
using namespace std;

void verificarEntrada(string tipo){}

void subMenu_CrearCancion( int codigoUsuario, string usuario ){

    string nombre;
    //string nombreArtista es igual al parametro usuario
    double duracion;
    string album;

    string rpta = "Si";


    do {
        //Recibir datos
        cout<<"Nombre de la cancion:"<<endl<<" >";
        getline(cin, nombre);

        /* El autor ya se obtiene automaticamente arriba */

        cout<<"Album de la cancion: "<<endl<<" >";
        getline(cin, album);

        cout<<"Duracion de la cancion:"<<endl;
        cout<<"(Minutos.Segundos)"<<endl<<" >";
        cin>>duracion;
        cin.ignore();

        cout<<"Seguro quieres crear la cancion: "<<endl;
        cout<<"Nombre: \t"<<nombre<<endl;
        cout<<"Autor: \t"<<usuario<<endl;
        cout<<"Album:\t"<<album<<endl;
        cout<<"Duracion: \t"<<duracion<<endl;

        cout<<"[Si] \t [No]"<<endl<<" >";
        cin>>rpta;

        if ( rpta== "Si" || rpta=="si" || rpta=="SI" || rpta=="sI" ){
            duracion = ((int) duracion*60) + (duracion - (int)duracion)*100;
            cout<<(int) duracion<<endl;
            //  Calculo raro: parte_entera*60 + parte_decimal*100

            //Crea el objeto cancion
            Cancion nueva( nombre, usuario, album, codigoUsuario, duracion );

            /*
            Agregar el objeto cancion a vector
            */


            cout<<"Cancion agregada con exito"<<endl;
            cout<<"¿Desea agregar una nueva cancion?"<<endl<<" >";
            cin>>rpta;
        }

        cin.ignore();
    } while ( rpta== "Si" || rpta=="si" || rpta=="SI" || rpta=="sI" );

}

/*
int main(){
    subMenu_CrearCancion(404, "UsuarioPrueba");
}*/

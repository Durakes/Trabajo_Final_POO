#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include "..\include\Cancion.h"
#include "..\include\Auxiliar.h"
#include "..\include\Archivo.h"
using namespace std;

void verificarEntrada(string tipo){}

void crearCancion(int codigoUsuario, string nombreArtista)
{
    string nombre;
    double duracion;
    string album;
    string respuesta = "Si";

    do 
    {
        system("cls");
        aux::cuadro(0,0,60,25);

        aux::gotoxy(1,2);   cout << "Nombre de la cancion >";   getline(cin, nombre);
        aux::gotoxy(1,3); cout << "Album de la cancion >";  getline(cin, album);

        aux::gotoxy(1,4);   cout << "Duracion de la cancion: ";
        aux::gotoxy(1,5);   cout << "(Minutos.Segundos) >";   cin >> duracion;  cin.ignore();

        system("cls");

        aux::cuadro(0,0,60,25);
        aux::gotoxy(1,1);   cout << "Seguro quieres crear la cancion: ";
        aux::gotoxy(1,2);   cout << "Nombre:";  aux::gotoxy(20,2);  cout << nombre;
        aux::gotoxy(1,3);   cout << "Autor:";   aux::gotoxy(20,3);  cout << nombreArtista;
        aux::gotoxy(1,4);   cout << "Album:";   aux::gotoxy(20,4);  cout << album;
        aux::gotoxy(1,5);   cout << "Duracion:";aux::gotoxy(20,5);  cout << duracion;

        aux::gotoxy(1,7);   cout << "(Si o No) >";  getline(cin, respuesta);
        
        aux::aMinuscula(respuesta);
        if (respuesta == "si")
        {
            duracion = ((int) duracion * 60) + (duracion - (int)duracion) * 100;
            Cancion nuevaCancion(nombre, nombreArtista, album, codigoUsuario, duracion);

            Archivo archivo(R"(..\docs\Canciones.csv)");
            archivo.grabarNuevaLinea(nuevaCancion);

            system("cls");
            aux::cuadro(0,0,60,10);
            aux::gotoxy(1,1);   cout << "Cancion agregada con exito";
            aux::gotoxy(1,2);   cout << "Desea agregar una nueva cancion? >";    getline(cin, respuesta);
            aux::aMinuscula(respuesta);
        }
    } while ( respuesta == "si");
}
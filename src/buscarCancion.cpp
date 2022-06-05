#ifndef __BUSCARCANCION_CPP__
#define __BUSCARCANCION_CPP__
#include <iostream>
#include "..\include\BuscarCancion.h"
#include "playlist.cpp"
#include <algorithm>

using namespace std;

void menuBuscar(string codPlaylist)
{
    BuscarCancion objBuscar;
    string titulo, rspta;
    int codCancion;

    do
    {
        string nuevoTit;
        cout<<"Ingrese el titulo de la cancion: ";
        getline(cin,titulo);
        transform(titulo.begin(), titulo.end(), titulo.begin(), ::tolower);
        cout<<"Desea continuar? ";
        cin>>rspta;
        transform(rspta.begin(), rspta.end(), rspta.begin(), ::tolower);
        cin.ignore();

    } while ( rspta!="si");

    system("cls");

    if(objBuscar.getResultados(titulo)==0)
    {
        cout<<"No se encontraron resultados"<<endl;
        system("pause");
        system("cls");
        menuBuscar(codPlaylist);
    }
    else
    {
        objBuscar.imprimirResultados();
        cout<<endl;
        cout<<"Elija una cancion: ";
        cin>>codCancion;
        system("cls");

        objBuscar.getDatos(codCancion-1);
        cout<<endl;

        if (codPlaylist=="0") // determina si se viene del menu principal o una playlist especifica
        {
            objBuscar.fromMainMenu();
        }
        else
        {
            objBuscar.fromPlaylist(codPlaylist);
        }

    }


}

/*int main()
{
    string prueba="01";
    menuBuscar(prueba);
}*/
#endif

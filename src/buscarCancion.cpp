#ifndef __BUSCARCANCION_CPP__
#define __BUSCARCANCION_CPP__
#include <iostream>
#include "..\include\BuscarCancion.h"
#include <algorithm>

using namespace std;

void menuBuscarCancion(string username, string codPlaylist)
{
    BuscarCancion objBuscar;
    string titulo, rspta;
    int codCancion;
    int codigo;
    int opcion;

    do
    {
        cout<<"Ingrese el titulo de la cancion: ";
        getline(cin,titulo);
        transform(titulo.begin(), titulo.end(), titulo.begin(), ::tolower);
        cout<<"Desea buscar la cancion? ";
        cin>>rspta;
        transform(rspta.begin(), rspta.end(), rspta.begin(), ::tolower);
        cin.ignore();

    } while ( rspta!="si");

    system("cls");

    if(objBuscar.getResultados(titulo)==0)
    {
        system("pause");
        system("cls");
        menuBuscarCancion(username, codPlaylist);
    }
    else
    {
        objBuscar.imprimirResultados();
        cout<<endl;
        cout<<"Elija una cancion: ";
        cin>>codCancion;
        system("cls");

        objBuscar.getDatos(codCancion-1);
        codigo=objBuscar.getCodCancion(codCancion-1);
        cout<<endl;

        if (codPlaylist=="0") // determina si se viene del menu principal o una playlist especifica
        {
            objBuscar.fromMainMenu(username, codigo);
            
            cout<<"Realizar otra busqueda       [1]"<<endl;
            cout<<"Regresar al menu principal   [2]"<<endl;
            cout<<"Elija una opcion: ";
            cin>>opcion;
            cin.ignore();
        }
        else
        {
            objBuscar.fromPlaylist(codPlaylist, codigo);

            cout<<"Realizar otra busqueda        [1]"<<endl;
            cout<<"Regresar al menu de Playlist  [2]"<<endl;
            cout<<"Elija una opcion: ";
            cin>>opcion;
            cin.ignore();
        }
    }
   
    switch (opcion)
    {
        case 1:
            system("cls");
            menuBuscarCancion(username, codPlaylist);
            break;
        case 2:
            break;
        default:
            break;
    }

}


/*int main()
{
    string prueba="0";
    menuBuscar(prueba);
}*/

#endif
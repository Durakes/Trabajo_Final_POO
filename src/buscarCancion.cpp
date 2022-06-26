#ifndef __BUSCARCANCION_CPP__
#define __BUSCARCANCION_CPP__
#include <iostream>
#include <algorithm>
#include "..\include\BuscarCancion.h"
#include "..\include\Auxiliar.h"

using namespace std;
void elegirCancion(BuscarCancion objBuscar, string nombreUsuario, string codPlaylist, int codCancion);

void menuBuscarCancion(string nombreUsuario, string codPlaylist)
{
    BuscarCancion objBuscar;
    int codCancion;
    string titulo, respuesta;
    do
    {
        system("cls");
        aux::cuadro(0,0,60, 13);
        aux::gotoxy(1,1);   cout << "Ingrese el titulo de la cancion > ";  getline(cin,titulo);
        transform(titulo.begin(), titulo.end(), titulo.begin(), ::tolower);
        
        aux::gotoxy(1,2);   cout << "Desea buscar la cancion? (si/no) > "; getline(cin,respuesta);
        transform(respuesta.begin(), respuesta.end(), respuesta.begin(), ::tolower);

    } while ( respuesta!="si");

    system("cls");

    if(objBuscar.getResultados(titulo)==0)
    {   
        aux::cuadro(0,0,45, 7);
        aux::gotoxy(1,2);   cout << "No se encontro resultados" << endl;
        aux::gotoxy(1,3);   system("pause");
        menuBuscarCancion(nombreUsuario, codPlaylist);
    }
    else
    {   
        codCancion = objBuscar.imprimirResultados();
        
        elegirCancion(objBuscar, nombreUsuario, codPlaylist, codCancion);
    }
}

void elegirCancion(BuscarCancion objBuscar, string nombreUsuario, string codPlaylist, int codCancion)
{
    system("cls");
    int codigo;
    int opcion;

    objBuscar.getDatos(codCancion-1);
    codigo = objBuscar.getCodCancion(codCancion-1);

        if (codPlaylist == "0")
        {
            
            objBuscar.fromMainMenu(nombreUsuario, codigo);
            system("cls");
            aux::cuadro(0,0,50,10);
            aux::gotoxy(1,1);   cout <<"Realizar otra busqueda";    aux::gotoxy(35,1); cout << "[1]";
            aux::gotoxy(1,2);   cout <<"Regresar al menu principal";    aux::gotoxy(35,2);  cout << "[2]";
            aux::gotoxy(1,3);   cout << "Ingrese la opcion que desea > "; cin >> opcion; cin.ignore();
        }
        else
        {
            objBuscar.fromPlaylist(codPlaylist, codigo);
            system("cls");
            aux::cuadro(0,0,50,10);
            aux::gotoxy(1,1);   cout <<"Realizar otra busqueda";    aux::gotoxy(35,1); cout << "[1]";
            aux::gotoxy(1,2);   cout <<"Regresar al menu principal";    aux::gotoxy(35,2);  cout << "[2]";
            aux::gotoxy(1,3);   cout << "Ingrese la opcion que desea > "; cin >> opcion; cin.ignore();
        }

        switch (opcion)
        {
            case 1:
                system("cls");
                menuBuscarCancion(nombreUsuario, codPlaylist);
                break;
            case 2:
                break;
            default:
                break;
        }
}

#endif
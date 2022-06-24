#ifndef __BUSCARCANCION_CPP__
#define __BUSCARCANCION_CPP__
#include <iostream>
#include "..\include\BuscarCancion.h"
#include "..\include\Auxiliar.h"
#include <algorithm>

using namespace std;
void elegirCancion(BuscarCancion objBuscar, string username, string codPlaylist, int codCancion);

void menuBuscarCancion(string username, string codPlaylist)
{
    BuscarCancion objBuscar;
    int codCancion;
    string titulo, rspta;
    do
    {
        system("cls");
        aux::cuadro(0,0,60, 13);
        aux::gotoxy(1,1);   cout << "Ingrese el titulo de la cancion > ";  getline(cin,titulo);
        transform(titulo.begin(), titulo.end(), titulo.begin(), ::tolower);
        
        aux::gotoxy(1,2);   cout << "Desea buscar la cancion? (si/no) > "; getline(cin,rspta);
        transform(rspta.begin(), rspta.end(), rspta.begin(), ::tolower);
        //cin.ignore();

    } while ( rspta!="si");

    system("cls");

    if(objBuscar.getResultados(titulo)==0)
    {   
        aux::cuadro(0,0,45, 7);
        aux::gotoxy(1,2);   cout << "No se encontro resultados" << endl;
        aux::gotoxy(1,3);   system("pause");
        menuBuscarCancion(username, codPlaylist);
    }
    else
    {   
        codCancion = objBuscar.imprimirResultados();
        
        elegirCancion(objBuscar, username, codPlaylist, codCancion);
    }
}

void elegirCancion(BuscarCancion objBuscar, string username, string codPlaylist, int codCancion)
{

    system("cls");
    int codigo;
    int opcion;

    objBuscar.getDatos(codCancion-1);
    codigo = objBuscar.getCodCancion(codCancion-1);
    //cout << endl;

        if (codPlaylist == "0") // determina si se viene del menu principal o una playlist especifica
        {
            
            objBuscar.fromMainMenu(username, codigo);
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
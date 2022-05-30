#include <iostream>
#include "..\include\BuscarCancion.h"
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
    objBuscar.getResultados(titulo); // obtiene resultados de la búsqueda

    cout<<endl;
    cout<<"Elija una cancion: ";
    cin>>codCancion;
    system("cls");

    objBuscar.getDatos(codCancion-1);
    cout<<endl;

    if (codPlaylist=="") // determina si se viene del menu principal o una playlist especifica
    {
        objBuscar.fromMainMenu();
    }
    else
    {
        objBuscar.fromPlaylist(codPlaylist);
    }

}

/*int main()
{
    string prueba="";
    menuBuscar(prueba);
}*/


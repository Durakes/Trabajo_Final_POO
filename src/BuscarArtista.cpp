#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "..\src\buscarCancion.cpp"
#include "..\include\BuscarArtista.h"
#include "..\include\BuscarCancion.h"
#include "..\include\Cancion.h"
using namespace std;

void pestanaArtista(BuscarArtista obj, int numIngresado, string username, string codPlaylist){

    BuscarCancion objBuscar;
    string titulo;
    int codigo;
    int codCancion;
    vector<string> cancionArtista = objBuscar.getCancionArtista(obj.compararCodigo(numIngresado)); //Vector de canciones dependiendo del codigo del artista
    
    system("cls");
    aux::cuadro(0, 0, 50, cancionArtista.size() + 20);
    aux::gotoxy(1,1);   cout << "NOMBRE DEL ARTISTA" << endl;
    
    aux::gotoxy(1,3); cout << obj.tempNombre(numIngresado);

    //Se enumeran las canciones que coinciden con el codigo del artista
    int i=1;
    aux::gotoxy(1,4); cout << setw(3) << "#" << setw(10) << "Cancion" << endl;
    for(string x:cancionArtista)
    {
        aux::gotoxy(1,4 + i);   cout << setw(3) << i << setw(15) << x << endl;
        i++;
    }

    aux::gotoxy(1,cancionArtista.size() + i);   cout<< "Elija una cancion > ";   cin>> codigo;  cin.ignore();

    titulo = cancionArtista[codigo-1]; //Se obtiene el titulo de la cancion
    transform(titulo.begin(), titulo.end(), titulo.begin(), ::tolower);

    //Se busca el titulo de la cancion y se repite el proceso de elegirCancion
    if(objBuscar.getResultados(titulo) == 0)
    {
        aux::gotoxy(1,cancionArtista.size() + i + 2);   cout << "No se encontraron resultados";
        aux::gotoxy(1,cancionArtista.size() + i + 3);  system("pause");
        menuBuscarCancion(username, codPlaylist);
    }
    else
    {
        codCancion = objBuscar.imprimirResultados();
        elegirCancion(objBuscar, username, codPlaylist, codCancion);
    }

}


void menuBuscarArtista(string username, string codPlaylist)
{
    BuscarArtista objArtista;
    string nombreArtista;
    string respuesta;
    int codElegido;
    vector<Artista> vecArtista = objArtista.agregarDatos();
    system("cls");
    aux::cuadro(0, 0, 50, 15);
    //Ingresa el nombre del artista y se busca
    aux::gotoxy(1,1);   cout << "BUSCAR ARTISTA" << endl;
    aux::gotoxy(1,2);   cout << "Ingresa nombre de artista a buscar: "; getline(cin, nombreArtista);

    transform(nombreArtista.begin(), nombreArtista.end(), nombreArtista.begin(), ::tolower); //En minusculas

    objArtista.buscarArtista(nombreArtista);
    aux::gotoxy(1,4); cout << "Desea continuar? (Y/N) > ";    getline(cin, respuesta);
    transform(respuesta.begin(), respuesta.end(), respuesta.begin(), ::tolower);

    if(respuesta == "y")
    {
        system("cls");

        codElegido =objArtista.listarResultados(); //Impresion de resultados de busqueda      
        pestanaArtista(objArtista, codElegido, username, codPlaylist);
    }

    else{
        //Regresar a menu principal
    }

}

/*int main(){
    menuBuscarArtista(name, "0");
}*/


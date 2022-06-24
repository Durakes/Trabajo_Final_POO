#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "..\src\buscarCancion.cpp"
#include "..\include\BuscarArtista.h"
#include "..\include\BuscarCancion.h"
#include "..\include\Cancion.h"
using namespace std;

void pestanaArtista(BuscarArtista objArtista, int numIngresado, string nombreUsuario, string codPlaylist){

    BuscarCancion objBuscar;
    string titulo;
    int codigo;
    int codCancion;
    vector<Cancion> cancionArtista = objBuscar.getCancionArtista(objArtista.compararCodigo(numIngresado)); //Vector de canciones dependiendo del codigo del artista
    
    system("cls");
    aux::cuadro(0, 0, 50, cancionArtista.size() + 20);
    aux::gotoxy(1,1);   cout << "NOMBRE DEL ARTISTA" << endl;
    
    aux::gotoxy(1,3); cout << objArtista.tempNombre(numIngresado);

    //Se enumeran las canciones que coinciden con el codigo del artista
    int i=1;
    aux::gotoxy(1,4); cout << setw(3) << "#" << setw(10) << "Cancion" << endl;
    for(Cancion x:cancionArtista)
    {
        aux::gotoxy(1,4 + i);   cout << setw(3) << i << setw(15) << x.getNombre() << endl;
        i++;
    }

    aux::gotoxy(1,cancionArtista.size() + i + 4);   cout<< "Elija una cancion > ";   cin>> codigo;  cin.ignore();

    titulo = cancionArtista[codigo-1].getNombre(); //Se obtiene el titulo de la cancion
    transform(titulo.begin(), titulo.end(), titulo.begin(), ::tolower);

    //Se busca el titulo de la cancion y se repite el proceso de elegirCancion
    if(objBuscar.getResultados(titulo) == 0)
    {
        aux::gotoxy(1,cancionArtista.size() + i + 2);   cout << "No se encontraron resultados";
        aux::gotoxy(1,cancionArtista.size() + i + 3);  system("pause");
        menuBuscarCancion(nombreUsuario, codPlaylist);
    }
    else
    {
        //codCancion = objBuscar.imprimirResultados();

        elegirCancion(objBuscar, nombreUsuario, codPlaylist, codigo); //! Por mientas sirve para solo 1 cancion.
    }

}

void menuBuscarArtista(string nombreUsuario, string codPlaylist)
{
    BuscarArtista objArtista;
    string nombreArtista;
    string respuesta;
    int codElegido;
    vector<Artista> vecArtista = objArtista.agregarDatos();
    system("cls");
    aux::cuadro(0, 0, 50, 15);
    
    aux::gotoxy(1,1);   cout << "BUSCAR ARTISTA" << endl;
    aux::gotoxy(1,2);   cout << "Ingresa nombre de artista a buscar: "; getline(cin, nombreArtista);

    transform(nombreArtista.begin(), nombreArtista.end(), nombreArtista.begin(), ::tolower);
    objArtista.buscarArtista(nombreArtista);

    aux::gotoxy(1,4); cout << "Desea continuar? (si o no) > ";    getline(cin, respuesta);
    transform(respuesta.begin(), respuesta.end(), respuesta.begin(), ::tolower);

    if(respuesta == "si")
    {
        system("cls");

        codElegido =objArtista.listarResultados();      
        pestanaArtista(objArtista, codElegido, nombreUsuario, codPlaylist);
    }else
    {
        //! Mensaje de salida.
        //Regresar a menu principal
    }
}

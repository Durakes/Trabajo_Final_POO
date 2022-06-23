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
    vector<string> cancionArtista = objBuscar.getCancionArtista(obj.compararCodigo(numIngresado)); //Vector de canciones dependiendo del codigo del artista

    cout << "NOMBRE DEL ARTISTA" << endl;
    cout << obj.tempNombre(numIngresado) << endl;

    //Se enumeran las canciones que coinciden con el codigo del artista
    int i=1;
    cout << endl;
    cout << setw(3) << "#" << setw(10) << "Cancion" << endl;
    for(string x:cancionArtista){
        cout << setw(3) << i << setw(15) << x << endl;
        i++;
    }

    cout<< "Elija una cancion: ";
    cin>> codigo;

    titulo = cancionArtista[codigo-1]; //Se obtiene el titulo de la cancion
    transform(titulo.begin(), titulo.end(), titulo.begin(), ::tolower);

    //Se busca el titulo de la cancion y se repite el proceso de elegirCancion
    if(objBuscar.getResultados(titulo) == 0){
        cout << "No se encontraron resultados" << endl;
        system("pause");
        system("cls");
        menuBuscarCancion(username, codPlaylist);
    }
    else{
        objBuscar.imprimirResultados();
        cout<<endl;
        system("cls");

        elegirCancion(objBuscar, username, codPlaylist, codigo);
    }

}


void menuBuscarArtista(string username, string codPlaylist){

    BuscarArtista objArtista;
    string nombreArtista;
    string respuesta;
    int codElegido;
    vector<Artista> vecArtista = objArtista.agregarDatos();
    

    //Ingresa el nombre del artista y se busca
    cout << "BUSCAR ARTISTA" << endl;
    cout << "Ingresa nombre de artista a buscar: ";
    getline(cin, nombreArtista);
    transform(nombreArtista.begin(), nombreArtista.end(), nombreArtista.begin(), ::tolower); //En minusculas

    objArtista.buscarArtista(nombreArtista);
    cout << "Desea continuar? (Y/N): ";
    getline(cin, respuesta);
    transform(respuesta.begin(), respuesta.end(), respuesta.begin(), ::tolower);

    if(respuesta == "y"){
        system("cls");

        objArtista.listarResultados(); //Impresion de resultados de busqueda

        cout << "Ingrese codigo del artista elegido: ";
        cin >> codElegido;

        system("pause");
        system("cls");

        pestanaArtista(objArtista, codElegido, username, codPlaylist);
    }

    else{
        //Regresar a menu principal
    }

}

/*int main(){
    menuBuscarArtista(name, "0");
}*/


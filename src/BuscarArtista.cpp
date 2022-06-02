#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "..\include\BuscarArtista.h"
using namespace std;

BuscarArtista objArtista;
string nombreArtista;
int codigoArtista;
vector<string> vecArtista = objArtista.agregarDatos();
void pestanaArtista();

void menuBuscarArtista(){
    string respuesta;

    //Ingresa el nombre y se busca
    cout << "BUSCAR ARTISTA" << endl;
    cout << "Ingresa nombre de artista a buscar: ";
    cin >> nombreArtista;
    transform(nombreArtista.begin(), nombreArtista.end(), nombreArtista.begin(), ::tolower);
    
    objArtista.buscarArtista(nombreArtista);
    cout << "¿Desea continuar? (Y/N)";
    cin >> respuesta;

    if(respuesta == "Y"){
        system("cls");

        //Impresion de resultados de busqueda
        objArtista.listarResultados();

        cout << "Ingrese codigo del artista elegido: ";
        cin >> codigoArtista;

        int posicion = objArtista.compararCodigo(codigoArtista);
        system("pause");
        system("cls");

        pestanaArtista(posicion);
    }

    else{
        //Regresar a menu principal
    }
    
}

void pestanaArtista(int posicion){
    cout << "NOMBRE DEL ARTISTA" << endl;
    cout << "Canciones: " << endl;
    //objArtista.listarCanciones();
    //Se elige una cancion y se repite el proceso de ElegirCancion
}

int main(){
    menuBuscarArtista();
}
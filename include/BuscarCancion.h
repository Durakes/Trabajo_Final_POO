#include <iostream>
#include <vector>
#include "..\include\Archive.h"

using namespace std;

class BuscarCancion
{
    private:

        vector<Cancion> vectorCanciones; // almacena todas las canciones
        vector<Cancion> vectorResultados; //almacena los resultados encontrados

    public:
        BuscarCancion()
        {            
            Cancion objCancion;
            Archive archive(R"(..\docs\Canciones.csv)");
            archive.cargarDatos(objCancion, &vectorCanciones); // graba las canciones a un vector;
        }

        void getDatos(int cod) // Imprime los datos de la canción seleccionada
        {
            
            int minutos=(vectorResultados[cod].getDuracion())/60;
            int segundos=vectorResultados[cod].getDuracion()-minutos*60;
            cout<<"Titulo: "<<vectorResultados[cod].getNombre()<<endl;
            cout<<"Artista: "<<vectorResultados[cod].getAutor()<<endl;
            cout<<"Duracion: "<<minutos<<":"<<segundos<<endl;

        }
        void fromMainMenu() // Elejir Playlist cuando se llega del menu principal
        {
            cout<<"Elija la playlist a la que desea agregar la cancion: ";
        }

        void fromPlaylist(string codeP) // Añadir a playlist ya determinada
        {
            cout<<"Desea agregar la cancion a "<<endl;
        }

        string aMinuscula(string cadena) // Convierte los titulos a minuscula
        {
            for (int i = 0; i < cadena.length(); i++) 
            {
                cadena[i] = tolower(cadena[i]);
            }
            return cadena;
        }

        void getResultados(string titulo)  // Imprime resultados
        {
            int i=1;
            for (Cancion x : vectorCanciones)
            {
                string nombre = aMinuscula(x.getNombre());
                if (titulo==nombre) // Compara el titulo ingresado con los almacenados en el archivo
                {
                    cout<<x.getNombre()<<" - "<<x.getAutor()<<" ["<<i<<"]"<<endl;
                    i++;
                    vectorResultados.push_back(x); // Añade al vector el obj Cancion
                }
                else
                {
                    cout<<"No se encontraron resultados"<<endl;
                }
            }
        }

};
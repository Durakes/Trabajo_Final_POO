#ifndef __BUSCARCANCION_H__
#define __BUSCARCANCION_H__
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
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

        static bool compareTitle(Cancion &a, Cancion &b)
        {
            return a.getNombre() < b.getNombre();
        }
        static bool compareAuthor(Cancion &a, Cancion &b)
        {
            return a.getAutor() < b.getAutor();
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
            cout<<"Elija la playlist a la que desea agregar la cancion: "<<endl;

        }

        void fromPlaylist(string codeP) // Añadir a playlist ya determinada
        {
            cout<<"Desea agregar la cancion a  "<<endl;


        }

        string aMinuscula(string cadena) // Convierte los titulos a minuscula
        {
            for (int i = 0; i < cadena.length(); i++)
            {
                cadena[i] = tolower(cadena[i]);
            }
            return cadena;
        }

        int binarySearch(int first, int last, string titulo)   // busqueda binaria
        {
            int med=(first+last)/2;
            if (last>=first)
            {

                if (aMinuscula(vectorCanciones[med].getNombre())==titulo)
                {
                    vectorResultados.push_back(vectorCanciones[med]);
                    int n=1;
                    while(titulo==aMinuscula(vectorCanciones[med-n].getNombre()))
                    {

                        vectorResultados.push_back(vectorCanciones[med-n]);
                        n++;
                    }

                    int m=1;
                    while(titulo==aMinuscula(vectorCanciones[med+m].getNombre()))
                    {
                        vectorResultados.push_back(vectorCanciones[med+m]);
                        m++;
                    }
                    return 1;


                }
                else if(aMinuscula(vectorCanciones[med].getNombre())>titulo)
                {
                    return binarySearch(first,med-1,titulo);

                }
                else
                {
                    return binarySearch(med+1,last,titulo);

                }
            }
            else
            {
                return 0;
            }

        }

        int getResultados(string titulo)  // Recibe el titulo para buscar los resultados
        {
            sort(vectorCanciones.begin(), vectorCanciones.end(), compareTitle);
            int v;
            int first=0,
                last=vectorCanciones.size()-1,
                med=last/2;

            v=binarySearch(first, last, titulo); // busqueda binaria
            return v;


        }

        void imprimirResultados() // imprime resultados encontrados
        {

            int i=1;

            sort(vectorResultados.begin(), vectorResultados.end(), compareAuthor);
            for (Cancion x : vectorResultados)
            {
                cout<<x.getNombre()<<" - "<<x.getAutor()<<" ["<<i<<"]"<<endl;
                i++;
            }

        }

};
#endif

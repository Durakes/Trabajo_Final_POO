#ifndef __BUSCARCANCION_H__
#define __BUSCARCANCION_H__
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <ctime>
#include "..\include\Auxiliar.h"
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
            cout<<"Album: "<<vectorResultados[cod].getAlbum()<<endl;
            cout<<"Artista: "<<vectorResultados[cod].getAutor()<<endl;
            cout<<"Duracion: "<<minutos<<":"<<segundos<<endl;
        }

        int getCodCancion(int cod)
        {
            return vectorResultados[cod].getCodigo();
        }

        void agregarCancionPlaylist(int codCancion, int codPlaylist)
        {
            Playlist objPlaylist;
            vector<Playlist> vectorPlaylist;
            Archive archive(R"(..\docs\Playlists.csv)");
            archive.cargarDatos(objPlaylist, &vectorPlaylist);
            
            string confirma;
            vector<int> vectorCodCanciones = vectorPlaylist[codPlaylist-1].getCanciones();
            if(vectorCodCanciones.size()!=0)
            {
                aux::ordenamientoRapido(&vectorCodCanciones, 0, vectorCodCanciones.size()-1, &vectorCodCanciones);
                aux::busquedaBinariaPuntual(0, vectorCodCanciones.size()-1, codCancion, vectorCodCanciones);
                
                if(aux::busquedaBinariaPuntual(0, vectorCodCanciones.size()-1, codCancion, vectorCodCanciones))
                {
                    system("cls");
                    cout<<"La cancion ya se encuentra agregada a la playlist "<<vectorPlaylist[codPlaylist-1].getNombre()<<"."<<endl;
                    cout<<"Esta seguro que desea agregarla nuevamente? ";
                    cin>>confirma;
                    transform(confirma.begin(), confirma.end(), confirma.begin(), ::tolower);
                    if(confirma=="si")
                    {
                        
                        vectorPlaylist[codPlaylist-1].agregarCancion(codCancion);
                        archive.modificarPlaylist(vectorPlaylist);
                        cout<<"La cancion se agrego a la playlist "<<vectorPlaylist[codPlaylist-1].getNombre()<<" exitosamente"<<endl;    
                    }
                    else
                    {
                        cout<<"No se agrego la cancion."<<endl;
                    }
                }

                else
                {
                    cout<<"Desea agregar la cancion a la playlist "<<vectorPlaylist[codPlaylist-1].getNombre()<<" ? ";
                    cin>>confirma;
                    transform(confirma.begin(), confirma.end(), confirma.begin(), ::tolower);
                    if(confirma=="si")
                    {
                        system("cls");
                        vectorPlaylist[codPlaylist-1].agregarCancion(codCancion);
                        archive.modificarPlaylist(vectorPlaylist);
                        cout<<"La cancion se agrego a la playlist "<<vectorPlaylist[codPlaylist-1].getNombre()<<" exitosamente"<<endl;    
                    }
                    else
                    {
                        system("cls");
                        cout<<"No se agrego la cancion."<<endl;

                    }
                    
                }
            }   
            else
            {
                cout<<"Desea agregar la cancion a la playlist "<<vectorPlaylist[codPlaylist-1].getNombre()<<" ? ";
                cin>>confirma;
                transform(confirma.begin(), confirma.end(), confirma.begin(), ::tolower);
                if(confirma=="si")
                {         
                    system("cls");         
                    vectorPlaylist[codPlaylist-1].agregarCancion(codCancion);
                    archive.modificarPlaylist(vectorPlaylist);
                    cout<<"La cancion se agrego a la playlist "<<vectorPlaylist[codPlaylist-1].getNombre()<<" exitosamente"<<endl;
                }
                else
                {
                    system("cls");
                    cout<<"No se agrego la cancion."<<endl;
                }
            }
            system("pause");
            system("cls");     
        }

        void fromMainMenu(string username, int codCancion) // Elejir Playlist cuando se llega del menu principal
        {
            Playlist objPlaylist;
            vector<Playlist> vectorPlaylist;
            Archive archive(R"(..\docs\Playlists.csv)");
            archive.cargarDatos(objPlaylist, &vectorPlaylist);
            
            vector<Playlist> vectorResUsuarios;
            vector<Playlist> vectorResEstado;
            vector<string> vectorUsuarios;
            vector<string> vectorEstado;
            int codigo=1;
            int respuesta;
            
            for(Playlist x: vectorPlaylist)
            {
                vectorUsuarios.push_back(aux::aMinuscula(x.getUsuario()));
            }
            
            aux:: ordenamientoRapido(&vectorUsuarios, 0, vectorUsuarios.size()-1, &vectorPlaylist);
            aux:: busquedaBinariaMultiple(0, vectorUsuarios.size()-1, aux::aMinuscula(username), vectorUsuarios, &vectorResUsuarios, vectorPlaylist); // encuentra todas las playlist del usuario

            for(Playlist x: vectorResUsuarios)
            {
                vectorEstado.push_back(x.getEstado());
            }

            string tipo="true";
            int i=1;
            aux:: ordenamientoRapido(&vectorEstado, 0, vectorEstado.size()-1, &vectorResUsuarios);
            aux:: busquedaBinariaMultiple(0, vectorEstado.size()-1, tipo, vectorEstado, &vectorResEstado, vectorResUsuarios );

            for (Playlist x: vectorResEstado)
            {
                cout<<"["<<i<<"]"<<x.getNombre()<<endl;
                i++;
            }

            cout<<"Elija la playlist a la que desea agregar la cancion: ";    
            cin>>respuesta;
            system("cls");

            int codPlaylist=(vectorResEstado[respuesta-1].getCodigo());
            agregarCancionPlaylist(codCancion, codPlaylist);
                 
        }

        void fromPlaylist(string codeP, int codCan) // Añadir a playlist ya determinada
        {
            Playlist objPlaylist;
            vector<Playlist> vectorPlaylist;
            Archive archive(R"(..\docs\Playlists.csv)");
            archive.cargarDatos(objPlaylist, &vectorPlaylist);

            int codPlay=stoi(codeP);
            agregarCancionPlaylist(codCan, codPlay);
          
        } 

        int getResultados(string titulo)  // Recibe el titulo para buscar los resultados
        {
            int i=0;
            int v;
            int first=0,
                last=vectorCanciones.size()-1;
            string temporal;
            vector<string> vectorTitulos;
            
            for (Cancion x:vectorCanciones)
            {
                vectorTitulos.push_back(aux::aMinuscula(x.getNombre()));
            }

            if(vectorCanciones.size()<=2)
            {
                for (Cancion x : vectorCanciones)
                {
                    if (titulo==aux::aMinuscula(x.getNombre()))
                    {
                        vectorResultados.push_back(x);
                    }
                }
                if (vectorResultados.size()==0)
                {
                    return 0;
                }
                else
                {
                    return 1;
                }

            }
            else
            {
                aux::ordenamientoRapido(&vectorTitulos, 0, vectorTitulos.size()-1, &vectorCanciones);
                aux::busquedaBinariaMultiple(first, last, titulo, vectorTitulos, &vectorResultados, vectorCanciones);// busqueda binaria
                if(vectorResultados.size()!=0)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }

        }

        void imprimirResultados() // imprime resultados encontrados
        {
            int i=1;
            vector<string> vectorAutores;

            for (Cancion x : vectorResultados)
            {
                vectorAutores.push_back(aux::aMinuscula(x.getAutor()));
            }

            aux::ordenamientoRapido(&vectorAutores,0,vectorAutores.size()-1, &vectorResultados);
            
            for (Cancion x : vectorResultados)
            {
                cout<<x.getNombre()<<" - "<<x.getAutor()<<" ["<<i<<"]"<<endl;
                i++;
            }

        }

};

#endif

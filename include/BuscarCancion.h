#ifndef __BUSCARCANCION_H__
#define __BUSCARCANCION_H__
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <ctime>
#include "..\include\Auxiliar.h"
#include "..\include\Archivo.h"
using namespace std;

class BuscarCancion
{
    private:

        vector<Cancion> VectorCanciones; // almacena todas las canciones
        vector<Cancion> VectorResultados; //almacena los resultados encontrados
        
    public:
        BuscarCancion()
        {
            Cancion objCancion;
            Archivo archive(R"(..\docs\Canciones.csv)");
            archive.cargarDatos(objCancion, &VectorCanciones); // graba las canciones a un vector;
        }


        void getDatos(int cod) // Imprime los datos de la canción seleccionada
        {
            system("cls");
            aux::cuadro(0,0,70, 15);
            int minutos = (VectorResultados[cod].getDuracion()) / 60;
            int segundos = VectorResultados[cod].getDuracion() - minutos * 60;
            aux::gotoxy(1,1); cout << "Titulo: " << VectorResultados[cod].getNombre() << endl;
            aux::gotoxy(1,2); cout << "Album: "  << VectorResultados[cod].getAlbum() << endl;
            aux::gotoxy(1,3); cout << "Artista: " << VectorResultados[cod].getAutor() << endl;
            aux::gotoxy(1,4); cout << "Duracion: " << minutos << ":" <<segundos << endl;
            aux::gotoxy(1,5); system("pause");
        }

        int getCodCancion(int cod)
        {
            return VectorResultados[cod].getCodigo();
        }

        void agregarCancionPlaylist(int codCancion, int codPlaylist, int tamanoY = 0)
        {
            Playlist objPlaylist;
            vector<Playlist> vectorPlaylist;
            Archivo archive(R"(..\docs\Playlists.csv)");
            archive.cargarDatos(objPlaylist, &vectorPlaylist);
            
            string confirma;
            vector<int> vectorCodCanciones = vectorPlaylist[codPlaylist-1].getCanciones();
            if(vectorCodCanciones.size()!=0)
            {
                aux::ordenamientoRapido(&vectorCodCanciones, 0, vectorCodCanciones.size()-1, &vectorCodCanciones);
                aux::busquedaBinariaPuntual(0, vectorCodCanciones.size()-1, codCancion, vectorCodCanciones);
                
                if(aux::busquedaBinariaPuntual(0, vectorCodCanciones.size()-1, codCancion, vectorCodCanciones))
                {

                    aux::gotoxy(1,6 + tamanoY);   cout<<"La cancion ya se encuentra agregada a la playlist "<<vectorPlaylist[codPlaylist-1].getNombre()<<"."<<endl;
                    aux::gotoxy(1,7 + tamanoY);   cout<<"Esta seguro que desea agregarla nuevamente? ";   getline(cin, confirma);
                    transform(confirma.begin(), confirma.end(), confirma.begin(), ::tolower);
                    if(confirma == "si")
                    {
                        vectorPlaylist[codPlaylist-1].agregarCancion(codCancion);
                        archive.modificarPlaylist(vectorPlaylist);
                        
                        aux::gotoxy(1,9 + tamanoY);   cout<<"La cancion se agrego a la playlist "<<vectorPlaylist[codPlaylist-1].getNombre()<<" exitosamente"<<endl;
                    }
                    else
                    {
                        aux::gotoxy(1,9 + tamanoY);   cout<<"No se agrego la cancion."<<endl;
                    }
                }

                else
                {
                    aux::gotoxy(1,6 + tamanoY);   cout<<"Desea agregar la cancion a la playlist "<<vectorPlaylist[codPlaylist-1].getNombre()<<" ? ";  getline(cin, confirma);

                    transform(confirma.begin(), confirma.end(), confirma.begin(), ::tolower);

                    if(confirma == "si")
                    {
                        vectorPlaylist[codPlaylist-1].agregarCancion(codCancion);
                        archive.modificarPlaylist(vectorPlaylist);
                        aux::gotoxy(1,8 + tamanoY);   cout<<"La cancion se agrego a la playlist "<<vectorPlaylist[codPlaylist-1].getNombre()<<" exitosamente"<<endl;    
                    }
                    else
                    {
                        aux::gotoxy(1,8 + tamanoY); cout<<"No se agrego la cancion."<<endl;
                    }
                    
                }
            }   
            else
            {
                aux::gotoxy(1,6 + tamanoY);    cout<<"Desea agregar la cancion a la playlist "<<vectorPlaylist[codPlaylist-1].getNombre()<<" ? ";getline(cin, confirma);
                transform(confirma.begin(), confirma.end(), confirma.begin(), ::tolower);
                if(confirma == "si")
                {      
                    vectorPlaylist[codPlaylist-1].agregarCancion(codCancion);
                    archive.modificarPlaylist(vectorPlaylist);
                    aux::gotoxy(1,8 + tamanoY);   cout<<"La cancion se agrego a la playlist "<<vectorPlaylist[codPlaylist-1].getNombre()<<" exitosamente"<<endl;
                }
                else
                {
                    aux::gotoxy(1,8 + tamanoY); cout<<"No se agrego la cancion."<<endl;
                }
            }
            aux::gotoxy(1,10 + tamanoY);  system("pause");
            system("cls");     
        }

        void fromMainMenu(string username, int codCancion) // Elegir Playlist cuando se llega del menu principal
        {
            system("cls");
            Playlist objPlaylist;
            vector<Playlist> vectorPlaylist;
            Archivo archive(R"(..\docs\Playlists.csv)");
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
            aux::cuadro(0,0, 60, vectorResEstado.size() + 20);
            aux::gotoxy(1,1); cout << "Playlist disponibles";
            for (Playlist x: vectorResEstado)
            {
                
                aux::gotoxy(1,i+1); cout<<"["<<i<<"]"<<x.getNombre()<<endl;
                i++;
            }

            aux::gotoxy(1,vectorResEstado.size() + 2);    cout<<"Elija la playlist a la que desea agregar la cancion: ";    cin >> respuesta; cin.ignore();

            int codPlaylist=(vectorResEstado[respuesta-1].getCodigo());
            agregarCancionPlaylist(codCancion, codPlaylist, vectorResEstado.size() + 2);
        
        }

        void fromPlaylist(string codeP, int codCan) // Añadir a playlist ya determinada
        {
            Playlist objPlaylist;
            vector<Playlist> vectorPlaylist;
            Archivo archive(R"(..\docs\Playlists.csv)");
            archive.cargarDatos(objPlaylist, &vectorPlaylist);

            int codPlay = stoi(codeP);
            agregarCancionPlaylist(codCan, codPlay);
        } 

        int getResultados(string titulo)  // Recibe el titulo para buscar los resultados
        {
            int i=0;
            int v;
            int first=0,
                last=VectorCanciones.size()-1;
            string temporal;
            vector<string> vectorTitulos;
            
            for (Cancion x:VectorCanciones)
            {
                vectorTitulos.push_back(aux::aMinuscula(x.getNombre()));
            }

            if(VectorCanciones.size()<=2)
            {
                for (Cancion x : VectorCanciones)
                {
                    if (titulo==aux::aMinuscula(x.getNombre()))
                    {
                        VectorResultados.push_back(x);
                    }
                }
                if (VectorResultados.size()==0)
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
                aux::ordenamientoRapido(&vectorTitulos, 0, vectorTitulos.size()-1, &VectorCanciones);
                aux::busquedaBinariaMultiple(first, last, titulo, vectorTitulos, &VectorResultados, VectorCanciones);// busqueda binaria
                if(VectorResultados.size()!=0)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }

        }

        int imprimirResultados() // imprime resultados encontrados
        {
            system("cls");
            int i=1;
            int codCancion;
            vector<string> vectorAutores;

            for (Cancion x : VectorResultados)
            {
                vectorAutores.push_back(aux::aMinuscula(x.getAutor()));
            }

            aux::ordenamientoRapido(&vectorAutores,0,vectorAutores.size() - 1, &VectorResultados);
            
            aux::cuadro(0,0,45, VectorResultados.size() + 5);
            for (Cancion x : VectorResultados)
            {
                aux::gotoxy(1,1+i); cout<<x.getNombre()<<" - "<<x.getAutor()<<" ["<<i<<"]"<<endl;
                i++;
            }

            aux::gotoxy(1,VectorResultados.size() + 3);  cout<<"Elija una cancion: "; cin >> codCancion; cin.ignore();
            
            return codCancion;
        }

        vector<Cancion> getCancionArtista(int codArtista)
        { //De un codigo del artista, se obtienen todas sus canciones
            vector<string> vectorCancionArtista; //almacena canciones segun artista
            vector<int> codigos;
            //vector<Cancion> vectorResultados;
            VectorResultados.clear();

            for(Cancion cancion: VectorCanciones)
            {
                codigos.push_back(cancion.getCodigoAutor());
            }

            aux::ordenamientoRapido(&codigos, 0, codigos.size()-1, &VectorCanciones);
            aux::busquedaBinariaMultiple(0, codigos.size() - 1, codArtista, codigos, &VectorResultados, VectorCanciones);

            return VectorResultados;
        }
};

#endif

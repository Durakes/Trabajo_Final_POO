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

        vector<Cancion> VectorCanciones; 
        vector<Cancion> VectorResultados; 
        
    public:
        BuscarCancion()
        {
            Cancion objCancion;
            Archivo archive(R"(..\docs\Canciones.csv)");
            archive.cargarDatos(objCancion, &VectorCanciones); 
        }


        void getDatos(int cod) 
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

            if(vectorCodCanciones.size() != 0)
            {
                aux::ordenamientoRapido(&vectorCodCanciones, 0, vectorCodCanciones.size()-1, &vectorCodCanciones);
                aux::busquedaBinariaPuntual(0, vectorCodCanciones.size()-1, codCancion, vectorCodCanciones);
                
                if(aux::busquedaBinariaPuntual(0, vectorCodCanciones.size()-1, codCancion, vectorCodCanciones))
                {

                    aux::gotoxy(1,tamanoY);   cout << "La cancion ya se encuentra agregada a la playlist " << vectorPlaylist[codPlaylist-1].getNombre() << "." << endl;
                    aux::gotoxy(1,1 + tamanoY);   cout << "Esta seguro que desea agregarla nuevamente? ";   getline(cin, confirma);
                    transform(confirma.begin(), confirma.end(), confirma.begin(), ::tolower);
                    if(confirma == "si")
                    {
                        vectorPlaylist[codPlaylist-1].agregarCancion(codCancion);
                        archive.modificarPlaylist(vectorPlaylist);
                        
                        aux::gotoxy(1,3 + tamanoY);   cout << "La cancion se agrego a la playlist " << vectorPlaylist[codPlaylist-1].getNombre()<< " exitosamente" << endl;
                    }
                    else
                    {
                        aux::gotoxy(1,3 + tamanoY);   cout << "No se agrego la cancion." << endl;
                    }
                }

                else
                {
                    aux::gotoxy(1,tamanoY);   cout << "Desea agregar la cancion a la playlist " << vectorPlaylist[codPlaylist-1].getNombre() << " ? ";  getline(cin, confirma);

                    transform(confirma.begin(), confirma.end(), confirma.begin(), ::tolower);

                    if(confirma == "si")
                    {
                        vectorPlaylist[codPlaylist-1].agregarCancion(codCancion);
                        archive.modificarPlaylist(vectorPlaylist);
                        aux::gotoxy(1,2 + tamanoY);   cout << "La cancion se agrego a la playlist " << vectorPlaylist[codPlaylist-1].getNombre()<< " exitosamente" << endl;
                    }
                    else
                    {
                        aux::gotoxy(1,2 + tamanoY); cout << "No se agrego la cancion." << endl;
                    }
                    
                }
            }   
            else
            {
                aux::gotoxy(1,tamanoY);    cout<<"Desea agregar la cancion a la playlist "<<vectorPlaylist[codPlaylist-1].getNombre()<<" ? ";getline(cin, confirma);
                transform(confirma.begin(), confirma.end(), confirma.begin(), ::tolower);
                if(confirma == "si")
                {      
                    vectorPlaylist[codPlaylist-1].agregarCancion(codCancion);
                    archive.modificarPlaylist(vectorPlaylist);
                    aux::gotoxy(1,2 + tamanoY);   cout<<"La cancion se agrego a la playlist "<<vectorPlaylist[codPlaylist-1].getNombre()<<" exitosamente"<<endl;
                }
                else
                {
                    aux::gotoxy(1,2 + tamanoY); cout<<"No se agrego la cancion."<<endl;
                }
            }
            aux::gotoxy(1,4 + tamanoY);  system("pause");
            system("cls");     
        }

        void fromMainMenu(string username, int codCancion)
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
            
            for(Playlist playlist: vectorPlaylist)
            {
                vectorUsuarios.push_back(aux::aMinuscula(playlist.getUsuario()));
            }
            
            aux:: ordenamientoRapido(&vectorUsuarios, 0, vectorUsuarios.size()-1, &vectorPlaylist);
            aux:: busquedaBinariaMultiple(0, vectorUsuarios.size()-1, aux::aMinuscula(username), vectorUsuarios, &vectorResUsuarios, vectorPlaylist);

            for(Playlist playlist: vectorResUsuarios)
            {
                vectorEstado.push_back(playlist.getEstado());
            }

            string tipo="true";
            int i=1;
            aux:: ordenamientoRapido(&vectorEstado, 0, vectorEstado.size()-1, &vectorResUsuarios);
            aux:: busquedaBinariaMultiple(0, vectorEstado.size()-1, tipo, vectorEstado, &vectorResEstado, vectorResUsuarios );
            aux::cuadro(0,0, 60, vectorResEstado.size() + 20);
            aux::gotoxy(1,1); cout << "Playlist disponibles";
            for (Playlist playlist: vectorResEstado)
            {
                
                aux::gotoxy(1,i + 2); cout<<"["<<i<<"]"; aux::gotoxy(20,i + 2); cout << playlist.getNombre();
                i++;
            }

            aux::gotoxy(1,i + 4);    cout << "Elija la playlist a la que desea agregar la cancion: ";    cin >> respuesta; cin.ignore();

            int codPlaylist = (vectorResEstado[respuesta-1].getCodigo());
            agregarCancionPlaylist(codCancion, codPlaylist, i + 6);
        
        }

        void fromPlaylist(string codeP, int codCan)
        {
            Playlist objPlaylist;
            vector<Playlist> vectorPlaylist;
            Archivo archive(R"(..\docs\Playlists.csv)");
            archive.cargarDatos(objPlaylist, &vectorPlaylist);

            int codPlay = stoi(codeP);
            agregarCancionPlaylist(codCan, codPlay);
        } 

        int getResultados(string titulo)
        {
            int i=0;
            int v;
            int first=0,
                last=VectorCanciones.size()-1;
            string temporal;
            vector<string> vectorTitulos;
            
            for (Cancion cancion: VectorCanciones)
            {
                vectorTitulos.push_back(aux::aMinuscula(cancion.getNombre()));
            }

            if(VectorCanciones.size()<=2)
            {
                for (Cancion cancion: VectorCanciones)
                {
                    if (titulo == aux::aMinuscula(cancion.getNombre()))
                    {
                        VectorResultados.push_back(cancion);
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
                aux::busquedaBinariaMultiple(first, last, titulo, vectorTitulos, &VectorResultados, VectorCanciones);

                if(VectorResultados.size() != 0)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }

        }

        int imprimirResultados()
        {
            system("cls");
            int i=1;
            int codCancion;
            vector<string> vectorAutores;

            for (Cancion cancion: VectorResultados)
            {
                vectorAutores.push_back(aux::aMinuscula(cancion.getAutor()));
            }

            aux::ordenamientoRapido(&vectorAutores,0,vectorAutores.size() - 1, &VectorResultados);
            
            aux::cuadro(0,0,45, VectorResultados.size() + 5);
            for (Cancion cancion: VectorResultados)
            {
                aux::gotoxy(1,1+i); cout << cancion.getNombre() << " - " << cancion.getAutor() << " [" << i << "]" << endl;
                i++;
            }

            aux::gotoxy(1,VectorResultados.size() + 3);  cout<<"Elija una cancion: "; cin >> codCancion; cin.ignore();
            
            return codCancion;
        }

        vector<Cancion> getCancionArtista(int codArtista)
        { 
            vector<string> vectorCancionArtista;
            vector<int> codigos;
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

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

        string aMinuscula(string cadena) // Convierte los titulos a minuscula
        {
            for (int i = 0; i < cadena.length(); i++)
            {
                cadena[i] = tolower(cadena[i]);
            }
            return cadena;
        }

        static bool compareTitle(Cancion a, Cancion b)
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
            cout<<"Album: "<<vectorResultados[cod].getAlbum()<<endl;
            cout<<"Artista: "<<vectorResultados[cod].getAutor()<<endl;
            cout<<"Duracion: "<<minutos<<":"<<segundos<<endl;
        }

        int getCodCancion(int cod)
        {
            return vectorResultados[cod].getCodigo();
        }

        void agregarCancionPlaylist(vector<Playlist> vectorPlaylist, int codCancion, int codPlaylist)
        {
            Archive archive(R"(..\docs\Playlists.csv)");

            bool flag;
            string confirma;
            if(vectorPlaylist[codPlaylist-1].getCanciones().size()!=0)
            {
                for(int cod:vectorPlaylist[codPlaylist-1].getCanciones()) // usar busqueda binaria 
                {
                    if(codCancion==cod)
                    {
                        flag=true;
                        break;
                    }
                    else
                    {
                        flag=false;
                    }
                }
                if(flag==false)
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
                else
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
            
            vector<Playlist> vectorResPlay;
            int codigo=1;
            int respuesta;
            
            
            for (Playlist x:vectorPlaylist)
            {
                if (x.getUsuario()==username && x.getEstado()=="true") // usar busqueda binaria
                {
                    cout<<"["<<codigo<<"] "<<x.getNombre()<<endl;
                    codigo++;
                    vectorResPlay.push_back(x);
                }
            }
            cout<<"Elija la playlist a la que desea agregar la cancion: ";    
            cin>>respuesta;
            system("cls");

            int codPlaylist=(vectorResPlay[respuesta-1].getCodigo());
            agregarCancionPlaylist(vectorPlaylist, codCancion, codPlaylist);
                 
        }

        void fromPlaylist(string codeP, int codCan) // Añadir a playlist ya determinada
        {
            Playlist objPlaylist;
            vector<Playlist> vectorPlaylist;
            Archive archive(R"(..\docs\Playlists.csv)");
            archive.cargarDatos(objPlaylist, &vectorPlaylist);

            int codPlay=stoi(codeP);
            agregarCancionPlaylist(vectorPlaylist, codCan, codPlay);
          
        }

        int binarySearch(int first, int last, string titulo, vector<Cancion> vectorMinusculas)   // busqueda binaria           
        {
            int codigo;
            int med=(first+last)/2;
            if (last>=first)
            {  
                if (vectorMinusculas[med].getNombre()==titulo)
                {
                    codigo=(vectorMinusculas[med].getCodigo());
                    vectorResultados.push_back(vectorCanciones[codigo-1]);
                                      
                    if(med!=0)
                    {
                        int n=1;
                        while(titulo==vectorMinusculas[med-n].getNombre())
                        {
                            codigo=vectorMinusculas[med-n].getCodigo();
                            vectorResultados.push_back(vectorCanciones[codigo-1]);
                            n++;
                        }
                    }
                    
                    if(med!=vectorMinusculas.size()-1)
                    {
                        int m=1;

                        while(titulo==vectorMinusculas[med+m].getNombre())
                        {
                            codigo=vectorMinusculas[med+m].getCodigo();
                            vectorResultados.push_back(vectorCanciones[codigo-1]);
                            m++;
                        }
                    }

                    return 1;
                }

                else if(vectorMinusculas[med].getNombre()>titulo)
                {
                    return binarySearch(first,med-1,titulo, vectorMinusculas);
                }
                else
                {
                    return binarySearch(med+1,last,titulo, vectorMinusculas);
                }
            }
            else
            {
                return 0;
            }

        }

        int getResultados(string titulo)  // Recibe el titulo para buscar los resultados
        {
            int i=0;
            int v;
            int first=0,
                last=vectorCanciones.size()-1;
            string temporal;
            vector<Cancion> vectorMinusculas;
            
            if(vectorCanciones.size()<=2)
            {
                for (Cancion x : vectorCanciones)
                {
                    if (titulo==aMinuscula(x.getNombre()))
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
                       
                for (Cancion x:vectorCanciones)
                {   
                    vectorMinusculas.push_back(x);
                    temporal=aMinuscula(x.getNombre());
                    vectorMinusculas[i].setNombre(temporal);
                    i++;
                }
                sort(vectorMinusculas.begin(), vectorMinusculas.end(), compareTitle);
                v=binarySearch(first, last, titulo, vectorMinusculas); // busqueda binaria
                return v;
            }

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

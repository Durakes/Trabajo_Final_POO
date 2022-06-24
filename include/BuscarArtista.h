#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include "Binario.h"
#include "Artista.h"
#include "BuscarCancion.h"
#include "Auxiliar.h"

using namespace std;

class BuscarArtista
{
    private:
        vector<Artista> VectorArtista;
        vector<Artista> Temporal; 

    public:
        BuscarArtista(){}

        vector<Artista> agregarDatos()
        {
            BuscarCancion objBuscar;
            string path = "..\\docs\\Usuarios.bin";
            Binario archive(path);
            vector<Usuario> vectorUsuario = archive.LeerDato();
            string tipo = "artist";
            vector<string> tipoArtista;
            vector<Usuario> artistas;

            for(Usuario x: vectorUsuario)
            {
                tipoArtista.push_back(x.getTipo());
            }

            aux::ordenamientoRapido(&tipoArtista, 0, tipoArtista.size() - 1, &vectorUsuario);
            aux::busquedaBinariaMultiple(0, tipoArtista.size() - 1, tipo, tipoArtista, &artistas, vectorUsuario);

            for(Usuario x:artistas)
            {   
                vector<Cancion> cancionArtista = objBuscar.getCancionArtista(x.getCodigo());

                Artista objArtista(x.getNombre(), x.getCodigo(), cancionArtista.size());
                VectorArtista.push_back(objArtista);
            }
            return VectorArtista;
        }

        void buscarArtista(string nombreArtista)
        {
            system("cls");
            aux::cuadro(0,0, 60, 10);
            aux::gotoxy(1,1);   cout << "............Buscando..........." << endl;

            vector<string> nombres;
            for(Artista artista: VectorArtista)
            {
                nombres.push_back(aux::aMinuscula(artista.getNombre()));
            }

            aux::ordenamientoRapido(&nombres,0, nombres.size() - 1, &VectorArtista);
            aux::busquedaBinariaMultiple(0, nombres.size() - 1, nombreArtista, nombres, &Temporal, VectorArtista);

            if(Temporal.size() > 0)
            {
                aux::gotoxy(1,2); cout << "Se han encontrado " << Temporal.size() << " coincidencias...";
            }
            else
            {
                aux::gotoxy(1,2);    cout << "No se encontraron coincidencias";
            }
        }

        int listarResultados()
        {
            int codElegido;
            aux::cuadro(0,0, 60, Temporal.size()+15);

            aux::gotoxy(1,1);   cout << "..................." << endl;
            aux::gotoxy(1,2);   cout << "    RESULTADOS" << endl;
            aux::gotoxy(1,3);   cout << "..................." << endl;

            int i=1;
            aux::gotoxy(1,4);   cout << setw(3) << "#" << setw(10) << "Nombre" << setw(20) << "#Canciones" << endl;
            
            for (Artista x:Temporal) 
            {
                //!Revisar
                aux::gotoxy(1,5+i);   cout << setw(3) << "[" << i << "]" << setw(10) << x.getNombre() << setw(20) << x.getNumCanciones() << endl;
                i++;
            }

            aux::gotoxy(1, Temporal.size() + i + 6);  cout << "Ingrese codigo del artista elegido > ";cin >> codElegido; cin.ignore();
            return codElegido; 
        }

        int compararCodigo(int numIngresado)
        { 
            return Temporal[numIngresado - 1].getCodigo();
        }

        string tempNombre(int numIngresado)
        {
            return Temporal[numIngresado - 1].getNombre();
        }

};
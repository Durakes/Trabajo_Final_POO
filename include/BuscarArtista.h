#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include "BinaryFile.h"
#include "Artista.h"
#include "BuscarCancion.h"
#include "Auxiliar.h"

using namespace std;

class BuscarArtista{
    private:
        vector<Artista> vectorArtista;
        vector<Artista> temporal; 

    public:
        BuscarArtista(){}

        vector<Artista> agregarDatos()
        { //Agrega artistas, su codigo y numero de canciones al vectorArtista
            BuscarCancion objBuscar;
            string path = "..\\docs\\Usuarios.bin";
            BinaryFile archive(path);
            vector<User> vectorUsuario = archive.LeerDato();
            string tipo = "artist";
            vector<string> tipoArtista;
            vector<User> artistas;

            for(User x: vectorUsuario)
            {
                tipoArtista.push_back(x.getType());
            }

            aux::ordenamientoRapido(&tipoArtista, 0, tipoArtista.size() - 1, &vectorUsuario);
            aux::busquedaBinariaMultiple(0, tipoArtista.size() - 1, tipo, tipoArtista, &artistas, vectorUsuario);
            //Recorre vector del archivo binario y agrega nombre, codigo y #canciones a vectorArtista

            for(User x:artistas)
            {   
                vector<string> cancionArtista = objBuscar.getCancionArtista(x.getCode());

                Artista objArtista(x.getName(), x.getCode(), cancionArtista.size());
                vectorArtista.push_back(objArtista);
            }
            return vectorArtista;
        }

        void buscarArtista(string nombreArtista)
        { //Busca si el nombre ingresado coincide con artista registrado y registra resultados en vector temporal
            system("cls");
            aux::cuadro(0,0, 60, 10);
            aux::gotoxy(1,1);   cout << "............Buscando..........." << endl;

            //int i=0;
            vector<string> nombres;
            //vector<Artista> artistaFinal;

            for(Artista artista: vectorArtista)
            {
                //cout << artista.getNombre() << endl;
                nombres.push_back(aux::aMinuscula(artista.getNombre()));
            }

            aux::ordenamientoRapido(&nombres,0, nombres.size()-1, &vectorArtista);
            aux::busquedaBinariaMultiple(0, nombres.size()-1, nombreArtista, nombres, &temporal, vectorArtista);

            if(temporal.size() > 0)
            {
                aux::gotoxy(1,2); cout << "Se han encontrado " << temporal.size() << " coincidencias...";
            }
            else
            {
                aux::gotoxy(1,2);    cout << "No se encontraron coincidencias";
                // Regresar a menu principal (cambiar)
                // exit(0);
            }
        }

        int listarResultados()
        { //Se imprimen todos los resultados
            int codElegido;
            aux::cuadro(0,0, 60, temporal.size()+15);

            aux::gotoxy(1,1);   cout << "..................." << endl;
            aux::gotoxy(1,2);   cout << "    RESULTADOS" << endl;
            aux::gotoxy(1,3);   cout << "..................." << endl;

            int i=1;
            aux::gotoxy(1,4);   cout << setw(3) << "#" << setw(10) << "Nombre" << setw(20) << "#Canciones" << endl;
            
            for (Artista x:temporal) 
            {
                //!Revisar
                aux::gotoxy(1,5+i);   cout << setw(3) << "[" << i << "]" << setw(10) << x.getNombre() << setw(20) << x.getNumCanciones() << endl;
                i++;
            }

            aux::gotoxy(1, temporal.size() + i + 6);  cout << "Ingrese codigo del artista elegido > ";cin >> codElegido; cin.ignore();
            return codElegido; 
        }

        int compararCodigo(int numIngresado){ //Se verifica la opcion elegida por el usuario y se retorna el codigoArtista 
            return temporal[numIngresado-1].getCodigo();
        }

        string tempNombre(int numIngresado){ //Se verifica la opcion elegida por el usuario y se retorna el nombreArtista 
            return temporal[numIngresado-1].getNombre();
        }

};
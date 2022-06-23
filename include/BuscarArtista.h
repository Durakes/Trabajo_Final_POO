#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include "BinaryFile.h"
#include "Artista.h"
#include "BuscarCancion.h"

using namespace std;

class BuscarArtista{
    private:
        vector<Artista> vectorArtista;
        vector<Artista> temporal; 

    public:
        BuscarArtista(){}

        vector<Artista> agregarDatos(){ //Agrega artistas, su codigo y numero de canciones al vectorArtista
            BuscarCancion objBuscar;
            string path = "..\\docs\\Users.bin";
            BinaryFile archive(path);
            vector<User> vectorUsuario = archive.LeerDato();

            //Recorre vector del archivo binario y agrega nombre, codigo y #canciones a vectorArtista
            for(User x:vectorUsuario){
                string tipoArtista = (char*)&x.getType()[0];
                if("artist" == tipoArtista){
                    string nombre = x.getName();
                    int codigo = x.getCode();
                    transform(nombre.begin(), nombre.end(), nombre.begin(), ::tolower);
                    vector<string> cancionArtista = objBuscar.getCancionArtista(codigo);

                    Artista objArtista(nombre, codigo, cancionArtista.size());
                    vectorArtista.push_back(objArtista);
                }
            }

            return vectorArtista;
        }


        void buscarArtista(string nombreArtista){ //Busca si el nombre ingresado coincide con artista registrado y registra resultados en vector temporal
            cout << endl;
            cout << "............Buscando..........." << endl;

            int i=0;
            for(Artista x:vectorArtista){
                if(x.getNombre() == nombreArtista){
                    i++;
                    Artista objArtista(x.getNombre(), x.getCodigo(), x.getNumCanciones());
                    temporal.push_back(objArtista);
                }
            }

            if(i>0){
                cout << "Se han encontrado " << i << " coincidencias..." << endl;
            }
            else{
                cout << "No se encontraron coincidencias" << endl;
                //Regresar a menu principal (cambiar)
                exit(0);
            }

        }

        void listarResultados(){ //Se imprimen todos los resultados

            cout << "..................." << endl;
            cout << "    RESULTADOS" << endl;
            cout << "..................." << endl;
            cout << endl;

            int i=1;
            cout << setw(3) << "#" << setw(10) << "Nombre" << setw(20) << "#Canciones" << endl;
            for (Artista x:temporal) {
                cout << setw(3) << "[" << i << "]" << setw(10) << x.getNombre() << setw(20) << x.getNumCanciones() << endl;
                i++;
            } 
        }

        int compararCodigo(int numIngresado){ //Se verifica la opcion elegida por el usuario y se retorna el codigoArtista 
            return temporal[numIngresado-1].getCodigo();
        }

        string tempNombre(int numIngresado){ //Se verifica la opcion elegida por el usuario y se retorna el nombreArtista 
            return temporal[numIngresado-1].getNombre();
        }

};
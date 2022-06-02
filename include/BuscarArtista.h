#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include "BinaryFile.h"

using namespace std;

class BuscarArtista{
    private:
        vector<string> vectorArtista;
        vector<string> temporal; 

    public:
        BuscarArtista(){}

        vector<string> agregarDatos(){
            //Agrega artistas al vector artista
            string path = "..\\docs\\Users.bin";
            BinaryFile archive(path);
            vector<User> vectorUsuario = archive.LeerDato();

            for(User x:vectorUsuario){
                string tipoArtista = (char*)&x.getType()[0];
                if("artist" == tipoArtista){
                    string nombre = x.getName();
                    transform(nombre.begin(), nombre.end(), nombre.begin(), ::tolower);
                    vectorArtista.push_back(nombre);
                }
            }

            return vectorArtista;
        }

        void buscarArtista(string nombreArtista){
            //Busca si el nombre ingresado coincide con artista registrado
            cout << endl;
            cout << "............Buscando..........." << endl;

            int i=0;
            for(string x:vectorArtista){
                if(x == nombreArtista){
                    i++;
                    temporal.push_back(x);
                }
            }

            if(i>0){
                cout << "Se han encontrado " << i << " coincidencias..." << endl;
                }
            else{
                cout << "No se encontraron coincidencias" << endl;
                //Regresar a menu principal
                exit(0);
            }

        }

        void listarResultados(){
            //Se imprimen todos los resultados
            cout << "..................." << endl;
            cout << "RESULTADOS" << endl;
            cout << "..................." << endl;
            cout << endl;
            for (auto it = temporal.begin(); it != temporal.end(); it++) {
                int pos = distance(temporal.begin(), it);
                //Faltan el numero de canciones
                cout << setw(3) << "["<< pos+1 << "]"<< setw(10) << *it << endl;
            }
        }

        int compararCodigo(int codigoArtista){
            for (auto it = temporal.begin(); it != temporal.end(); it++) {
                int pos = distance(temporal.begin(), it);
                if(codigoArtista == pos+1){
                    return pos;
                }
            }
        }

        //De la posicion, se extraen canciones, luego pondre mas validaciones
        void getCanciones(){

        }

        void listarCanciones(){

        }
};
#ifndef __PLAYLIST_H__
#define __PLAYLIST_H__
#include<string>
#include<iostream>
#include<vector>
using namespace std;
class Playlist{
    private:
        string nombre;
        int codigo;
        string nombreUsuario;
        vector<int> vectorCodigo;
        string estado;//para hacer una eliminacion logica, no se muestra en el programa, pero se queda en el archivo
        //solo guardar los codigos, cancion csv y de alli solo jalo el codigo de la cancion.
    public:
        Playlist(int code, string name, string userName){
            this->nombre=name;
            this->codigo=code;
            this->nombreUsuario=userName;
            estado="true";
        }
        Playlist(){
        }
        ~Playlist(){
        }
        void setCodigo(int code) {codigo=code;}

        void setNombre(string name) {nombre=name;}

        void setUsuario(string userName) {nombreUsuario=userName;}

        void setCanciones(vector<int> vectorCode) {vectorCodigo=vectorCode;}

        void setEstado(string state) {estado=state;}

        int getCodigo()
        {
            return codigo;
        }
        string getNombre()
        {
            return nombre;
        }

        string getUsuario()
        {
            return nombreUsuario;
        }

        vector<int> getCanciones()
        {
          return vectorCodigo;
        }

        string getEstado(){
          return estado;
        }

        void agregarCancion(int cod){
          vectorCodigo.push_back(cod);
        }
};
#endif
//cuando haga el getvectorcodigocancion, consigo el codigo de las canciones, tengo un vector con puros codigos, debo ir comparando uno con uno con las canciones del codigo csv, puedo usar la clase de jaqui
//los codigos que tengo yo deben compararse con los codigos de las canciones y ver cuales son iguales para mostrarlas.

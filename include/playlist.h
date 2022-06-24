#ifndef __PLAYLIST_H__
#define __PLAYLIST_H__
#include<string>
#include<iostream>
#include<vector>
using namespace std;

class Playlist
{
    private:
        string Nombre;
        int Codigo;
        string NombreUsuario;
        vector<int> VectorCodigo;
        string Estado;//para hacer una eliminacion logica, no se muestra en el programa, pero se queda en el archivo
        //solo guardar los codigos, cancion csv y de alli solo jalo el codigo de la cancion.
    public:
        Playlist(int codigo, string name, string userName)
        {
            this->Nombre = name;
            this->Codigo = codigo;
            this->NombreUsuario = userName;
            Estado = "true";
        }
        Playlist(){
        }
        ~Playlist(){
        }

        int getCodigo() {return Codigo;}
        void setCodigo(int codigo) {Codigo = codigo;}

        string getNombre()  {return Nombre;}
        void setNombre(string nombre) {Nombre = nombre;}

        string getUsuario(){return NombreUsuario;}
        void setUsuario(string nombreUsuario) {NombreUsuario = nombreUsuario;}

        vector<int> getCanciones(){return VectorCodigo;}
        void setCanciones(vector<int> codigoVector) {VectorCodigo = codigoVector;}

        string getEstado(){return Estado;}
        void setEstado(string estado) {Estado=estado;}

        void agregarCancion(int cod){VectorCodigo.push_back(cod);}
};
#endif

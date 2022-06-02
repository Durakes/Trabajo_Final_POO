#include<string>
#include "Cancion.h"
using namespace std;
class Playlist{
    private:
        string nombre;
        int codigo;
        string nombreUsuario;
        vector<Cancion> vectorCancion;//crear un set y un get, guardar solo el codigo en el csv, pero en el vector playlist todos los datos.
        //vector canciones, agegar, quitar y mostrar canciones de la playlist, crear clase
        vector<int> vectorCodigo;
        //solo guardar los codigos, cancion csv y de alli solo jalo el codigo de la cancion.
    public:
        Playlist(string name, int code, string userName, vector<Cancion> vectorSong, vector<int> vectorCode){
            this->nombre=name;
            this->codigo=code;
            this->nombreUsuario=userName;
            this->vectorCancion=vectorSong;
            this->vectorCodigo=vectorCode;
        }
        Playlist(){
        }
        ~Playlist(){
        }
        void setCodigoPlaylist(int code) {codigo=code;}

        void setNombrePlaylist(string name) {nombre=name;}

        void setNombreUsuario(string userName) {nombreUsuario=userName;}

        void setVectorCancion(vector<Cancion> vectorSong) {vectorCancion=vectorSong;}

        void setVectorCanncionCodigo(vector<int> vectorCode) {vectorCodigo=vectorCode;}

        int getCodigoPlaylist()
        {
            return codigo;
        }
        string getNombrePlaylist()
        {
            return nombre;
        }

        string getNombreUsuario()
        {
            return nombreUsuario;
        }

        vector<Cancion> getVectorCancion()
        {
          return vectorCancion;
        }

        vector<int> getVectorCodigoCancion()
        {
          return vectorCodigo;
        }
};

//cuando haga el getvectorcodigocancion, consigo el codigo de las canciones, tengo un vector con puros codigos, debo ir comparando uno con uno con las canciones del codigo csv, puedo usar la clase de jaqui
//los codigos que tengo yo deben compararse con los codigos de las canciones y ver cuales son iguales para mostrarlas.

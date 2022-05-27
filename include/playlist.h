#include<string>
using namespace std;
class Playlist{
    private:
        string nombre;
        int codigo;
    public:
        Playlist(string name, int code){
            this->nombre=name;
            this->codigo=code;
        }
        Playlist(){
        }
        ~Playlist(){
        }
        void setCodigoPlaylist(int code) {codigo=code;}

        void setNombrePlaylist(string name) {nombre=name;}

        int getCodigoPlaylist()
        {
            return codigo;
        }
        string getNombrePlaylist()
        {
            return nombre;
        }
};
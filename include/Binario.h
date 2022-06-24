#ifndef __BINARIO_H__
#define __BINARIO_H__
#include <vector>
#include <fstream>
#include "Usuario.h"

class Binario
{
    private:
        string Ruta;
    public:
        Binario(string ruta)
        {
            Ruta = ruta;
        }
        
        void GrabarDato(Usuario obj)
        {
            FILE* archivo;
            archivo = fopen((char*)&Ruta[0], "ab");
            fwrite((char*)&obj, sizeof(Usuario), 1, archivo);
            fclose(archivo);
        }

        vector<Usuario> LeerDato()
        {
            vector<Usuario> vectorUsuarios;
            Usuario objUsuario;

            FILE* archivo;
            archivo = fopen((char*)&Ruta[0], "rb");

            fread(&objUsuario, sizeof(Usuario), 1, archivo);

            while(!feof(archivo))
            {
                vectorUsuarios.push_back(objUsuario);
                fread(&objUsuario, sizeof(Usuario), 1, archivo);
            };

            fclose(archivo);

            return vectorUsuarios;
        }
};
#endif
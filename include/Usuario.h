#ifndef __USUARIO_H__
#define __USUARIO_H__
#include <iostream>
#include <cstring>
using namespace std;
class Usuario
{
    protected:
        int Codigo;
        char Nombre[100];
        char NombreUsuario[100];
        char Contrasena[100];
        char Tipo[100];
    public:
        Usuario(){}
        Usuario(int codigo,char* nombre, char* nombreUsuario, char* contrasena, char* tipo)
        {
            Codigo = codigo;
            strcpy(Nombre, nombre);
            strcpy(NombreUsuario, nombreUsuario);
            strcpy(Contrasena, contrasena);
            strcpy(Tipo, tipo);
        }

        int getCodigo()    {return Codigo;}
        void setCodigo(int codigo)   {Codigo = codigo;}

        char* getNombre()    {return Nombre;}
        void setNombre(char* nombre)   {strcpy(Nombre, nombre);}

        char* getNombreUsuario()    {return NombreUsuario;}
        void setNombreUsuario(char* nombreUsuario) {strcpy(NombreUsuario, nombreUsuario);}

        char* getContrasena()    {return Contrasena;}
        void setContrasena(char *contrasena) {strcpy(Contrasena, contrasena);}

        char* getTipo()    {return Tipo;}
        void setTipo(char* tipo)   {strcpy(Tipo, tipo);}
};
#endif

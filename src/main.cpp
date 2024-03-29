#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <algorithm>
#include "..\include\Auxiliar.h"
#include "..\include\Archivo.h"
#include "..\include\Binario.h"
#include "..\lib\bcrypt\src\bcrypt.cpp"
#include "buscarCancion.cpp"
#include "crearCancion.cpp"
#include "buscarArtista.cpp"
#include "playlist.cpp"
using namespace std;

void menuOpciones(int codigo, string nombreUsuario, string nombreArtista)
{
    int opcion;
    system("cls");
    
    aux::cuadro(0,0,45, 13);
    aux::gotoxy(6,1);   cout << "##### Bienvenido " << nombreArtista << " ##### ";
    aux::gotoxy(1,3);   cout << "Playlist";         aux::gotoxy(25,3); cout << "[1]";
    aux::gotoxy(1,4);   cout << "Buscar Canciones"; aux::gotoxy(25,4); cout << "[2]";
    aux::gotoxy(1,5);   cout << "Buscar Artista";   aux::gotoxy(25,5); cout << "[3]";
    aux::gotoxy(1,6);   cout << "Crear Cancion";    aux::gotoxy(25,6); cout << "[4]";
    aux::gotoxy(1,7);   cout << "Salir";            aux::gotoxy(25,7); cout << "[5]";
    aux::gotoxy(1,9);   cout << "Ingrese la opcion que desea > "; cin >> opcion; cin.ignore();
    
    switch (opcion)
    {
    case 1:
        system("cls");
        menuPlaylist(nombreUsuario);
        menuOpciones(codigo, nombreUsuario, nombreArtista);
        break;
    case 2:
        system("cls");
        menuBuscarCancion(nombreUsuario,"0");
        menuOpciones(codigo, nombreUsuario, nombreArtista);
        break;
    case 3:
        system("cls");
        menuBuscarArtista(nombreUsuario,"0");
        menuOpciones(codigo, nombreUsuario, nombreArtista);
        break;
    case 4:
        crearCancion(codigo, nombreArtista);
        menuOpciones(codigo, nombreUsuario, nombreArtista);
        break;
    case 5:
        system("cls");
        aux::cuadro(0,0,50, 6);
        aux::gotoxy(1,2);   cout << "GRACIAS!!!";
        aux::gotoxy(1,3);   system("pause");
        system("cls");
        exit(0);
        break;
    default:
        aux::gotoxy(1,11); cout << "Ingrese una opcion correcta!!" << endl;
        aux::gotoxy(1,12); system("pause");
        menuOpciones(codigo, nombreUsuario, nombreArtista);
        break;
    }
}

void menuOpciones(int codigo, string nombreUsuario)
{
    int opcion;
    system("cls");
    aux::cuadro(0,0,45, 13);
    
    aux::gotoxy(5,1);   cout << "##### Bienvenido " << nombreUsuario << " #####";
    aux::gotoxy(1,3);   cout << "Playlist";         aux::gotoxy(25,3); cout << "[1]";
    aux::gotoxy(1,4);   cout << "Buscar Canciones"; aux::gotoxy(25,4); cout << "[2]";
    aux::gotoxy(1,5);   cout << "Buscar Artista";   aux::gotoxy(25,5); cout << "[3]";
    aux::gotoxy(1,6);   cout << "Salir";            aux::gotoxy(25,6); cout << "[4]";
    aux::gotoxy(1,8);   cout << "Ingrese la opcion que desea > "; cin >> opcion; cin.ignore();
    
    switch (opcion)
    {
    case 1:
        system("cls");
        menuPlaylist(nombreUsuario);
        menuOpciones(codigo, nombreUsuario);
        break;
    case 2:
        system("cls");
        menuBuscarCancion(nombreUsuario,"0");
        menuOpciones(codigo, nombreUsuario);
        break;
    case 3:
        system("cls");
        menuBuscarArtista(nombreUsuario,"0");
        menuOpciones(codigo, nombreUsuario);
        break;
    case 4:
        system("cls");
        aux::cuadro(0,0,50, 6);
        aux::gotoxy(1,2);   cout << "GRACIAS!!!";
        aux::gotoxy(1,3);   system("pause");
        system("cls");
        exit(0);
        break;
    default:
        aux::gotoxy(1,11); cout << "Ingrese una opcion correcta!!" << endl;
        aux::gotoxy(1,12); system("pause");
        menuOpciones(codigo, nombreUsuario);
        break;
    }
}

void inicioSesion(int tries)
{
    string nombreUsuario;
    int ch;
    string contrasena;
    bool usuarioExiste;
    string ruta = "..\\docs\\Usuarios.bin";
    Binario binFile(ruta);
    vector<string> usuariosExistentes;
    vector<Usuario> vectorUsuarios = binFile.leerDato();
    Usuario usuario;

    if(tries<3)
    {
        system("cls");
        aux::cuadro(0,0,45, 11);
        aux::gotoxy(9,1);   cout << "##### INICIO DE SESION #####" << endl;
        aux::gotoxy(1,3);   cout << "Ingrese su Usuario > "; getline(cin, nombreUsuario);
        aux::gotoxy(1,4);   cout << "Ingrese su Contrasena > "; ch = getch();
        
        while (ch != 13) /*13 ASCCI ENTER*/
        {
            if(ch != 8) /*8 BACKSPACE*/
            {
                contrasena.push_back(ch);
                cout << "*";
            }else
            {
                if(contrasena.length() > 0)
                {
                    cout << "\b \b";
                    contrasena = contrasena.substr(0, contrasena.length() - 1);
                }
            }
            ch = getch();
        }

        for(Usuario usuario: vectorUsuarios)
        {
            usuariosExistentes.push_back(aux::aMinuscula(usuario.getNombreUsuario())); 
        }

        aux::ordenamientoRapido(&usuariosExistentes, 0, usuariosExistentes.size() - 1, &vectorUsuarios);

        if(aux::busquedaBinariaPuntual(0, usuariosExistentes.size() - 1, aux::aMinuscula(nombreUsuario), usuariosExistentes))
        {
            usuarioExiste = true;
            aux::busquedaBinariaUsuario(0, usuariosExistentes.size() - 1, aux::aMinuscula(nombreUsuario), usuariosExistentes, &usuario, vectorUsuarios);
        }
        
        if(usuarioExiste == true)
        {
            if(bcrypt::validatePassword(contrasena,usuario.getContrasena()))
            {
                string tipo = "user";
                if(usuario.getTipo() == tipo)
                {
                    menuOpciones(usuario.getCodigo(), usuario.getNombreUsuario());
                }else
                {
                    menuOpciones(usuario.getCodigo(), usuario.getNombreUsuario(), usuario.getNombre());
                }
            }else
            {
                aux::gotoxy(1,6); cout << "Los datos ingresados son incorrectos!!" << endl;
                aux::gotoxy(1,7); system("pause");
                inicioSesion(tries+1);
            }
        }else
        {
            aux::gotoxy(1,6); cout << "El usuario no existe!" << endl;
            aux::gotoxy(1,7); system("pause");
            inicioSesion(tries+1);
        }
    }
    else
    {
        aux::gotoxy(1,9); cout << "Ha superado el limite de intentos " << endl;
        aux::gotoxy(1,10); system("pause");
        exit(0);
    }
}

void registroUsuario()
{
    string nombreCompleto;
    string nombreUsuario;
    string contrasena;
    string verificarContrasena;
    string esArtista;
    string tipoUsuario;
    bool usuarioExiste = false;

    system("cls");
    aux::cuadro(0,0,59,15);
    aux::gotoxy(17,1);   cout << "##### NUEVO REGISTRO #####" << endl;
    aux::gotoxy(1,3);   cout << "Ingrese su nombre completo > ";    getline(cin, nombreCompleto);
    aux::gotoxy(1,4);   cout << "Ingrese su usuario a usar > ";     getline(cin, nombreUsuario);
    aux::gotoxy(1,5);   cout << "Ingrese su contrasena > ";  getline(cin, contrasena);
    aux::gotoxy(1,6);   cout << "Ingrese su contrasena nuevamente > "; getline(cin, verificarContrasena);
    aux::gotoxy(1,7);   cout << "Es una cuenta de artista? (Si o no) > "; getline(cin, esArtista);
    transform(esArtista.begin(), esArtista.end(), esArtista.begin(), ::tolower);

    if(esArtista == "si")
    {
        tipoUsuario = "artist";
    }else
    {
        tipoUsuario = "user";
    }

    string ruta = "..\\docs\\Usuarios.bin";
    Binario archivoBin(ruta);
    vector<string> usuariosExistentes;
    int codigo = 1;
    string rutaVerificar = "../docs/Usuarios.bin";
    ifstream archivo((char*)&rutaVerificar[0]);
    if(archivo.good() == true)
    {
        vector<Usuario> vectorUsuarios = archivoBin.leerDato();
        if(vectorUsuarios.size() == 0)
        {
            codigo = 1;
        }else
        {
            codigo = vectorUsuarios.size() + 1;
        }

        for(Usuario usuario: vectorUsuarios)
        {
            usuariosExistentes.push_back(aux::aMinuscula(usuario.getNombreUsuario())); 
        }

        aux::ordenamientoRapido(&usuariosExistentes, 0, usuariosExistentes.size() - 1, &vectorUsuarios);
        
        if(aux::busquedaBinariaPuntual(0, usuariosExistentes.size() - 1, aux::aMinuscula(nombreUsuario), usuariosExistentes))
        {
            aux::gotoxy(1,9);   cout << "Este nombre de usuario ya existe" << endl;
            aux::gotoxy(1,10);  system("pause");
            usuarioExiste = true;
        }else
        {
            usuarioExiste = false;
        }
        
    }
    archivo.close();
    if(usuarioExiste == false)
    {
        if(verificarContrasena == contrasena)
        {
            string hashed = bcrypt::generateHash(contrasena);
            Usuario nuevoUsuario(codigo, (char*)&nombreCompleto[0], (char*)&nombreUsuario[0], (char*)&hashed[0], (char*)&tipoUsuario[0]);
            archivoBin.grabarDato(nuevoUsuario);
            aux::gotoxy(1,9);   cout << "Cuenta creada exitosamente!" << endl;
            aux::gotoxy(1,10);  system("pause");
        }else
        {
            aux::gotoxy(1,9);   cout << "Las contrasenas no coinciden!!!" << endl;
            aux::gotoxy(1,10);  system("pause");
            registroUsuario();
        }
    }else
    {
        registroUsuario();
    }
}

int main()
{
    int opcion;
    system("cls");
    aux::cuadro(0,0,35, 10);
    aux::gotoxy(7,1);   cout << "##### BIENVENIDO #####" << endl;
    aux::gotoxy(1,3);   cout << "Iniciar sesion" << endl;   aux::gotoxy(18,3); cout << "[1]" << endl;
    aux::gotoxy(1,4);   cout << "Registro" << endl;         aux::gotoxy(18,4); cout << "[2]" << endl;
    aux::gotoxy(1,5);   cout << "Ingrese la opcion que desea > "; cin >> opcion; cin.ignore();

    switch (opcion)
    {
    case 1:
        system("cls");
        inicioSesion(0);
        break;
    case 2:
        registroUsuario();
        system("cls");
        main();
        break;
    default:
        system("cls");
        exit(0);
        break;
    }
    return 0;
}
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <algorithm>
#include "..\include\Auxiliar.h"
#include "..\include\Archive.h"
#include "..\lib\bcrypt\src\bcrypt.cpp"
#include "..\src\buscarCancion.cpp"
#include "..\src\creacancion.cpp"
#include "..\src\BuscarArtista.cpp"
#include "..\include\BinaryFile.h"
#include "playlist.cpp"
using namespace std;

void menuOpciones(int codigo, string name, string typeUser, string artistName)
{
    int opcion;
    system("cls");
    if(typeUser == "user")
    {
        aux::cuadro(0,0,45, 13);
        //! hacer un string, conocer la cantidad de caracteres, dividir total/string size y restar - 1 para que esté centrado!
        aux::gotoxy(5,1);   cout << "##### Bienvenido "<< name <<" ##### "; //! Convertir a string
        aux::gotoxy(1,3);   cout << "Playlist" << endl;         aux::gotoxy(25,3); cout << "[1]" << endl;
        aux::gotoxy(1,4);   cout << "Buscar Canciones" << endl; aux::gotoxy(25,4); cout << "[2]" << endl;
        aux::gotoxy(1,5);   cout << "Buscar Artista" << endl;   aux::gotoxy(25,5); cout << "[3]" << endl;
        aux::gotoxy(1,6);   cout << "Salir" << endl;            aux::gotoxy(25,6); cout << "[5]" << endl;
        aux::gotoxy(1,8);   cout << "Ingrese la opcion que desea > "; cin >> opcion; cin.ignore();
    }else
    {
        aux::cuadro(0,0,45, 13);
        aux::gotoxy(6,1);   cout << "##### Bienvenido "<< name <<" ##### ";
        aux::gotoxy(1,3);   cout << "Playlist";         aux::gotoxy(25,3); cout << "[1]";
        aux::gotoxy(1,4);   cout << "Buscar Canciones"; aux::gotoxy(25,4); cout << "[2]";
        aux::gotoxy(1,5);   cout << "Buscar Artista";   aux::gotoxy(25,5); cout << "[3]";
        aux::gotoxy(1,6);   cout << "Crear Cancion";    aux::gotoxy(25,6); cout << "[4]";
        aux::gotoxy(1,7);   cout << "Salir";            aux::gotoxy(25,7); cout << "[5]";
        aux::gotoxy(1,9);   cout << "Ingrese la opcion que desea > "; cin >> opcion; cin.ignore();
    }
    switch (opcion)
    {
    case 1:
        system("cls");
        menuPlaylist(name);
        break;
    case 2:
        system("cls");
        menuBuscarCancion(name,"0");
        menuOpciones(codigo, name, typeUser, artistName);
        break;
    case 3:
        system("cls");
        menuBuscarArtista(name,"0");
        menuOpciones(codigo, name, typeUser, artistName);
        break;
    case 5:
        exit(0);
        break;
    case 4:
        if (typeUser != "user")
        {
            system("cls");
            subMenu_CrearCancion(codigo, artistName);
            menuOpciones(codigo, name, typeUser, artistName);
            break;
        }
    default:
        aux::gotoxy(1,11); cout << "Ingrese una opcion correcta!!" << endl;
        menuOpciones(codigo, name, typeUser, artistName);
        break;
    }
}


void login(int tries)
{
    string nombreUsuario;
    int ch;
    string contrasena;
    bool usuarioExiste;
    string ruta = "..\\docs\\Usuarios.bin";
    BinaryFile binFile(ruta);
    vector<string> usuariosExistentes;
    vector<User> vectorUsuarios = binFile.LeerDato();
    User usuario;

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

        for(User user: vectorUsuarios)
        {
            //! Pensar un workaround porque los usernames deben distingir uppercase de lowercase
            usuariosExistentes.push_back(aux::aMinuscula(user.getUsername())); 
        }

        aux::ordenamientoRapido(&usuariosExistentes, 0, usuariosExistentes.size() - 1, &vectorUsuarios);

        if(aux::busquedaBinariaPuntual(0, usuariosExistentes.size() - 1, aux::aMinuscula(nombreUsuario), usuariosExistentes))
        {
            usuarioExiste = true;
            aux::busquedaBinariaUsuario(0, usuariosExistentes.size() - 1, aux::aMinuscula(nombreUsuario), usuariosExistentes, &usuario, vectorUsuarios);
        }
        
        if(usuarioExiste == true)
        {
            if(bcrypt::validatePassword(contrasena,usuario.getPassword()))
            {
                menuOpciones(usuario.getCode(), usuario.getUsername(), usuario.getType(), usuario.getName());
            }else
            {
                aux::gotoxy(1,6); cout << "Los datos ingresados son incorrectos!!" << endl;
                aux::gotoxy(1,7); system("pause");
                login(tries+1);
            }
        }else
        {
            aux::gotoxy(1,6); cout << "El usuario no existe!" << endl;
            aux::gotoxy(1,7); system("pause");
            login(tries+1);
        }
    }
    else
    {
        aux::gotoxy(1,9); cout << "Ha superado el limite de intentos " << endl;
        aux::gotoxy(1,10); system("pause");
        exit(0);
    }
}

void registerUser()
{
    string name;
    string username;
    string passwordIni;
    string passwordFin;
    string typeArtist;
    string type;
    bool userExists = false;

    system("cls");
    aux::cuadro(0,0,59,15);
    aux::gotoxy(17,1);   cout << "##### NUEVO REGISTRO #####" << endl;
    aux::gotoxy(1,3);   cout << "Ingrese su nombre completo > ";    getline(cin, name);
    aux::gotoxy(1,4);   cout << "Ingrese su usuario a usar > ";     getline(cin, username);
    aux::gotoxy(1,5);   cout << "Ingrese su contrasena > ";  getline(cin, passwordIni);
    aux::gotoxy(1,6);   cout << "Ingrese su contrasena nuevamente > "; getline(cin, passwordFin);
    aux::gotoxy(1,7);   cout << "Es una cuenta de artista? (Si o no) > "; getline(cin, typeArtist);
    transform(typeArtist.begin(), typeArtist.end(), typeArtist.begin(), ::tolower);

    //Arreglar y ordenar
    if(typeArtist == "si")
    {
        type = "artist";
    }else
    {
        type = "user";
    }

    string ruta = "..\\docs\\Usuarios.bin";
    BinaryFile archive(ruta);
    vector<string> usuariosExistentes;
    int codigo = 1;
    string rutaF = "../docs/Usuarios.bin";
    ifstream file((char*)&rutaF[0]);
    if(file.good() == true)
    {
        vector<User> vectorUsuarios = archive.LeerDato();
        if(vectorUsuarios.size() == 0)
        {
            codigo = 1;
        }else
        {
            codigo = vectorUsuarios.size() + 1;
        }

        for(User user: vectorUsuarios)
        {
            //! Pensar un workaround porque los usernames deben distingir uppercase de lowercase
            usuariosExistentes.push_back(aux::aMinuscula(user.getUsername())); 
        }

        aux::ordenamientoRapido(&usuariosExistentes, 0, usuariosExistentes.size() - 1, &vectorUsuarios);
        
        if(aux::busquedaBinariaPuntual(0, usuariosExistentes.size() - 1, aux::aMinuscula(username), usuariosExistentes))
        {
            aux::gotoxy(1,9);   cout << "Este nombre de usuario ya existe" << endl;
            aux::gotoxy(1,10);  system("pause");
            userExists = true;
        }else
        {
            userExists = false;
        }
        
    }
    file.close();
    if(userExists == false)
    {
        if(passwordFin == passwordIni)
        {
            string hashed = bcrypt::generateHash(passwordIni);
            User newUser(codigo, (char*)&name[0], (char*)&username[0], (char*)&hashed[0], (char*)&type[0]);
            archive.GrabarDato(newUser);
            //cout << endl;
            aux::gotoxy(1,9);  cout << "Cuenta creada exitosamente!" << endl;
            aux::gotoxy(1,10);  system("pause");
        }else
        {
            //cout << endl;
            aux::gotoxy(1,9);   cout << "Las contrasenas no coinciden!!!" << endl;
            aux::gotoxy(1,10);   system("pause");
            registerUser();
        }
    }else
    {
        registerUser();
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
        login(0);
        break;
    case 2:
        registerUser();
        system("cls");
        main();
        break;
    default:
        break;
    }
    return 0;
}

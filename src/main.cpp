#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <algorithm>
#include "..\include\Archive.h"
#include "..\lib\bcrypt\src\bcrypt.cpp"
#include "..\src\buscarCancion.cpp"
#include "..\src\creacancion.cpp"
#include "..\include\BinaryFile.h"
#include "playlist.cpp"
using namespace std;

void menuOpciones(int code, string name, string typeUser)
{
    int option;
    system("cls");
    if(typeUser == "user")
    {
        cout << "##### Bienvenido "<< name << " ##### \n Playlist [1] \n Buscar Canciones [2] \n Buscar Artista [3] \n Ingrese una opcion [1-3] o presione [5] para salir" << endl;
    }else
    {
        cout << "##### Bienvenido "<< name << " ##### \n Playlist [1] \n Buscar Canciones [2] \n Buscar Artista [3] \n Crear Cancion [4] \n Ingrese una opcion [1-4] o presione [5] para salir" << endl;
    }

    cin >> option;
    cin.ignore();

    switch (option)
    {
    case 1:
        menuPlaylist(name);
        break;
    case 2:
        system("cls");
        menuBuscarCancion(name,"0");
        menuOpciones(code, name, typeUser);
        break;
    case 4:
        system("cls");
        subMenu_CrearCancion(code, name);
    case 5:
        exit(0);
        break;

    default:
        break;
    }
}


void login(int tries)
{
    string user;
    int ch;
    string password;
    bool userExist;
    string path = "..\\docs\\Users.bin";
    BinaryFile binFile(path);
    vector<User> users = binFile.LeerDato();
    User usuario;


    if(tries<3)
    {
        system("cls");
        cout << "Ingrese su Usuario: " << endl;
        cin >> user;
        cout << "Ingrese su Contrasena: " << endl;
        ch = getch();
        while (ch != 13) /*13 ASCCI ENTER*/
        {
            if(ch != 8) /*8 BACKSPACE*/
            {
                password.push_back(ch);
                cout << "*";
            }else
            {
                if(password.length() > 0)
                {
                    cout << "\b \b";
                    password = password.substr(0, password.length() - 1);
                }
            }
            ch = getch();
        }

        for(int i = 0; i < users.size(); i++)
        {
            if(user == users[i].getUsername())
            {
                userExist = true;
                usuario = users[i];
                break;
            }
        }

        if(userExist == true)
        {
            if(bcrypt::validatePassword(password,usuario.getPassword()))
            {
                menuOpciones(usuario.getCode(), usuario.getUsername(), usuario.getType());
            }else
            {
                cout << endl;
                cout << "Los datos ingresados son incorrectos!!" << endl;
                system("pause");
                login(tries+1);
            }
        }else
        {
            cout << endl;
            cout << "El usuario no existe!" << endl;
            system("pause");
            login(tries+1);
        }
    }
    else
    {
        cout << endl;
        cout << "Ha superado el limite de intentos " << endl;
        system("pause");
        exit(0);
    }


}

void registerUser()
{
    string name;
    string email;
    string phoneNumber;
    string username;
    string passwordIni;
    string passwordFin;
    string typeArtist;
    string type;
    bool userExists = false;

    system("cls");
    cout << " REGISTRO DE NUEVO USUARIO \n";
    cout << "Ingrese su nombre completo: \n";
    getline(cin, name);
    cout << "Ingrese su usuario a usar: \n";
    getline(cin, username);
    cout << "Ingrese su contrasena: \n";
    getline(cin, passwordIni);
    cout << "Ingrese su contrasena nuevamente: \n";
    getline(cin, passwordFin);
    cout << "Es una cuenta de artista? (Si o no)\n";
    getline(cin, typeArtist);
    transform(typeArtist.begin(), typeArtist.end(), typeArtist.begin(), ::tolower);

    //Arreglar y ordenar
    if(typeArtist == "si")
    {
        type = "artist";
    }else
    {
        type = "user";
    }

    string path = "..\\docs\\Users.bin";
    BinaryFile archive(path);
    User user;
    int code = 1;
    string ruta = "../docs/Users.bin";
    ifstream file((char*)&ruta[0]);
    if(file.good() == true)
    {
        vector<User> users = archive.LeerDato();
        if(users.size() == 0)
        {
            code = 1;
        }else
        {
            code = users.size() + 1;
        }

        for(int i = 0 ; i < users.size(); i++)
        {
            if(username == users[i].getUsername())
            {
                cout << endl;
                cout << "Este nombre de usuario ya existe" << endl;
                system("pause");
                userExists = true;
                break;
            }else
            {
                userExists = false;
            }
        }
    }
    file.close();
    if(userExists == false)
    {
        if(passwordFin == passwordIni)
        {
            string hashed = bcrypt::generateHash(passwordIni);
            User newUser(code, (char*)&name[0], (char*)&username[0], (char*)&hashed[0], (char*)&type[0]);
            archive.GrabarDato(newUser);
            cout << endl;
            cout << "Cuenta creada exitosamente!" << endl;
            system("pause");
        }else
        {
            cout << endl;
            cout << "Las contrasenas no coinciden!!!" << endl;
            system("pause");
            registerUser();
        }
    }else
    {
        registerUser();
    }

}

int main()
{
    int option;
    cout << "##### INICIO DE SESION ##### \n Iniciar sesion [1] \n Registro [2] \n Ingrese una opcion [1-2]" << endl;
    cin >> option;
    cin.ignore();

    switch (option)
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

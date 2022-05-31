#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <algorithm>
#include "..\include\Archive.h"
#include "..\lib\bcrypt\src\bcrypt.cpp"
#include "..\src\buscarCancion.cpp"
using namespace std;

void menuOpciones(string name, string typeUser)
{
    int option;
    system("cls");
    if(typeUser == "user")
    {
        cout << "##### Bienvenido "<< name << " ##### \n Mostrar Playlist [1] \n Buscar Canciones [2] \n Buscar Artista [3] \n Ingrese una opcion [1-3] o presione [5] para salir" << endl;
    }else
    {
        cout << "##### Bienvenido "<< name << " ##### \n Mostrar Playlist [1] \n Buscar Canciones [2] \n Buscar Artista [3] \n Crear Cancion [4] \n Ingrese una opcion [1-4] o presione [5] para salir" << endl;
    }

    cin >> option;
    cin.ignore();

    switch (option)
    {
    case 2:
        menuBuscar("");
        break;
    case 5:
        exit(0);
        break;
    
    default:
        break;
    }
}


void login()
{
    string user;
    int ch;
    string password;
    bool userExist;
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
    

    Archive archive(R"(..\docs\Users.csv)");
    vector<User> users;
    User usuario;
    archive.cargarDatos(usuario, &users);

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
            menuOpciones(usuario.getUsername(), usuario.getType());
        }else
        {
            cout << "Los datos ingresados son incorrectos!!" << endl;
            system("pause");
            login();
        }
    }else
    {
        cout << "El usuario no existe!" << endl;
        system("pause");
        login();
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

    Archive archive(R"(..\docs\Users.csv)");
    vector<User> users;
    User user;
    int code = 1;
    archive.cargarDatos(user, &users);

    //Arreglar y ordenar
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
            cout << "Este nombre de usuario ya existe" << endl;
            system("pause");
            userExists = true;
            break;
        }
    }

    if(userExists == false)
    {
        if(passwordFin == passwordIni)
        {
            string hashed = bcrypt::generateHash(passwordIni);
            User newUser(code, name, username, hashed, type);
            archive.saveNewLine(newUser);
            cout << "Cuenta creada exitosamente!" << endl;
            system("pause");
        }else
        {
            cout << "Contrasena Incorrecta!!!" << endl;
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
    //HOLA
    int option;
    cout << "##### INICIO DE SESION ##### \n Iniciar sesion [1] \n Registro [2] \n Ingrese una opcion [1-2]" << endl;
    cin >> option;
    cin.ignore();

    switch (option)
    {
    case 1:
        system("cls");
        login();
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
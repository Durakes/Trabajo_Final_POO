#include <iostream>
#include <string>
#include "..\include\User.h"
#include "..\lib\bcrypt\src\bcrypt.cpp"

void showPlaylist()
{
    cout << "Se muestran playlist" << endl;
}

void searchSong()
{
    cout << "Se buscan canciones" << endl;
}

void searchArtist()
{
    cout << "Se muestran artistas" << endl;
}

void createSong()
{
    cout << "Se crea una cancion" << endl;
}

void optionMenu()
{
    int option;
    cout << "##### BIENVENIDO USER ##### \n Mostrar Playlist [1] \n Buscar Cancion [2] \n Buscar Artista [3] \n Salir[5] \n Ingrese una opcion [1-5]" << endl;
    cin >> option;

    switch (option)
    {
    case 1:
        showPlaylist();
        break;
    case 2:
        searchSong();
        break;
    case 3:
        searchArtist();
        break;
    case 4:
        createSong();
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
    string password;
    system("cls");
    cout << "Ingrese su Usuario: " << endl;
    cin >> user;
    cout << "Ingrese su Contrasena: " << endl;
    cin >> password;
    
    string datos[2] = {user, password};
}

void registerUser()
{
    string user;
    string password;
    system("cls");
    cout << "Ingrese su Usuario: \n";
    cin >> user;
    cout << "Ingrese su Contrasena: \n";
    cin >> password;

    string hashed = bcrypt::generateHash(password);
    cout << password << endl;
    cout << hashed << endl;
    cout << bcrypt::validatePassword(password, hashed);
}

int main()
{
    int option;
    cout << "##### INICIO DE SESION ##### \n Iniciar sesion [1] \n Registro [2] \n Ingrese una opcion [1-2]" << endl;
    cin >> option;

    switch (option)
    {
    case 1:
        login();
        break;
    
    case 2:
        registerUser();
        break;
    
    default:
        break;
    }
    return 0;
}
#include <iostream>
#include <string>
#include <vector>
#include "..\include\Archive.h"
#include "..\lib\bcrypt\src\bcrypt.cpp"
using namespace std;

void login()
{

    // string user;
    // string password;
    // system("cls");
    // cout << "Ingrese su Usuario: " << endl;
    // cin >> user;
    // cout << "Ingrese su Contrasena: " << endl;
    // cin >> password;
    // string datos[2] = {user, password};

}

void registerUser()
{
    //Doble verificacion contraseña
    //Verificar que no existe un Usuario similar
    system("cls");
    string name;
    string email;
    int phoneNumber;
    string username;
    string passwordIni;
    string passwordFin;

    cout << " REGISTRO DE NUEVO USUARIO \n";
    cin.ignore();
    cout << "Ingrese su nombre completo: \n";
    getline(cin, name);
    cout << "Ingrese su correo electronico: \n"; 
    getline(cin, email);
    cout << "Ingrese su numero telefonico: \n";
    cin >> phoneNumber;
    cin.ignore();
    cout << "Ingrese su usuario a usar: \n";
    getline(cin, username);
    cout << "Ingrese su contrasena: \n";
    getline(cin, passwordIni);
    cout << "Ingrese su contrasena nuevamente: \n";
    getline(cin, passwordFin);

    if(passwordFin == passwordIni)
    {
        string hashed = bcrypt::generateHash(passwordIni);
        Archive archive(R"(..\docs\Users.csv)", 0);
        User newUser("U1", name, email, phoneNumber, username, hashed);
        archive.saveNewLine(newUser);
    }else
    {
        "Contrasena Incorrecta!!!";
        system("pause");
        registerUser();
    }

}

int main()
{
    //HOLA
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
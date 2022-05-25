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
    //Verificar que no existe un Usuario similar
    
    string name;
    string email;
    string phoneNumber;
    string username;
    string passwordIni;
    string passwordFin;
    bool userExists = false;

    system("cls");
    cout << " REGISTRO DE NUEVO USUARIO \n";
    cout << "Ingrese su nombre completo: \n";
    getline(cin, name);
    cout << "Ingrese su correo electronico: \n"; 
    getline(cin, email);
    cout << "Ingrese su numero telefonico: \n";
    getline(cin, phoneNumber);
    cout << "Ingrese su usuario a usar: \n";
    getline(cin, username);
    cout << "Ingrese su contrasena: \n";
    getline(cin, passwordIni);
    cout << "Ingrese su contrasena nuevamente: \n";
    getline(cin, passwordFin);

    Archive archive(R"(..\docs\Users.csv)", 0);
    vector<User> users;
    User user;
    archive.cargarDatos(&users);

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
            User newUser("U1", name, email, phoneNumber, username, hashed);
            archive.saveNewLine(newUser);
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
        break;
    
    default:
        break;
    }
    return 0;
}
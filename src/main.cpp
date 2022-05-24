#include <iostream>
#include <string>
using namespace std;

void login()
{

}

void registerUser()
{

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
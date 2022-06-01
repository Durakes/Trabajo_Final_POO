#include <iostream>
#include "../include/playlistVector.h"
#include <vector>
#include <cstring>
using namespace std;

PlaylistVector vectorPlaylist; //Instancia de la clase AlumnoVector
//Prototipos
void menuDeOpcionesInicioPlaylist();
void adicionarPlaylist();
void agregarCancionesPlaylist();
void listarPlaylist();
void BuscarPlaylist();
void EditarPlaylist();
void EliminarPlaylist();

int main()
{
	menuDeOpcionesInicioPlaylist();
}

void menuDeOpcionesInicioPlaylist()
{
	int respuesta;
	
	do
	{
		cout<<"Playlist\n";
		cout<<"Crear una playlist 	[1]\n";
		cout<<"Mostrar tus playlist	[2]\n";
		cout<<"Ingrese una opcion [1-2]:" ;
		cin>>respuesta;
		
		switch(respuesta)
		{
			case 1 : 	system("cls");	
						adicionarPlaylist();
				break;
            
            case 2 : 	system("cls");	
						listarPlaylist();
				break;

			default : cout<<"* INGRESE UN OPCION CORRECTA [1-2] *"<<endl;
		}
	}
	while(respuesta != 3);
}

void agregarCancionesPlaylist(){
	cout<<"* Busca las canciones para tu playlist: "<<endl;
	//llamo funcion de jacqueline
}

void adicionarPlaylist()
{
	int 	code;
	string 	name;
	string 	respuesta;

	do {
		code = vectorPlaylist.getCorrelativo();

		cout << "Crea tu playlist "<< endl;
		cin.ignore();
		cout << "* Crea un nombre para tu playlist: "; getline(cin, name);
		
		
		//Crear el objeto de la clase playlist
		Playlist playlist;
		
		playlist.setCodigoPlaylist(code);
		playlist.setNombrePlaylist(name);	
			
		vectorPlaylist.add(playlist); //Agregar el objeto a la estructura
		
		vectorPlaylist.grabarEnArchivo(playlist);
		
		agregarCancionesPlaylist();

		cout << "Desea continuar(SI/si): "; cin >> respuesta;
		system("cls");
	}

	while(respuesta == "SI" || respuesta == "si");
}

void EditarPlaylist(int rpta){
	int code; //Buscar el codigo
	code=rpta;
	Playlist objAModificar = vectorPlaylist.buscarPorCodigo(code);
	
	cout << "Registro encontrado" << endl;
	cout << "Codigo:" << objAModificar.getCodigoPlaylist() << endl;
	cout << "Nombre:" << objAModificar.getNombrePlaylist() << endl;
	cin.ignore();
	
	string nomMod;
	cout << "Ingrese el nuevo nombre: "; getline(cin, nomMod);
	bool estado = vectorPlaylist.modificar(objAModificar,nomMod);
		if(estado == true)
		{
			cout << "Registro modificado satisfactoriamente" << endl;
			vectorPlaylist.grabarModificarEliminarArchivo(); /* Grabar en archivo */
		}
		else
		{
			cout << "No se edito el registro" << endl;
		}
		system ("pause");
		system("cls");
}

void EliminarPlaylist(int rpta){
	int code;
	code=rpta;
	Playlist objAModificar = vectorPlaylist.buscarPorCodigo(code);
	cout << "Registro encontrado" << endl;
	cout << "Codigo:" << objAModificar.getCodigoPlaylist() << endl;
	cout << "Nombre:" << objAModificar.getNombrePlaylist() << endl;
	cin.ignore();
	
	string flag;
	cout << "Desea borrar este usuario...(Y/N)"; cin >> flag;
	
	if(flag == "Y" || flag == "y")
	{
		
		Playlist objADelete = vectorPlaylist.buscarPorCodigo(code);
		if(objADelete.getNombrePlaylist() != "Error")
		{
			vectorPlaylist.remove(objADelete);
			cout << "Registro eliminado satisfactoriamente" << endl;
			// Actualizamos el archivo para que nos muestre la lista nueva
			vectorPlaylist.grabarModificarEliminarArchivo();	
		}
		else
		{
			cout << "No se encontró el registro" << endl;
		}
		
		system ("pause");
		system("cls");
	}
	else
	{
		system ("pause");
		system("cls");
		menuDeOpcionesInicioPlaylist();
	}
}

void BuscarPlaylist(){

	int code;
	int rpta;
	cout << "Ingresar el codigo de la playlist que desea elegir: "; cin >> code;
	Playlist playlist = vectorPlaylist.buscarPorCodigo(code);
	
	if(playlist.getNombrePlaylist() != "Error")
	{
		cout << "Registro encontrado" << endl;
		cout << "Codigo:" << playlist.getCodigoPlaylist()<< endl;
		cout << "Nombre:" << playlist.getNombrePlaylist()<< endl;

		cout<<"Editar playlist	 [1]"<<endl;
		cout<<"Eliminar playlist [2]"<<endl;
		cout<<"Mostrar canciones [3]"<<endl;
		cout<<"* Elija una opción [1-3]: ";
		cin>>rpta;

		switch (rpta)
		{
		case 1:
			system("cls");
			EditarPlaylist(code);
			break;
		case 2:
			system("cls");
			EliminarPlaylist(code);
			break;
		case 3:
			system("cls");
			agregarCancionesPlaylist();
			break;		
		default:
			cout<<"Error elija una opción [1-3]: ";
			break;
		}

		system ("pause");
		system("cls");	
	}
	else
	{
		cout << "No se encontró el registro" << endl;
	}
	system ("pause");
	system("cls");
	menuDeOpcionesInicioPlaylist();
}

void listarPlaylist()
{
	int i;
	
	for(i=0; i<vectorPlaylist.rows(); i++) 
	{
		cout<<"Codigo: "<<vectorPlaylist.get(i).getCodigoPlaylist()<< "\t";
		cout<<"Nombre: "<<vectorPlaylist.get(i).getNombrePlaylist()<<endl;
	}
	
	BuscarPlaylist();

	system("pause");
	system("cls");
}
#ifndef __PLAYLIST_CPP__
#define __PLAYLIST_CPP__
#include <iostream>
#include "../include/playlistVector.h"
#include <vector>
#include <cstring>
#include "buscarCancion.cpp"
using namespace std;

PlaylistVector vectorPlaylist; //Instancia de la clase AlumnoVector
//Prototipos
void menuDeOpcionesInicioPlaylist(string name);
void adicionarPlaylist(string userName);
void agregarCancionesPlaylist();
void listarPlaylist(string userName);
void BuscarPlaylist();
void EditarPlaylist();
void EliminarPlaylist();
void EliminarCancion();
void mainPlaylist();
void listarCanciones();
void 	MostrarCancionesPorCodigo();

//el name es igual al username, si es igual se agrega al vector
//para mostrar, se diferencia por el codigo

void menuDeOpcionesInicioPlaylist(string name){
	int respuesta;
	string userName;
	userName=name;
	Playlist objAModificar = vectorPlaylist.buscarPorNombreUsuario(userName);
	objAModificar.setNombreUsuario(userName);
	cout<<objAModificar.getNombreUsuario();
	cout<<"\n";
		do
		{

			cout<<"Playlist\n";
			cout<<"Crear una playlist 	[1]\n";
			cout<<"Mostrar tus playlist	[2]\n";
			cout<<"Salir								[3]\n";
			cout<<"Ingrese una opcion [1-3]:" ;
			cin>>respuesta;

			switch(respuesta)
			{
				case 1 : 	system("cls");
				adicionarPlaylist(userName);
				break;

	      case 2 : 	system("cls");
				listarPlaylist(userName);
				break;

				case 3 : 	system("cls");
				cout<<"GRACIAS!!!";
				break;

				default : cout<<"* INGRESE UN OPCION CORRECTA [1-2] *"<<endl;
			}
		}
		while(respuesta != 3);
}

void agregarCancionesPlaylist(){

	cout<<"* Busca las canciones para tu playlist: "<<endl;

}

void adicionarPlaylist(string name)
{
	int 	code;
	string 	nameplaylist;
	string 	respuesta;
	string userName;
	userName=name;

			do {
				code = vectorPlaylist.getCorrelativo();

				cout << "Crea tu playlist "<< endl;
				cin.ignore();
				cout << "* Crea un nombre para tu playlist: "; getline(cin, name);


				//Crear el objeto de la clase alumno
				Playlist playlist;

				playlist.setCodigoPlaylist(code);
				playlist.setNombrePlaylist(name);
				playlist.setNombreUsuario(userName);

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
	string name;
	Playlist objAModificar = vectorPlaylist.buscarPorCodigo(code);
	cout << "Registro encontrado" << endl;
	cout << "Codigo:" << objAModificar.getCodigoPlaylist() << endl;
	cout << "Nombre:" << objAModificar.getNombrePlaylist() << endl;
	cin.ignore();

	string flag;
	cout << "Desea borrar esta playlist...(Y/N)"; cin >> flag;

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
			cout << "No se encontro el registro" << endl;
		}

		system ("pause");
		system("cls");
	}
	else
	{
		system ("pause");
		system("cls");
		menuDeOpcionesInicioPlaylist(name);
	}
}

void BuscarPlaylist(){

	int code;
	int rpta;
	string name;
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
		cout<<"* Elija una opcion [1-3]: ";
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
			listarCanciones();
			break;
		default:
			cout<<"Error elija una opcion [1-3]: ";
			break;
		}

		system ("pause");
		system("cls");
	}
	else
	{
		cout << "No se encontro el registro" << endl;
	}
	system ("pause");
	system("cls");
	menuDeOpcionesInicioPlaylist(name);
}

void listarPlaylist(string name)
{
	int i;
	string userName;
	userName=name;
		for(i=0; i<vectorPlaylist.rows(); i++)
		{
			if(userName==vectorPlaylist.get(i).getNombreUsuario()){
				cout<<"Codigo: "<<vectorPlaylist.get(i).getCodigoPlaylist()<< "\t";
				cout<<"Nombre: "<<vectorPlaylist.get(i).getNombrePlaylist()<<endl;
			}
		}

		BuscarPlaylist();

		system("pause");
		system("cls");
}


void MostrarCancionesPorCodigo(){
//Tengo que modificar esto para que primero busque el codigo en el vectorcodigocancion de acorde al codigo que Ingrese
//Probar si es con buscar por codigo cancion o buscar por cancion, si es asi entonces debo crear un buscarporvectorcancion
// luego el el cout debo poner cancion.getnombre por ejemplo y asi con todos los atributos de la cancion, recordar que solo puedo elimiar cancion
// o agregar cancion.

}

void listarCanciones(){

}
#endif
